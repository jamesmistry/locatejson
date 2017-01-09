/*!
 * @file JsonStringLiteral.cpp
 *
 * Copyright (c) 2016 James Mistry
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string>
#include <sstream>
#include <cstdint>
#include <iomanip>
#include <utility>

#include "jsondb/JsonStringLiteral.hpp"

namespace locj
{

	JsonStringLiteral::JsonStringLiteral(const std::string & data)
	{
		literalise(data, m_result);
	}

	JsonStringLiteral::JsonStringLiteral(const char * data)
	{
		std::string strData(data);

		literalise(strData, m_result);
	}

	JsonStringLiteral::JsonStringLiteral(JsonStringLiteral && rhs) : m_result(std::move(rhs.m_result))
	{
	}

	JsonStringLiteral & JsonStringLiteral::operator=(JsonStringLiteral && rhs)
	{
		if (this != &rhs)
		{
			m_result = std::move(rhs.m_result);
			rhs.m_result.clear();
		}

		return (*this);
	}

	JsonStringLiteral::operator const char * () const
	{
		return m_result.c_str();
	}

	void JsonStringLiteral::literalise(const std::string & in, std::string & out) const
	{
		out.push_back('"');

		for (auto c : in)
		{
			if ((c >= 0) && (c <= 0x1f))
			{
				switch(c)
				{
				case 8: // Backspace
					out.push_back('\\');
					out.push_back('b');
					break;
				case 9: // Horizontal tab
					out.push_back('\\');
					out.push_back('t');
					break;
				case 10: // Line feed
					out.push_back('\\');
					out.push_back('n');
					break;
				case 12: // Form feed
					out.push_back('\\');
					out.push_back('f');
					break;
				case 13: // Carriage return
					out.push_back('\\');
					out.push_back('r');
					break;
				default:
					escapeAsHex(c, out);
					break;
				}
			}
			else
			{
				switch(c)
				{
				case '"':
				case '\\':
				case '/':
					// Must be escaped
					out.push_back('\\');
					out.push_back(c);
					break;
				default:
					out.push_back(c);
					break;
				}
			}
		}

		out.push_back('"');
	}

	void JsonStringLiteral::escapeAsHex(char c, std::string & out) const
	{
		std::stringstream formatter;

		formatter << "\\u00" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << static_cast<std::uint16_t>(c);

		out += formatter.str();
	}

}
