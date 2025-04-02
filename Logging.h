#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "spdlog\spdlog.h"
#include "spdlog\sinks\basic_file_sink.h"
#include "spdlog\sinks\stdout_color_sinks.h"

namespace PackageInstaller {
	class Logging
	{
	public:

		Logging();

		void CustomLogger(const char* Kernel_Log = nullptr, spdlog::level::level_enum Log_Level = spdlog::level::off, const char* User_Log = nullptr, spdlog::level::level_enum User_Log_Level = spdlog::level::off);


	private:
		std::shared_ptr<spdlog::logger>KernelLog = std::make_shared<spdlog::logger>("KERNEL_LOG");
		std::shared_ptr<spdlog::logger>UserLog = std::make_shared<spdlog::logger>("USER_LOG");
	};
}

