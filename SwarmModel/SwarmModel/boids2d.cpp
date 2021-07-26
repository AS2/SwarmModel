#include "boids2d.h"

void swarm::InitSwarm(int boidsCnt) {
  boids_on_screen = std::vector<boid>(boidsCnt);
  boids_near_screen = std::vector<std::vector<boid>>(8, std::vector<boid>(boidsCnt));

  for (int i = 0; i < boidsCnt; i++) {
    vec2 newBoidPos = vec2(2 * ((1.0 * rand()) / (RAND_MAX + 1) - 0.5), 2 * ((1.0 * rand()) / (RAND_MAX + 1) - 0.5)),
      newBoidVelocity = vec2(0.02 * ((1.0 * rand()) / (RAND_MAX + 1) - 0.5), 0.02 * ((1.0 * rand()) / (RAND_MAX + 1) - 0.5)).normal();

    boids_on_screen[i] = boid(newBoidPos, newBoidVelocity);

    boids_near_screen[0][i] = boid(newBoidPos + vec2(2, 2), newBoidVelocity);
    boids_near_screen[1][i] = boid(newBoidPos + vec2(2, 0), newBoidVelocity);
    boids_near_screen[2][i] = boid(newBoidPos + vec2(2, -2), newBoidVelocity);
    boids_near_screen[3][i] = boid(newBoidPos + vec2(0, -2), newBoidVelocity);
    boids_near_screen[4][i] = boid(newBoidPos + vec2(-2, -2), newBoidVelocity);
    boids_near_screen[5][i] = boid(newBoidPos + vec2(-2, 0), newBoidVelocity);
    boids_near_screen[6][i] = boid(newBoidPos + vec2(-2, 2), newBoidVelocity);
    boids_near_screen[7][i] = boid(newBoidPos + vec2(0, 2), newBoidVelocity);
  }
}

void swarm::TeleportBoid(int boidIndex) {
  vec2 vecToTeleport = vec2();
  switch (isÑrossedRightBorder(boids_on_screen[boidIndex]) + isÑrossedLeftBorder(boids_on_screen[boidIndex]) +
          isÑrossedTopBorder(boids_on_screen[boidIndex])   + isÑrossedBottomBorder(boids_on_screen[boidIndex])) {
    case 0:
      return;
    case 6:
      vecToTeleport = vec2(-2, -2);
      break;
    case 2:
      vecToTeleport = vec2(-2,  0);
      break;
    case 10:
      vecToTeleport = vec2(-2,  2);
      break;
    case 8:
      vecToTeleport = vec2( 0,  2);
      break;
    case 9:
      vecToTeleport = vec2( 2,  2);
      break;
    case 1:
      vecToTeleport = vec2( 2,  0);
      break;
    case 5:
      vecToTeleport = vec2( 2, -2);
      break;
    case 4:
      vecToTeleport = vec2( 0, -2);
      break;
  }

  boids_on_screen[boidIndex].pos = boids_on_screen[boidIndex].pos + vecToTeleport;
  for (int i = 0; i < 8; i++)
    boids_near_screen[i][boidIndex].pos = boids_near_screen[i][boidIndex].pos + vecToTeleport;
}

void swarm::UpdateBoidsVecInZone(std::vector<int>& medianCnt, std::vector<vec2>& medianPos, std::vector<vec2>& avoidVel, std::vector<vec2>& averageDir, int boidIndex, int zoneIndex) {
  std::vector<boid> *boidsZone = nullptr;

  switch (zoneIndex) {
  case -1:
    boidsZone = &boids_on_screen;
    break;
  default:
    boidsZone = &boids_near_screen[zoneIndex];
    break;
  }

  for (int j = 0; j < boidsZone->size(); j++) {
    if (boidIndex != j && ((*boidsZone)[j].pos - boids_on_screen[boidIndex].pos).length() <= SWARM_RAD) {
      medianCnt[boidIndex]++;

      medianPos[boidIndex] = medianPos[boidIndex] + (*boidsZone)[j].pos;
      avoidVel[boidIndex] = avoidVel[boidIndex] + ((*boidsZone)[j].pos - boids_on_screen[boidIndex].pos) * ((SWARM_RAD - 1.0f * (boids_on_screen[j].pos - boids_on_screen[boidIndex].pos).length()) / (SWARM_RAD)) * (-1);
      averageDir[boidIndex] = averageDir[boidIndex] + (*boidsZone)[j].velocity;
    }
  }
}
