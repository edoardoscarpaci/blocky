#include "pch.h"
#pragma once
#include "renderable.hpp"

namespace graphics {

class Cube : public Renderable {
public:
  Cube(Vector3 position);
  Cube(float x, float y, float z);

  virtual ~Cube();

private:
  Vector3 position;
};

} // namespace graphics