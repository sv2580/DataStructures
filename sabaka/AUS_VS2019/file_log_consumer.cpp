#include "file_log_consumer.h"
#include <stdexcept>
#include <iostream>

namespace structures
{
	FileLogConsumer::FileLogConsumer(const std::string& path) :
		fileStream_(path)
	{
		auto mask = fileStream_.exceptions() | std::ios::failbit;
		fileStream_.exceptions(mask);
		if (!fileStream_.is_open())
		{
			throw std::runtime_error("Failed to open file " + path);
		}

		
	}

	void FileLogConsumer::logMessage(LogType type, const std::string& message)
	{
		fileStream_ << logTypeToString(type) << ';' << message << std::endl;
	}

	void FileLogConsumer::logDuration(size_t size, DurationType duration, const std::string& message)
	{
		fileStream_ << logTypeToString(LogType::Duration) << ';'
			<< duration.count() << ';'
			<< message << ';'
			<< std::endl;
	}
}


