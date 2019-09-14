#include "pch.h"

#pragma once
#include "indexarray.hpp"
#include "vbo.hpp"

namespace graphics
{

class Renderable
{
public:
  Renderable() : m_Transform(1){};

  inline VBO *const getVBO() const { return m_Vbo; };
  inline Ibo *const getIbo() const { return m_Ibo; };

protected:
  glm::mat4 m_Transform;
  VBO *m_Vbo;
  Ibo *m_Ibo;
};

} // namespace graphics