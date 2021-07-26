#include <math.h>
#include "glut_manager.h"

static clock_t StartTime = -1, OldTime;
static double totalDeltaTime = 0;
static double deltaTime, syncTime;

static void GM_DisplayFunc(void) {
  clock_t time = clock();

  if (StartTime == -1)
    StartTime = OldTime = time;

  deltaTime = (time - OldTime) / (double)CLOCKS_PER_SEC;
  syncTime = (time - StartTime) / (double)CLOCKS_PER_SEC;
  OldTime = time;
  totalDeltaTime += deltaTime;

  if (totalDeltaTime > 0.01) {
    glClearColor(0.3, 0.5, 0.7, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1, 0, 0);
    glRectd(0, 0, 0.59 * sin(syncTime), 0.30 * cos(syncTime));

    glFinish();
    glutSwapBuffers();
  }

  glutPostRedisplay();
}

static void GM_KeyboardFunc(unsigned char key, int x, int y) {
  if (key == 27)
    exit(0);
}

static void GM_SpecialKeyboardFunc(int key, int x, int y) {
}

glutManager::glutManager(int argc, char* argv[], int w, int h) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);

  glutInitWindowPosition(30, 30);
  glutInitWindowSize(w, h);
  glutCreateWindow("Glut manager window!");

  glutDisplayFunc(GM_DisplayFunc);
  glutKeyboardFunc(GM_KeyboardFunc);
  glutSpecialFunc(GM_SpecialKeyboardFunc);
}

void glutManager::Start(void) {
  glutMainLoop();
}
