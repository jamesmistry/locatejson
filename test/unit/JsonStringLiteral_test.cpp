#include <gtest/gtest.h>
#include <string>

#include "jsondb/JsonStringLiteral.hpp"

namespace locj
{

	TEST(JsonStringLiteral, jsonify_from_str)
	{
		std::string data("x\"\\/\u0008\u0009\u000a\u000c\u000dabc");
		data.push_back('\0');
		data.push_back('\x1f');
		JsonStringLiteral subject(data);
		std::string result(subject);

		EXPECT_EQ("\"x\\\"\\\\\\/\\b\\t\\n\\f\\rabc\\u0000\\u001F\"", result);
	}

	TEST(JsonStringLiteral, jsonify_from_cstr)
	{
		std::string data("x\"\\/\u0008\u0009\u000a\u000c\u000dabc");
		data.push_back('\x1f');
		JsonStringLiteral subject(data.c_str());
		std::string result(subject);

		EXPECT_EQ("\"x\\\"\\\\\\/\\b\\t\\n\\f\\rabc\\u001F\"", result);
	}
}
