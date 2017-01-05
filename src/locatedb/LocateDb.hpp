#ifndef LOCATEDB_HPP_
#define LOCATEDB_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include <stddef.h>
#include <cstring>
#include <limits.h>
#include <array>

#include "locatedb/Order.hpp"

#if CHAR_BIT != 8
#error Compile Error: Platforms on which chars != octets are not supported.
#endif

namespace locj
{

	/*!
	 * @enum FileEntryType
	 *
	 * The type of mlocate.db file entry.
	 */
	enum class FileEntryType
	{
		NON_DIRECTORY,//!< NON_DIRECTORY
		SUBDIRECTORY  //!< SUBDIRECTORY
	};

	/*!
	 * @class LocateDb
	 *
	 * Loads and parses an mlocate.db database.
	 */
	class LocateDb
	{

	public:
		/*!
		 * Constructor.
		 *
		 * @param[in]	filename	Filename of the mlocate database to read
		 */
		explicit LocateDb(std::string filename);

		/*!
		 * Load the file entry records in the database file, each representing a file or sub-directory.
		 *
		 * @param[in]	recordCallback	The callback to call for each record. Must provide an operator()(FileEntryType type, std::string path, std::string name) method
		 */
		template <typename C>
		void load(C recordCallback)
		{
			// Calculate the file size
			m_dbFile.seekg(0, std::ios::end);
			m_dbFileSize = m_dbFile.tellg();
			m_dbFile.seekg(0, std::ios::beg);

			try
			{
				header(recordCallback);
			}
			catch(std::ios_base::failure & e)
			{
				throw FileReadError(m_dbFilename);
			}
		}

	private:
		/*!
		 * Reads a null-terminated string from the m_dbFile stream
		 * object.
		 *
		 * @param[out]	value	The string object to which the read string is set
		 */
		void dbStr(std::string & value);

		/*!
		 * Tests if the specified number of bytes are available in the m_dbFile
		 * stream.
		 *
		 * @param[in]	numBytes	The number of bytes to test for
		 *
		 * @return true if the bytes are available, false if not
		 */
		bool bytesAvailable(long int numBytes);

		/*!
		 * Parses the database file header, before delegating to the ::entries() method
		 * for parsing the file entries.
		 *
		 * @param[in]	recordCallback	The callback to call for each record.
		 */
		template <typename C>
		void header(C recordCallback)
		{
			if (m_dbFileSize < m_MLOCATE_DB_HDR_SIZE)
			{
				throw TruncatedFileHeader();
			}

			// Read in the fixed header
			char hdr[m_MLOCATE_DB_HDR_SIZE];
			m_dbFile.read(&(hdr[0]), m_MLOCATE_DB_HDR_SIZE);

			// Check the magic number is correct
			if (memcmp(&(hdr[0]), m_MLOCATE_DB_MAGIC.data(), m_MLOCATE_DB_MAGIC.size()) != 0)
			{
				throw BadMagicNumber();
			}

			// Read the config block size
			std::uint32_t configBlockSize = Order::big32(reinterpret_cast<unsigned char *>(&(hdr[8])));
			if ((configBlockSize & static_cast<std::uint32_t>(0x80000000ul)) != 0)
			{
				throw InvalidConfigBlockSize();
			}

			// Check the file format version is correct
			if (hdr[12] != 0)
			{
				throw UnsupportedDatabaseVersion();
			}

			/*
			 * Read the variable part of the header (null-terminated root). As the root will only
			 * ever be used for prepending to sub-directories, ensure it has a trailing path
			 * separator.
			 */
			m_dbRoot.clear();
			dbStr(m_dbRoot);
			if (m_dbRoot.size() > 0)
			{
				if (m_dbRoot[m_dbRoot.size() - 1] != '/')
				{
					m_dbRoot.push_back('/');
				}
			}

			// Check the block isn't truncated
			if (!bytesAvailable(static_cast<long int>(configBlockSize)))
			{
				throw TruncatedConfigBlock();
			}

			// Skip the config block
			m_dbFile.seekg(static_cast<long int>(configBlockSize), std::ios::cur);

			// Read directory and file entries
			entries(recordCallback);
		}

		/*!
		 * Parses the file entries. These are the database records representing files and
		 * sub-directories. Calls recordCallback for each file entry found.
		 *
		 * @param[in]	recordCallback	The callback to call for each record.
		 */
		template <typename C>
		void entries(C recordCallback)
		{
			while (!m_dbFile.eof())
			{
				if (!bytesAvailable(m_MLOCATE_DIR_HDR_SIZE))
				{
					throw TruncatedDirHdr();
				}

				// Skip the header
				m_dbFile.seekg(m_MLOCATE_DIR_HDR_SIZE, std::ios::cur);

				// Read the variable part of the header (directory name).
				std::string currentDirPathName;
				dbStr(currentDirPathName);

				// Read the current directory's file entries
				bool noMoreEntries = false;
				while (!m_dbFile.eof())
				{
					FileEntryType fileType;
					unsigned char entryType = 3;
					m_dbFile.read(reinterpret_cast<char *>(&(entryType)), 1);

					switch (entryType)
					{
					case 0: // Non-directory file, string follows
						fileType = FileEntryType::NON_DIRECTORY;
						break;

					case 1: // Subdirectory, string follows
						fileType = FileEntryType::SUBDIRECTORY;
						break;

					case 2: // End of current directory
						noMoreEntries = true;
						break;

					default:
						throw BadFileEntryType();
						break;
					}

					if (noMoreEntries)
					{
						if (m_dbFile.tellg() == m_dbFileSize)
						{
							return;
						}
						else
						{
							break;
						}
					}
					else
					{
						std::string objectName;
						dbStr(objectName);

						recordCallback(fileType, currentDirPathName, objectName);
					}
				}
			}
		}

		/*!
		 * 16 bytes for the file fixed header:
		 *  - 8 byte magic number..............8
		 *  - 4 byte config block size........12
		 *  - 1 byte file format version......13
		 *  - 1 byte require visibility flag..14
		 *  - 2 byte padding..................16
		 */
		static const std::size_t m_MLOCATE_DB_HDR_SIZE;
		static const std::array<char, 8> m_MLOCATE_DB_MAGIC; //!< The mlocate.db magic number
		/*!
		 * 16 bytes for the directory fixed header:
		 *  - 8 byte time in seconds...........8
		 *  - 4 byte nanosecond remainder.....12
		 *  - 4 byte padding..................16
		 */
		static const std::size_t m_MLOCATE_DIR_HDR_SIZE;

		std::ifstream m_dbFile; //!< The database file stream from which to read
		std::string m_dbFilename; //!< The filename of the database being read
		long int m_dbFileSize; //!< The database file size
		std::string m_dbRoot; //!< The directory root of the mlocate database
	};

}

#endif /* LOCATEDB_HPP_ */
