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
