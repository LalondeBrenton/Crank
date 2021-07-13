#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Crank
{
	struct Logs
	{
		std::shared_ptr<spdlog::logger> Core;
		std::shared_ptr<spdlog::logger> Client;

		Logs(std::shared_ptr<spdlog::logger> core, std::shared_ptr<spdlog::logger> client)
			:Core(core), Client(client) {}

	};

	class Log
	{
	public:
		static void Init();
		static void Init(const Logs& logs);

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		static Logs& GetLogs() { return Logs(s_CoreLogger ,s_ClientLogger); }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define CGE_CORE_TRACE(...)    ::Crank::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CGE_CORE_INFO(...)     ::Crank::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CGE_CORE_WARN(...)     ::Crank::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CGE_CORE_ERROR(...)    ::Crank::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CGE_CORE_CRITICAL(...) ::Crank::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define CGE_TRACE(...)         ::Crank::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CGE_INFO(...)          ::Crank::Log::GetClientLogger()->info(__VA_ARGS__)
#define CGE_WARN(...)          ::Crank::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CGE_ERROR(...)         ::Crank::Log::GetClientLogger()->error(__VA_ARGS__)
#define CGE_CRITICAL(...)      ::Crank::Log::GetClientLogger()->critical(__VA_ARGS__)