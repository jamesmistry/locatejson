#include <string>

#include "jsondb/JsonStringLiteral.hpp"

namespace locj
{

	JsonStringLiteral::JsonStringLiteral(const std::string & data)
	{
		literalise(data, m_result);
	}

	JsonStringLiteral::JsonStringLiteral(const char * data)
	{
		std::string strData(data);

		literalise(strData, m_result);
	}

	JsonStringLiteral::operator const char * () const
	{
		return m_result.c_str();
	}

	void JsonStringLiteral::literalise(const std::string & in, std::string & out)
	{
		out.push_back('"');

		for (auto c : in)
		{
			switch(c)
			{
			case '"':
			case '\\':
			case '/':
				// Must be escaped
				out.push_back('\\');
				out.push_back(c);
				break;
			case 8: // Backspace
				out.push_back('\\');
				out.push_back('b');
				break;
			case 9: // Horizontal tab
				out.push_back('\\');
				out.push_back('t');
				break;
			case 10: // Line feed
				out.push_back('\\');
				out.push_back('n');
				break;
			case 12: // Form feed
				out.push_back('\\');
				out.push_back('f');
				break;
			case 13: // Carriage return
				out.push_back('\\');
				out.push_back('r');
				break;
			default:
				out.push_back(c);
				break;
			}
		}

		out.push_back('"');
	}

}
