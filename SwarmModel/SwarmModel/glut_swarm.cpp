#include "glut_swarm.h"

#define BIRD_SIZE 0.025

static clock_t StartTime = -1, OldTime;
static double totalDeltaTime = 0;
static double deltaTime, syncTime;

static swarm boidsSwarm;
static vec3 camera_coord;

static vec3 palette[] = {
  vec3(0.65, 0.2, 0.2),
  vec3(0.65, 0.65, 0.2),
  vec3(0.65, 0.2, 0.65),

  vec3(0.2, 0.65, 0.2),
  vec3(0.2, 0.65, 0.65),

  vec3(0.2, 0.2, 0.65),
};
static int curColor = 0;
static void DrawBird(boid oneBoid) {
  vec3 currentColor = palette[curColor++ % (sizeof(palette) / sizeof(palette[0]))];
  curColor %= boidsSwarm.boids_on_screen.size();

  vec2 boidTail = oneBoid.GetPos(), boidHead = oneBoid.GetPos() + (oneBoid.GetVel()).normal() * BIRD_SIZE;
  glPushMatrix();

  glTranslated(camera_coord.getX(), camera_coord.getY(), camera_coord.getZ());

  glLineWidth(2);
  glBegin(GL_LINES);
    glColor3d(currentColor.getX(), currentColor.getY(), currentColor.getZ());
    glVertex3d(boidTail.getX(), boidTail.getY(), -0.2);
    glColor3d(1, 0.3, 0.3);
    glVertex3d(boidHead.getX(), boidHead.getY(), -0.2);
  glEnd();

  glPopMatrix();
}

static void GS_DisplayFunc(void) {
  clock_t time = clock();

  if (StartTime == -1)
    StartTime = OldTime = time;

  deltaTime = (time - OldTime) / (double)CLOCKS_PER_SEC;
  syncTime = (time - StartTime) / (double)CLOCKS_PER_SEC;
  OldTime = time;
  totalDeltaTime += deltaTime;

  if (totalDeltaTime > 0.01) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < boidsSwarm.boids_on_screen.size(); i++)
      DrawBird(boidsSwarm.boids_on_screen[i]);

    for (int i = 0; i < boidsSwarm.boids_near_screen.size(); i++)
      for (int j = 0; j < boidsSwarm.boids_on_screen.size(); j++)
        DrawBird(boidsSwarm.boids_near_screen[i][j]);

    boidsSwarm.UpdateSwarm();
    glFinish();
    glutSwapBuffers();
  }

  glutPostRedisplay();
}

static void GS_KeyboardFunc(unsigned char key, int x, int y) {
  switch(key) {
  case 'w':
  case 'W':
    camera_coord = camera_coord + vec3(0, -0.05, 0);
    break;
  case 's':
  case 'S':
    camera_coord = camera_coord + vec3(0, +0.05, 0);
    break;
  case 'd':
  case 'D':
    camera_coord = camera_coord + vec3(-0.05, 0, 0);
    break;
  case 'a':
  case 'A':
    camera_coord = camera_coord + vec3(0.05, 0, 0);
    break;
  case 'r':
  case 'R':
    boidsSwarm.ResetSwarm();
    break;
  case 27:
    exit(0);
  }
}

static void GS_SpecialKeyboardFunc(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    camera_coord = camera_coord + vec3(0, 0, -0.05);
    break;
  case GLUT_KEY_DOWN:
    camera_coord = camera_coord + vec3(0, 0, +0.05);
    break;
  }
}

glutSwarm2d::glutSwarm2d(int argc, char* argv[], int w, int h) {
  camera_coord = vec3(0, 0, 0);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);

  glutInitWindowPosition(30, 30);
  glutInitWindowSize(w, h);
  glutCreateWindow("Glut swarm window!");

  glutDisplayFunc(GS_DisplayFunc);
  glutKeyboardFunc(GS_KeyboardFunc);
  glutSpecialFunc(GS_SpecialKeyboardFunc);
}

void glutSwarm2d::SetCameraCoord(int& x, int& y, int& z) {
}

void glutSwarm2d::AddSwarm(int birdsCnt) {
  boidsSwarm = swarm(birdsCnt);
}
