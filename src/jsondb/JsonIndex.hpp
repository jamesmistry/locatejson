#ifndef JSONINDEX_HPP_
#define JSONINDEX_HPP_

#include <fstream>
#include <cstdint>

namespace locj
{

	/*!
	 * @class JsonIndex
	 *
	 * Writes a JSON file index to file.
	 */
	class JsonIndex
	{

	public:
		/*!
		 * Constructor.
		 *
		 * @param[in]	filename	Name of the file to write the JSON to
		 * @param[in]	hostname	Contents of the index hostname field in the written data
		 */
		explicit JsonIndex(std::ostream & out, std::string hostname);
		JsonIndex(const JsonIndex & rhs) = delete;
		JsonIndex(const JsonIndex && rhs) = delete;

		~JsonIndex();

		/*!
		 * Write an entry to the JSON index.
		 *
		 * @param[in]	path		Path to the file that is the subject of the entry
		 * @param[in]	filename	Name of the file that is the subject of the entry
		 */
		void entry(bool file, const std::string & path, const std::string & name);

		JsonIndex & operator=(const JsonIndex & rhs) = delete;
		JsonIndex & operator=(const JsonIndex && rhs) = delete;

	private:
		/*!
		 * Write the leading file bytes.
		 *
		 * @param[in]	hostname	Contents of the index hostname field
		 */
		void indexHeader(const std::string & hostname);

		/*!
		 * Write the trailing file bytes.
		 */
		void indexFooter();

		std::string m_hostname; //!< Hostname field contents
		std::uint64_t m_numEntries; //!< Number of entries in the index
		std::ostream & m_output; //!< Output stream

	};

}

#endif /* JSONINDEX_HPP_ */
