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
