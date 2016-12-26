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
		JsonStringLiteral(const std::string & data);

		/*!
		 * Constructor.
		 *
		 * @param[in]	data	Contents of the string literal
		 */
		JsonStringLiteral(const char * data);

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
		void literalise(const std::string & in, std::string & out);

		std::string m_result; //!< The normalised JSON string literal

	};

}

#endif /* JSONSTRINGLITERAL_HPP_ */
