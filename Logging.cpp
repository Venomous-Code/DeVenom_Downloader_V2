#include "Logging.h"

PackageInstaller::Logging::Logging()
{
	auto CreateSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	//KERNEL LOGGER PROPERTIES
	KernelLog->sinks().push_back(CreateSink);
	KernelLog->set_level(spdlog::level::info);
	KernelLog->set_pattern("%d %b, %Y %^[%l]%$ => %v --- [%n]");

	//USER LOGGER PROPERTIES
	UserLog->sinks().push_back(CreateSink);
	UserLog->set_level(spdlog::level::warn);
	UserLog->set_pattern("%d %b, %Y %^[%l]%$ => %v --- [%n]");
}

void PackageInstaller::Logging::CustomLogger(const char* Kernel_Log, spdlog::level::level_enum Log_Level, const char* User_Log, spdlog::level::level_enum User_Log_Level)
{
	if (Kernel_Log != nullptr)
		KernelLog->log(Log_Level, Kernel_Log);
	if (User_Log != nullptr)
		UserLog->log(User_Log_Level, User_Log);
}

