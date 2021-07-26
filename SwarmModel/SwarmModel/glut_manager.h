#ifndef __glut_manager_h__
#define __glut_manager_h__

#include <ctime>

#include "lib/glut/include/GL/glew.h"
#include "lib/glut/include/GL/freeglut.h"

class glutManager {
public:
  glutManager() {};
  glutManager(int argc, char *argv[], int w, int h);

  void Start(void);
};

#endif  // __glut_manager_h__
