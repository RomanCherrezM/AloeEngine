#pragma once

#include <entt.hpp>

namespace Aloe {

	class System {
	public:
		virtual void Init() = 0;
		virtual void Execute() = 0;
	};
}