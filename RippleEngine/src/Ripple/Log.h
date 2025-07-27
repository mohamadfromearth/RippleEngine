#pragma once

#include "Core.h";
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"



namespace Ripple {


	class RIPPLE_API Log
	{
	
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


	};
}

#define RP_CORE_ERROR(...) ::Ripple::Log::GetCoreLogger()->error(__VA_ARGS__);
#define RP_CORE_INFO(...) ::Ripple::Log::GetCoreLogger()->info(__VA_ARGS__);
#define RP_CORE_WARN(...) ::Ripple::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define RP_CORE_TRACE(...) ::Ripple::Log::GetCoreLogger()->trace(__VA_ARGS__);

#define RP_CLIENT_ERROR(...) ::Ripple::Log::GetClientLogger()->error(__VA_ARGS__);
#define RP_CLIENT_INFO(...) ::Ripple::Log::GetCClientLogger()->info(__VA_ARGS__);
#define RP_CLIENT_WARN(...) ::Ripple::Log::GetCClientLogger()->warn(__VA_ARGS__);
#define RP_CLIENT_TRACE(...) ::Ripple::Log::GetClientLogger()->trace(__VA_ARGS__);


