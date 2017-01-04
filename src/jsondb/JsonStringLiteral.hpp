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
	 * http://www.json.org/).
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
		JsonStringLiteral(const JsonStringLiteral && rhs);

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
