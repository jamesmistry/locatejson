#ifndef FILETESTDATA_HPP_
#define FILETESTDATA_HPP_

#include <vector>
#include <string>
#include <stdlib.h>
#include <linux/limits.h>
#include <stdexcept>
#include <unistd.h>
#include <fstream>
#include <iostream>

namespace locj
{

	class FileTestData
	{

	public:
		FileTestData(bool preserve = false) : m_preserve(preserve)
		{
			std::vector<char> content;

			createTempFile(content);
		}

		FileTestData(std::vector<char> & content, bool preserve = false) : m_preserve(preserve)
		{
			createTempFile(content);
		}

		~FileTestData()
		{
			if (!m_preserve)
			{
				unlink(m_filePatName.c_str());
			}
		}

		void createTempFile(std::vector<char> & content)
		{
			char tempFileName[PATH_MAX] = { '/', 't', 'm', 'p', '/', 'X', 'X', 'X', 'X', 'X', 'X', '\0' };

			int tempFd = mkstemp(&(tempFileName[0]));
			if (tempFd == -1)
			{
				throw std::runtime_error("Failed to create temporary file");
			}
			else
			{
				m_filePatName = std::string(&(tempFileName[0]));

				ssize_t bytesToWrite = content.size();
				while (bytesToWrite > 0)
				{
					ssize_t bytesWritten = write(tempFd, content.data() + (content.size() - bytesToWrite), bytesToWrite);
					if (bytesWritten == -1)
					{
						throw std::runtime_error("Failed to write to temporary file");
					}
					else
					{
						bytesToWrite -= bytesWritten;
					}
				}

				close(tempFd);
			}
		}

		bool contains(std::string data) const
		{
			std::ifstream fileStream(m_filePatName);
			fileStream.seekg(0, std::ios::end);
			auto sz = fileStream.tellg();
			fileStream.seekg(0, std::ios::beg);

			std::string contents;
			contents.resize(sz);
			fileStream.read(&contents[0], sz);

			if (data != contents)
			{
				std::cout << "Expected size: " << data.size() << "\n";
				std::cout << "Actual size: " << contents.size() << "\n";
				std::cout << "Expected: " << data << "\n\n";
				std::cout << "Actual:   " << contents << "\n\n";
				return false;
			}
			else
			{
				return true;
			}
		}

		std::string fileName() const
		{
			return m_filePatName;
		}

	private:
		bool m_preserve;
		std::string m_filePatName;

	};

}

#endif /* FILETESTDATA_HPP_ */
