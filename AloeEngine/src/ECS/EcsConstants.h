#ifndef _ECS_CONSTANTS_H_
#define _ECS_CONSTANTS_H_ 1

#include <bitset>

#define MAX_COMPONENTS 32
#define MAX_ENTITIES 1000

namespace Aloe {

  typedef uint32_t Entity;
  typedef std::bitset<MAX_COMPONENTS> Signature;
  typedef uint8_t ComponentType;

}

#endif