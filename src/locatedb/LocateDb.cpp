#include <string>
#include <cstdint>
#include <stddef.h>
#include <limits.h>

#include "locatedb/Order.hpp"
#include "exceptions.hpp"
#include "locatedb/LocateDb.hpp"

namespace locj
{

	const std::size_t LocateDb::m_MLOCATE_DB_HDR_SIZE = 16;
	const std::array<char, 8> LocateDb::m_MLOCATE_DB_MAGIC = std::array<char, 8>({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e' });
	const std::size_t LocateDb::m_MLOCATE_DIR_HDR_SIZE = 16;

	LocateDb::LocateDb(std::string filename) : m_dbFilename(filename), m_dbFile(filename), m_dbFileSize(0)
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


