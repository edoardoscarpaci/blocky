#include "pch.h"
#pragma once
#include "renderable.hpp"
#include "texture.hpp"
namespace graphics
{

class Cube : public Renderable
{
public:
  Cube(Vector3 position);
  Cube(float x, float y, float z);

  Cube(Vector3 position, Texture tex);

  void addTexture(Texture tex);
  virtual ~Cube();

  void setScale(const Vector3 &scale);
  void setRotation(const Vector3 &scale);
  void setPosition(const Vector3 &scale);

private:
  Texture m_Texture;
  Vector3 m_Position;
};

} // namespace graphics