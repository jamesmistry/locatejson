#include <gtest/gtest.h>
#include <string>

#include "jsondb/JsonStringLiteral.hpp"

namespace locj
{

	TEST(JsonStringLiteral, jsonify_from_str)
	{
		std::string data("x\"\\/\u0008\u0009\u000a\u000c\u000dabc");
		JsonStringLiteral subject(data);
		std::string result(subject);

		EXPECT_EQ("\"x\\\"\\\\\\/\\b\\t\\n\\f\\rabc\"", result);
	}

	TEST(JsonStringLiteral, jsonify_from_cstr)
	{
		std::string data("x\"\\/\u0008\u0009\u000a\u000c\u000dabc");
		JsonStringLiteral subject(data.c_str());
		std::string result(subject);

		EXPECT_EQ("\"x\\\"\\\\\\/\\b\\t\\n\\f\\rabc\"", result);
	}
}
