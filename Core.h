#pragma once
#include "Windowing.h"
#include "spdlog\spdlog.h"
#include "spdlog\sinks\basic_file_sink.h"
#include "spdlog\sinks\stdout_color_sinks.h"


#define CRITICAL	spdlog::level::critical
#define ERROR		spdlog::level::err
#define WARN		spdlog::level::warn
#define INFO		spdlog::level::info
#define OFF			spdlog::level::off

namespace PackageInstaller {
	class Core
	{
	public:
		void InitializeApplication();

	private:
		Logging Logs;
      //Windowing window;
	};
}
