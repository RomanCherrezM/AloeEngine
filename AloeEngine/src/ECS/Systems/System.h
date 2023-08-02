#ifndef ALOE_SYSTEM_H
#define ALOE_SYSTEM_H 1

#include "ECS/EcsConstants.h"
#include <set>

namespace Aloe {

	class System {
	public:
		virtual void Init() = 0;
		virtual void Execute() = 0;

		std::set<Entity> entities;
	};

}

#endif