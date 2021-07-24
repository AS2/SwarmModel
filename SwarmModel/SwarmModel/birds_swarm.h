#ifndef __birds_manager_h__
#define __birds_manager_h__

#include <list>
#include "vec3.h"

class bird {
private:
  vec3 pos, velocity, acceleration;
public:
  bird(vec3 pos, vec3 dir);

  void UpdateDir();

  friend class swarm;
};

class swarm {
public:
  std::list<bird> birds;

  swarm();
  swarm(int birdsCnt);

  void AddBird();

  void UpdateSwarm(void);

  void ResetSwarm();
};

#endif // __birds_manager_h__