#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <limits.h>

#include "exceptions.hpp"
#include "FileTestData.hpp"
#include "locatedb/LocateDb.hpp"

namespace locj
{

	TEST(LocateDb, file_open_error)
	{
		EXPECT_THROW(LocateDb subject(std::string("/tmp/locatejson/file_that_should_not_exist")), FileOpenError);
	}

	TEST(LocateDb, file_hdr_truncated)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\0', '\0', '\x01', '\0' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
		        {
		        }),
		        TruncatedFileHeader);
	}

	TEST(LocateDb, bad_magic_number)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'r', '\0', '\0', '\0', '\0', '\0', '\x01', '\0', '\0' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				BadMagicNumber);
	}

	TEST(LocateDb, bad_block_size)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\xc0', '\0', '\0', '\x01', '\0', '\x01', '\0', '\0' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				InvalidConfigBlockSize);
	}

	TEST(LocateDb, bad_format_version)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\xff', '\x01', '\0', '\0', '\0' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				UnsupportedDatabaseVersion);
	}

	TEST(LocateDb, truncated_config_block)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\x03', '\0', '\0', '\0', '\0', '/', '\0', 'a', 'b' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				TruncatedConfigBlock);
	}

	TEST(LocateDb, truncated_string_start)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\x03', '\0', '\0', '\0', '\0' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				TruncatedDbString);
	}

	TEST(LocateDb, truncated_string_end)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\x03', '\0', '\0', '\0', '\0', '/' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				TruncatedDbString);
	}

	TEST(LocateDb, truncated_dir_hdr)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '/',
			'\0', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x01', '\x02', '\x03', '\x04', '\0', '\0', '\0', });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				TruncatedDirHdr);
	}

	TEST(LocateDb, bad_file_entry_type)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '/',
			'\0', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x01', '\x02', '\x03', '\x04', '\0', '\0', '\0', '\0',
		    't', 's', 't', '\0', '\x03' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				BadFileEntryType);
	}

	TEST(LocateDb, oversize_string)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' });

		for (std::size_t i=0;i<PATH_MAX+1;++i)
		{
			testPayload.push_back('a');
		}
		testPayload.push_back('\0');

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		EXPECT_THROW(
				subject.load([](FileEntryType type, std::string root, std::string object)
				{
				}),
				OversizeDbString);
	}

	TEST(LocateDb, successful_load)
	{
		std::vector<char> testPayload({ '\0', 'm', 'l', 'o', 'c', 'a', 't', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '/', 'r',
			'\0', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x01', '\x02', '\x03', '\x04', '\0', '\0', '\0', '\0',
			'd', 'i', 'r', '1', '\0', '\x01', 's', 'u', 'b', '1', '\0', '\x01', 's', 'u', 'b', '2', '\0', '\0', 'f', 'i', 'l', 'e', '1',
			'\0', '\0', 'f', 'i', 'l', 'e', '2', '\0', '\x02', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x01', '\x02',
			'\x03', '\x04', '\0', '\0', '\0', '\0', 'd', 'i', 'r', '2', '\0', '\0', 's', 'f', 'i', 'l', 'e', '1', '\0', '\x01', 's', 's',
			'u', 'b', '1', '\0', '\0', 's', 'f', 'i', 'l', 'e', '2', '\0', '\x01', 's', 's', 'u', 'b', '2', '\0', '\x02' });

		FileTestData data(testPayload);
		LocateDb subject(data.fileName());
		std::vector<std::string> results;
		subject.load([& results](FileEntryType type, std::string root, std::string object)
		{
			std::string result;

			switch (type)
			{
			case FileEntryType::NON_DIRECTORY:
				result = "file:";
				break;
			case FileEntryType::SUBDIRECTORY:
				result = "dir:";
				break;
			}

			result += root + '/' + object;
			results.push_back(result);
		});

		EXPECT_EQ(8, results.size());
		EXPECT_EQ("dir:dir1/sub1", results[0]);
		EXPECT_EQ("dir:dir1/sub2", results[1]);
		EXPECT_EQ("file:dir1/file1", results[2]);
		EXPECT_EQ("file:dir1/file2", results[3]);
		EXPECT_EQ("file:dir2/sfile1", results[4]);
		EXPECT_EQ("dir:dir2/ssub1", results[5]);
		EXPECT_EQ("file:dir2/sfile2", results[6]);
		EXPECT_EQ("dir:dir2/ssub2", results[7]);
	}

}


