#pragma once

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
		void logDuration(size_t size, Milliseconds duration, const std::string& message) override;

	private:
		std::ofstream fileStream_;
	};
}