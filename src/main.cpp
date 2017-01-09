/*!
 * @file main.cpp
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

#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <limits.h>
#include <cstring>

#include "tclap/CmdLine.h"
#include "main.hpp"
#include "appConfig.h"
#include "exceptions.hpp"
#include "jsondb/JsonIndex.hpp"
#include "locatedb/LocateDb.hpp"

static void parseArguments(int argc, char * argv[], locj::Config & config);
static void convert(std::ostream & outputStream, const locj::Config & config);

static void parseArguments(int argc, char * argv[], locj::Config & config)
{

	std::stringstream versionStr;
	versionStr << APP_VERSION_MAJOR << "." << APP_VERSION_MINOR << "." << APP_VERSION_REL;

	TCLAP::CmdLine cmd("Convert an mlocate database to JSON.", ' ', versionStr.str());

	TCLAP::ValueArg<std::string> inputArg("i", "input", "Filename of the database to convert. If ommitted, `/var/lib/mlocate/mlocate.db` is used.", false, "/var/lib/mlocate/mlocate.db", "filename");
	TCLAP::ValueArg<std::string> outputArg("o", "output", "Filename of the JSON file to write. If ommitted, standard output is used.", false, "-", "filename");
	TCLAP::ValueArg<std::string> hostnameArg("n", "hostname", "Hostname to associate with the file entries in the converted JSON. If ommitted, the current host's name is used.", false, "", "string");
	cmd.add(inputArg);
	cmd.add(outputArg);
	cmd.add(hostnameArg);

	cmd.parse(argc, argv);

	if (outputArg.isSet())
	{
		config.m_outputFilename = outputArg.getValue();
	}
	else
	{
		config.m_outputFilename.clear();
	}

	config.m_inputFilename = inputArg.getValue();

	if (hostnameArg.isSet())
	{
		config.m_hostname = hostnameArg.getValue();
	}
	else
	{
		// No hostname has been specified - use the current system's
		char currentHostname[HOST_NAME_MAX];
		memset(&(currentHostname[0]), 0, sizeof(currentHostname));
		if (gethostname(&(currentHostname[0]), sizeof(currentHostname)) != 0)
		{
			throw locj::AppException("Unable to determine hostname - try specifying one on the command-line using " + hostnameArg.getFlag());
		}
		else
		{
			config.m_hostname = std::string(&(currentHostname[0]));
		}
	}
}

static void convert(std::ostream & outputStream, const locj::Config & config)
{
	locj::JsonIndex output(outputStream, config.m_hostname);
	locj::LocateDb input(config.m_inputFilename);

	input.load([& output](locj::FileEntryType type, std::string path, std::string name)
				{
					output.entry((type == locj::FileEntryType::NON_DIRECTORY), path, name);
				});
}

int main(int argc, char * argv[])
{

	int returnVal = EXIT_SUCCESS;

	try
	{
		locj::Config config;
		parseArguments(argc, argv, config);

		std::ostream outputStream(std::cout.rdbuf());
		std::ofstream outputFile;

		if (config.m_outputFilename.size() > 0)
		{
			outputFile.open(config.m_outputFilename);
			outputStream.rdbuf(outputFile.rdbuf());
		}

		if (outputStream.fail())
		{
			throw locj::FileOpenError(config.m_outputFilename);
		}

		convert(outputStream, config);

	}
	catch(TCLAP::ArgException & e)
	{
		std::cerr << "Argument error: " << e.error() << " for argument " << e.argId() << "\n";
		returnVal = EXIT_FAILURE;
	}
	catch (locj::AppException & e)
	{
		std::cerr << e.what() << "\n";
		returnVal = EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unexpected fatal error\n";
		returnVal = EXIT_FAILURE;
	}

	return returnVal;

}

