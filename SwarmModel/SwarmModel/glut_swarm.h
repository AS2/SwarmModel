#ifndef __glut_swarm_h__
#define __glut_swarm_h__

#include "glut_manager.h"
#include "boids2d.h"
#include "vec3.h"

class glutSwarm2d : public glutManager {
public:
  glutSwarm2d(int  argc, char* argv[], int w, int h);

  void SetCameraCoord(int &x, int &y, int &z);

  void AddSwarm(int birdsCnt);
};

#endif  // __glut_manager_h__