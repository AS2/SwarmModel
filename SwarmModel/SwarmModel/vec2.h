#ifndef __VEC2_H__
#define __VEC2_H__

#include <math.h>

class vec2 {
private:
  double X, Y;

  float fastRevSqrt(float number) const {
    int i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));

    return y;
  }
public:
  // constructor #1
  vec2() {
    X = Y = 0;
  }

  // constructor #2
  vec2(double dotX, double dotY) {
    X = dotX;
    Y = dotY;
  }

  // methods
  double getX() const {
    return X;
  }

  double getY() const {
    return Y;
  }

  vec2 normal() const {
    if (X == 0 && Y == 0)
      return vec2(0, 0);

    double length = sqrt(X * X + Y * Y);
    return vec2(X / length, Y / length);
  }

  vec2 fastNormal() const {
    if (X == 0 && Y == 0)
      return vec2(0, 0);

    float length = fastRevSqrt(float(X * X + Y * Y));
    return vec2(X * length, Y * length);
  }

  double vecMul(const vec2& vec) const {
    return X * vec.X + Y * vec.Y;
  }

  double length() const {
    return sqrt(X * X + Y * Y);
  }

  /*
   * operators
   */
  vec2 operator+(const vec2& vec) const {
    return vec2(X + vec.X, Y + vec.Y);
  }
  vec2 operator-(const vec2& vec) const {
    return vec2(X - vec.X, Y - vec.Y);
  }

  vec2 operator*(double mul) const {
    return vec2(X * mul, Y * mul);
  }

  double operator*(const vec2& vec) const {
    return X * vec.X + Y * vec.Y;
  }

  vec2& operator=(const vec2& vec) {
    if (this == &vec)
      return *this;

    X = vec.X;
    Y = vec.Y;
    return *this;
  }
};

#endif // __VEC2_H__
