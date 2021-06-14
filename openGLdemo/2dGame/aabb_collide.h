#pragma once

#include "obj.h"

bool CollidesWith(const obj& o1, const obj& o2) {
  if (o1.location.x - o1.scale.x < o2.location.x + o2.scale.x &&
    o1.location.x + o1.scale.x > o2.location.x - o2.scale.x &&
    o1.location.y - o1.scale.y < o2.location.y + o2.scale.y &&
    o1.location.y + o1.scale.y > o2.location.y - o2.scale.y) {
    return true;
  }
  return false;
}
