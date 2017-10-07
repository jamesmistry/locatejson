/*!
 * @file LocateDb.cpp
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
#include <cstdint>
#include <stddef.h>
#include <limits.h>

#include "locatedb/Order.hpp"
#include "exceptions.hpp"
#include "locatedb/LocateDb.hpp"

namespace locj
{

	const long int LocateDb::m_MLOCATE_DB_HDR_SIZE = 16;
	const std::array<char, 8> LocateDb::m_MLOCATE_DB_MAGIC = std::array<char, 8>({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e' });
	const std::size_t LocateDb::m_MLOCATE_DIR_HDR_SIZE = 16;

	LocateDb::LocateDb(std::string filename) : m_dbFile(filename), m_dbFilename(filename), m_dbFileSize(0)
	{
		if (m_dbFile.fail())
		{
			throw FileOpenError(filename);
		}
		else
		{
			// Enable exceptions on failed file reads
			m_dbFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		}
	}

	void LocateDb::dbStr(std::string & value)
	{
		try
		{
			value.clear();

			char currentByte = '\0';
			m_dbFile.read(&currentByte, 1);

			while (currentByte != '\0')
			{
				value.push_back(currentByte);
				m_dbFile.read(&currentByte, 1);

				if (value.size() > PATH_MAX)
				{
					throw OversizeDbString();
				}
			}
		}
		catch(std::ios_base::failure & e)
		{
			throw TruncatedDbString();
		}
	}

	bool LocateDb::bytesAvailable(long int numBytes)
	{
		return ((m_dbFileSize < (m_dbFile.tellg() + numBytes)) ? false : true);
	}

}


