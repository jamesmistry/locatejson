/*!
 * @file JsonIndex.hpp
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
