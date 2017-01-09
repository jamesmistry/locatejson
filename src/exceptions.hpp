/*!
 * @file exceptions.hpp
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

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <stdexcept>
#include <string>

namespace locj
{

	class AppException : public std::runtime_error
	{
	public:
		AppException(std::string description) : std::runtime_error(description.c_str())
		{
		}

	};

	class FileOpenError : public AppException
	{
	public:
		FileOpenError(std::string filename) : AppException("Error opening file " + filename + ". Check the file exists and you have permissions to read it")
		{
		}

	};

	class FileReadError : public AppException
	{
	public:
		FileReadError(std::string filename) : AppException("Error reading from file " + filename)
		{
		}

	};

	class FileWriteError : public AppException
	{
	public:
		FileWriteError(std::string filename) : AppException("Error writing to file " + filename)
		{
		}

	};

	class InvalidUpdateDb : public AppException
	{
	public:
		InvalidUpdateDb(std::string description) : AppException(description)
		{
		}

	};

	class TruncatedFileHeader : public InvalidUpdateDb
	{
	public:
		TruncatedFileHeader() : InvalidUpdateDb("Database file appears to be truncated")
		{
		}

	};

	class BadMagicNumber : public InvalidUpdateDb
	{
	public:
		BadMagicNumber() : InvalidUpdateDb("Unrecognised database format")
		{
		}

	};

	class InvalidConfigBlockSize : public InvalidUpdateDb
	{
	public:
		InvalidConfigBlockSize() : InvalidUpdateDb("Config block size is too large")
		{
		}

	};

	class UnsupportedDatabaseVersion : public InvalidUpdateDb
	{
	public:
		UnsupportedDatabaseVersion() : InvalidUpdateDb("Unsupported database format version")
		{
		}

	};

	class TruncatedConfigBlock : public InvalidUpdateDb
	{
	public:
		TruncatedConfigBlock() : InvalidUpdateDb("Configuration block appears to be truncated")
		{
		}

	};

	class TruncatedDirHdr : public InvalidUpdateDb
	{
	public:
		TruncatedDirHdr() : InvalidUpdateDb("Directory entry appears to be truncated")
		{
		}

	};

	class BadFileEntryType : public InvalidUpdateDb
	{
	public:
		BadFileEntryType() : InvalidUpdateDb("Unexpected file entry type")
		{
		}

	};

	class TruncatedDbString : public InvalidUpdateDb
	{
	public:
		TruncatedDbString() : InvalidUpdateDb("String object appears to be truncated")
		{
		}

	};

	class OversizeDbString : public InvalidUpdateDb
	{
	public:
		OversizeDbString() : InvalidUpdateDb("Database string object exceeds maximum permitted size")
		{
		}

	};

}

#endif /* EXCEPTIONS_HPP_ */
