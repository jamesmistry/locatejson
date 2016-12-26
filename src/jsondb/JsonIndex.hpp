#ifndef JSONINDEX_HPP_
#define JSONINDEX_HPP_

#include <fstream>
#include <stdint.h>

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
		JsonIndex(std::ostream & out, std::string hostname);

		~JsonIndex();

		/*!
		 * Write an entry to the JSON index.
		 *
		 * @param[in]	path		Path to the file that is the subject of the entry
		 * @param[in]	filename	Name of the file that is the subject of the entry
		 */
		void entry(bool file, const std::string & path, const std::string & name);

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
		uint64_t m_numEntries; //!< Number of entries in the index
		std::ostream & m_output; //!< Output stream

	};

}

#endif /* JSONINDEX_HPP_ */
