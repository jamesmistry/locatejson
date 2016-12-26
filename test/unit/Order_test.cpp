#include <gtest/gtest.h>
#include <sstream>

#include "locatedb/Order.hpp"

namespace locj
{

	TEST(Order, big_endian_16)
	{
		std::stringstream data;
		data << "\xa1\xb2";

		EXPECT_EQ(static_cast<uint16_t>(0xa1b2), Order::big16(data));
	}

	TEST(Order, big_endian_32)
	{
		std::stringstream data;
		data << "\xa1\xb2\xc3\xd4";

		EXPECT_EQ(static_cast<uint32_t>(0xa1b2c3d4), Order::big32(data));
	}

	TEST(Order, big_endian_64)
	{
		std::stringstream data;
		data << "\xa1\xb2\xc3\xd4\xe5\xf6\xd7\xc8";

		EXPECT_EQ(static_cast<uint64_t>(0xa1b2c3d4e5f6d7c8), Order::big64(data));
	}

	TEST(Order, little_endian_16)
	{
		std::stringstream data;
		data << "\xa1\xb2";

		EXPECT_EQ(static_cast<uint16_t>(0xb2a1), Order::little16(data));
	}

	TEST(Order, little_endian_32)
	{
		std::stringstream data;
		data << "\xa1\xb2\xc3\xd4";

		EXPECT_EQ(static_cast<uint32_t>(0xd4c3b2a1), Order::little32(data));
	}

	TEST(Order, little_endian_64)
	{
		std::stringstream data;
		data << "\xa1\xb2\xc3\xd4\xe5\xf6\xd7\xc8";

		EXPECT_EQ(static_cast<uint64_t>(0xc8d7f6e5d4c3b2a1), Order::little64(data));
	}

}
