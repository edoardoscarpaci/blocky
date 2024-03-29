#include "pch.h"
#pragma once

using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

struct Vertex
{
  Vector3 position;
  Vector2 uv;

  Vertex(const Vector3 &pos, const Vector2 &uv) : position(pos), uv(uv){};
  Vertex(){};
};
