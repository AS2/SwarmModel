#ifndef __glut_swarm_h__
#define __glut_swarm_h__

#include "glut_manager.h"
#include "birds_swarm.h"
#include "vec3.h"

class glutSwarm : public glutDraw {
private:
  vec3 camera_coord;
  swarm birdsSwarm;
public:
  glutSwarm(int  argc, int* argv[], int w, int h);

  void KeyboardFunc(unsigned char key, int x, int y);
  void SpecialKeyboardFunc(unsigned char key, int x, int y);
  void DisplayFunc(void);
  void MakeMenu(void);

  void SetCameraCoord(int &x, int &y, int &z);

  void AddSwarm(int birdsCnt);
  void Start(void);
};

#endif  // __glut_manager_h__