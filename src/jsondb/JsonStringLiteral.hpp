/*!
 * @file JsonStringLiteral.hpp
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

#ifndef JSONSTRINGLITERAL_HPP_
#define JSONSTRINGLITERAL_HPP_

#include <string>

namespace locj
{

	/*!
	 * @class JsonStringLiteral
	 *
	 * Converts a data buffer to a JSON string literal for insertion
	 * directly in JSON data. The string literal representation contains
	 * the source data with leading and trailing double quotes along with
	 * appropriately escaped characters according to standards (see
	 * https://tools.ietf.org/html/rfc7159).
	 */
	class JsonStringLiteral
	{

	public:
		/*!
		 * Constructor.
		 *
		 * @param[in]	data	Contents of the string literal
		 */
		explicit JsonStringLiteral(const std::string & data);

		/*!
		 * Constructor.
		 *
		 * @param[in]	data	Contents of the string literal
		 */
		explicit JsonStringLiteral(const char * data);

		JsonStringLiteral(const JsonStringLiteral & rhs) = default;
		JsonStringLiteral(JsonStringLiteral && rhs);

		JsonStringLiteral & operator=(JsonStringLiteral & rhs) = default;
		JsonStringLiteral & operator=(JsonStringLiteral && rhs);

		/*!
		 * Get a pointer to a null-terminated string containing the JSON string literal,
		 * including leading and terminating double quotes, and appropriately escaped
		 * source characters.
		 */
		operator const char * () const;

	private:
		/*!
		 * Create a JSON-compatible string literal representation of in, and write it to
		 * out.
		 *
		 * @param[in]	in	The string from which to create a JSON string literal
		 * @param[out]	out	The result
		 */
		void literalise(const std::string & in, std::string & out) const;

		/*!
		 * Escape c as a JSON hex escape sequence of the form \uXXXX, where XXXX is a
		 * 32-bit integer in hexadecimal notation, and append it to out.
		 *
		 * @param[in]	c	The character to escape
		 * @param[out]	out	The string to which the escaped character will be appended
		 */
		void escapeAsHex(char c, std::string & out) const;

		std::string m_result; //!< The normalised JSON string literal

	};

}

#endif /* JSONSTRINGLITERAL_HPP_ */
