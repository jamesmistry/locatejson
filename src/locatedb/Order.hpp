/** @file Order.hpp
 *
 * Read unsigned integer data independent of its byte order.
 *
 * @author James Mistry
 * @copyright (c) 2016 James Mistry. Released under the MIT licence.
 */

#ifndef ORDER_HPP_
#define ORDER_HPP_

#include <stdint.h>
#include <iostream>
#include <limits.h>

#if CHAR_BIT != 8
#error Compile Error: Platforms on which chars != octets are not supported.
#endif

namespace locj
{

	/*!
	 * @class Order
	 * @brief Read unsigned integers into native byte order automatically
	 *
	 * Read 64-, 32- and 16-bit unsigned integers into native byte order
	 * without having to know the host platform's byte order. Reading is
	 * supported from both char arrays and std::istream objects.
	 */
	class Order
	{

	public:
		static uint64_t big64(std::istream & stream)
		{
			char raw[8];
			stream.read(&(raw[0]), 8);

			return big64(reinterpret_cast<unsigned char *>(&(raw[0])));
		}

		static uint32_t big32(std::istream & stream)
		{
			char raw[4];
			stream.read(&(raw[0]), 4);

			return big32(reinterpret_cast<unsigned char *>(&(raw[0])));
		}

		static uint16_t big16(std::istream & stream)
		{
			char raw[2];
			stream.read(&(raw[0]), 2);

			return big16(reinterpret_cast<unsigned char *>(&(raw[0])));
		}

		static uint64_t little64(std::istream & stream)
		{
			char raw[8];
			stream.read(&(raw[0]), 8);

			return little64(reinterpret_cast<unsigned char *>(&(raw[0])));
		}

		static uint32_t little32(std::istream & stream)
		{
			char raw[4];
			stream.read(&(raw[0]), 4);

			return little32(reinterpret_cast<unsigned char *>(&(raw[0])));
		}

		static uint16_t little16(std::istream & stream)
		{
			char raw[2];
			stream.read(&(raw[0]), 2);

			return little16(reinterpret_cast<unsigned char *>(&(raw[0])));
		}

		static uint64_t big64(unsigned char * val)
		{
			return static_cast<uint64_t>((static_cast<uint64_t>(val[7]) << 0)
					| (static_cast<uint64_t>(val[6]) << 8)
					| (static_cast<uint64_t>(val[5]) << 16)
					| (static_cast<uint64_t>(val[4]) << 24)
					| (static_cast<uint64_t>(val[3]) << 32)
					| (static_cast<uint64_t>(val[2]) << 40)
					| (static_cast<uint64_t>(val[1]) << 48)
					| (static_cast<uint64_t>(val[0]) << 56));
		}

		static uint32_t big32(unsigned char * val)
		{
			return static_cast<uint32_t>((static_cast<uint32_t>(val[3]) << 0)
					| (static_cast<uint32_t>(val[2]) << 8)
					| (static_cast<uint32_t>(val[1]) << 16)
					| (static_cast<uint32_t>(val[0]) << 24));
		}

		static uint16_t big16(unsigned char * val)
		{
			return static_cast<uint16_t>((static_cast<uint16_t>(val[1]) << 0)
					| (static_cast<uint16_t>(val[0]) << 8));
		}

		static uint64_t little64(unsigned char * val)
		{
			return static_cast<uint64_t>((static_cast<uint64_t>(val[0]) << 0)
					| (static_cast<uint64_t>(val[1]) << 8)
					| (static_cast<uint64_t>(val[2]) << 16)
					| (static_cast<uint64_t>(val[3]) << 24)
					| (static_cast<uint64_t>(val[4]) << 32)
					| (static_cast<uint64_t>(val[5]) << 40)
					| (static_cast<uint64_t>(val[6]) << 48)
					| (static_cast<uint64_t>(val[7]) << 56));
		}

		static uint32_t little32(unsigned char * val)
		{
			return static_cast<uint32_t>((static_cast<uint32_t>(val[0]) << 0)
					| (static_cast<uint32_t>(val[1]) << 8)
					| (static_cast<uint32_t>(val[2]) << 16)
					| (static_cast<uint32_t>(val[3]) << 24));
		}

		static uint16_t little16(unsigned char * val)
		{
			return static_cast<uint16_t>((static_cast<uint16_t>(val[0]) << 0)
					| (static_cast<uint16_t>(val[1]) << 8));
		}

	};

}

#endif /* ORDER_HPP_ */
