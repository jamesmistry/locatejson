#include <iostream>

#include "jsondb/JsonStringLiteral.hpp"
#include "jsondb/JsonIndex.hpp"
#include "exceptions.hpp"

namespace locj
{

	JsonIndex::JsonIndex(std::ostream & out, std::string hostname) : m_hostname(hostname), m_numEntries(0), m_output(out)
	{
		// Enable exceptions on failed file writes
		m_output.exceptions(std::ostream::failbit | std::ostream::badbit);

		indexHeader(hostname);
	}

	JsonIndex::~JsonIndex()
	{
		indexFooter();
	}

	void JsonIndex::indexHeader(const std::string & hostname)
	{
		m_output << '{' << JsonStringLiteral("host") << ":" << JsonStringLiteral(hostname) << "," << JsonStringLiteral("entities") << ":[";
	}

	void JsonIndex::indexFooter()
	{
		m_output << "]}" << std::endl;
	}

	void JsonIndex::entry(bool file, const std::string & path, const std::string & name)
	{
		if (m_numEntries > 0)
		{
			m_output << ',';
		}

		m_output << '{' << JsonStringLiteral("file") << ':' << ((file) ? "true" : "false") << ',' << JsonStringLiteral("path") << ':' << JsonStringLiteral(path) << ',' << JsonStringLiteral("name") << ':' << JsonStringLiteral(name) << '}';

		++m_numEntries;
	}

}
