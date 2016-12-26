#include <gtest/gtest.h>
#include <string>
#include <fstream>

#include "jsondb/JsonIndex.hpp"
#include "FileTestData.hpp"

namespace locj
{

	TEST(JsonIndex, format)
	{
		FileTestData resultFile;

		{
			std::ofstream resultStream(resultFile.fileName());
			std::ostream out(resultStream.rdbuf());
			JsonIndex subject(out, "test-host");
			subject.entry(true, "/test/path/1", "test-file-1");
			subject.entry(true, "/test/path/1", "test-file-2");
			subject.entry(true, "/test/dir/2", "test-file-3");
			subject.entry(false, "/test/dir/2", "test-subdir-1");
		}

		EXPECT_TRUE(resultFile.contains("{\"host\":\"test-host\",\"entities\":[{\"file\":true,\"path\":\"\\/test\\/path\\/1\",\"name\":\"test-file-1\"},{\"file\":true,\"path\":\"\\/test\\/path\\/1\",\"name\":\"test-file-2\"},{\"file\":true,\"path\":\"\\/test\\/dir\\/2\",\"name\":\"test-file-3\"},{\"file\":false,\"path\":\"\\/test\\/dir\\/2\",\"name\":\"test-subdir-1\"}]}\n"));

	}

}
