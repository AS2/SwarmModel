#ifndef __boids_2d_h__
#define __boids_2d_h__

#include <vector>
#include "vec2.h"

#define MATH_PI 3.14159265358979
#define BOID_SPEED 0.00005
#define SWARM_RAD 0.1

class boid {
private:
  vec2 pos, velocity;
public:
  boid() : pos(vec2()), velocity(vec2()) {};
  boid(vec2 newPos, vec2 newDir) : pos(newPos), velocity(newDir) {};

  void UpdateBird(vec2 newVel) {
    velocity = newVel;
    pos = pos + velocity * BOID_SPEED;
  };

  vec2 GetPos() { return pos; };
  vec2 GetVel() { return velocity; };

  friend class swarm;
};

class swarm {
private:
  void InitSwarm(int boidsCnt);

  int isNearLeftBorder(boid boidToCheck) { return boidToCheck.pos.getX() - SWARM_RAD < -1 ? 1 : 0; }
  int isNearRightBorder(boid boidToCheck) { return boidToCheck.pos.getX() + SWARM_RAD > 1 ? 2 : 0; }
  int isNearTopBorder(boid boidToCheck) { return boidToCheck.pos.getY() + SWARM_RAD > 1 ? 4 : 0; }
  int isNearBottomBorder(boid boidToCheck) { return boidToCheck.pos.getY() - SWARM_RAD < -1 ? 8 : 0; }

  int is—rossedLeftBorder(boid boidToCheck) { return boidToCheck.pos.getX() < -1 ? 1 : 0; }
  int is—rossedRightBorder(boid boidToCheck) { return boidToCheck.pos.getX() > 1 ? 2 : 0; }
  int is—rossedTopBorder(boid boidToCheck) { return boidToCheck.pos.getY() > 1 ? 4 : 0; }
  int is—rossedBottomBorder(boid boidToCheck) { return boidToCheck.pos.getY() < -1 ? 8 : 0; }

  void TeleportBoid(int boidIndex);

  void UpdateBoidsVecInZone(std::vector<int> &medianCnt, std::vector<vec2> &medianPos, std::vector<vec2> &avoidVel, std::vector<vec2> &averageDir, int boidIndex, int zoneIndex = -1);
public:
  // true boids, which would be drawed on screen
  std::vector<boid> boids_on_screen;
  // fake boids to truerly 
  std::vector<std::vector<boid>> boids_near_screen;

  swarm() {};
  swarm(int boidsCnt) { InitSwarm(boidsCnt); };

  void UpdateSwarm(void) {
    std::vector<int> medianCnt(boids_on_screen.size(), 0);
    std::vector<vec2> medianPos(boids_on_screen.size(), vec2());
    std::vector<vec2> avoidVel(boids_on_screen.size(), vec2());
    std::vector<vec2> averageDir(boids_on_screen.size(), vec2());

    for (int i = 0; i < boids_on_screen.size(); i++) {
      UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, -1);

      switch (isNearRightBorder(boids_on_screen[i]) + isNearLeftBorder(boids_on_screen[i]) +
              isNearLeftBorder(boids_on_screen[i])  + isNearBottomBorder(boids_on_screen[i])) {
      case 0:
        break;
      case 6:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 0);
        break;
      case 2:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 1);
        break;
      case 10:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 2);
        break;
      case 8:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 3);
        break;
      case 9:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 4);
        break;
      case 1:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 5);
        break;
      case 5:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 6);
        break;
      case 4:
        UpdateBoidsVecInZone(medianCnt, medianPos, avoidVel, averageDir, i, 7);
        break;
      }
    }

    for (int i = 0; i < boids_on_screen.size(); i++) {
      vec2 newVelocity = boids_on_screen[i].velocity;

      if (medianCnt[i] != 0) {
        newVelocity = newVelocity + ((medianPos[i]  * (1.0f / medianCnt[i]) - boids_on_screen[i].pos) * (0.23f * (rand() / (RAND_MAX + 1) - 0.1))) +
                                     (avoidVel[i]   * (1.0f / medianCnt[i])) + 
                                     (averageDir[i] * (1.0f / medianCnt[i] * (0.12 + 0.1 * (rand() / (RAND_MAX + 1) - 0.5))));
      }

      boids_on_screen[i].UpdateBird(newVelocity.normal());

      for (int j = 0; j < 8; j++) {
        boids_near_screen[j][i].UpdateBird(newVelocity.normal());
      }

      TeleportBoid(i);
    }
  };

  void ResetSwarm() {
    int boidsCnt = boids_on_screen.size();

    InitSwarm(boidsCnt);
  };
};

#endif // __birds_manager_h__