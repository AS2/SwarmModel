#include "glut_swarm.h"


int main(int argc, char* argv[]) {
  glutSwarm2d gl(argc, argv, 600, 300);   // <-- init glut swarm modeler class

  gl.AddSwarm(128);                       // <-- add boids
  gl.Start();                             // <-- start model '?)'

  return 0;
}
