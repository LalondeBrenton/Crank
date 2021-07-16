#include "pch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Crank
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	bool Log::m_Initialized = false;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("CRANK");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
		m_Initialized = true;
	}

	void Log::Init(const std::string& filename)
	{
		std::string path = filename.substr(0, filename.size() - 4);
		std::string extension = filename.substr(filename.size() - 4, filename.size());
		s_CoreLogger = spdlog::basic_logger_mt("CRANK", path + "-CORE" + extension);
		s_ClientLogger = spdlog::basic_logger_mt("CLIENT", path + "-CLIENT" + extension);
		m_Initialized = true;
	}
}