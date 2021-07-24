#ifndef __glut_manager_h__
#define __glut_manager_h__

class glutDraw {
public:
  glutDraw(int  argc, int *argv[], int w, int h);

  virtual void KeyboardFunc(unsigned char key, int x, int y);
  virtual void SpecialKeyboardFunc(unsigned char key, int x, int y);

  virtual void DisplayFunc(void);

  virtual void MakeMenu(void);

  virtual void Start(void);
};

#endif  // __glut_manager_h__
