/*!
 * @file JsonIndex.cpp
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

#include <iostream>

#include "jsondb/JsonStringLiteral.hpp"
#include "jsondb/JsonIndex.hpp"
#include "exceptions.hpp"

namespace locj
{

	JsonIndex::JsonIndex(std::ostream & out, std::string hostname) : m_hostname(hostname), m_numEntries(0), m_output(out)
	{
		// Enable exceptions on failed file writes
		m_output.exceptions(std::ostream::failbit | std::ostream::badbit);

		indexHeader(hostname);
	}

	JsonIndex::~JsonIndex()
	{
	    try
	    {
	        indexFooter();
	    }
	    catch (...)
	    {
	        return;
	    }
	}

	void JsonIndex::indexHeader(const std::string & hostname)
	{
		m_output << '{' << JsonStringLiteral("host") << ":" << JsonStringLiteral(hostname) << "," << JsonStringLiteral("entities") << ":[";
	}

	void JsonIndex::indexFooter()
	{
		m_output << "]}" << std::endl;
	}

	void JsonIndex::entry(bool file, const std::string & path, const std::string & name)
	{
		if (m_numEntries > 0)
		{
			m_output << ',';
		}

		m_output << '{' << JsonStringLiteral("file") << ':' << ((file) ? "true" : "false") << ',' << JsonStringLiteral("path") << ':' << JsonStringLiteral(path) << ',' << JsonStringLiteral("name") << ':' << JsonStringLiteral(name) << '}';

		++m_numEntries;
	}

}
