#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Aloe {

	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_logger;
	};

}

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#endif

#define ALOE_TRACE(...)    ::Aloe::Log::GetLogger()->trace(__VA_ARGS__)
#define ALOE_INFO(...)     ::Aloe::Log::GetLogger()->info(__VA_ARGS__)
#define ALOE_WARN(...)     ::Aloe::Log::GetLogger()->warn(__VA_ARGS__)
#define ALOE_ERROR(...)    ::Aloe::Log::GetLogger()->error(__VA_ARGS__)
#define ALOE_CRITICAL(...) ::Aloe::Log::GetLogger()->critical(__VA_ARGS__)

#define ALOE_ASSERT(x, ...)				\
{										\
	if (!x)								\
	{									\
		DEBUG_BREAK();					\
		ALOE_CRITICAL(__VA_ARGS__);		\
	}									\
}