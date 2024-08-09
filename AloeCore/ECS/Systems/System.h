#pragma once

#include <entt.hpp>

namespace Aloe {

	class System {
	public:
		virtual void Init() = 0;
		virtual void Execute() = 0;

		virtual void OnRuntimeStart() = 0;
		virtual void OnRuntimeStop() = 0;
	};
}