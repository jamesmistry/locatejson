#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <string>

namespace locj
{

	/*!
	 * @struct Config
	 *
	 * Configuration data provided by the user on the command-line.
	 */
	struct Config
	{
		std::string m_inputFilename; //!< mlocate database to convert
		std::string m_outputFilename; //!< JSON file to write the converted database to
		std::string m_hostname; //!< The hostname to use in the converted JSON
	};

}

#endif /* MAIN_HPP_ */
