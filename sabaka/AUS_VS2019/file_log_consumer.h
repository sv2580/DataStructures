
#pragma once
#include <string>

#include "structures/_logger/logger.h"
#include <fstream>


namespace structures

{
	class FileLogConsumer
		: public ILogConsumer
	{
	public:
		FileLogConsumer(const std::string& path);
		void logMessage(LogType type, const std::string& message) override;
		void logDuration(size_t size, DurationType duration, const std::string& message) override;
	public:
		std::ofstream fileStream_;
	};
}