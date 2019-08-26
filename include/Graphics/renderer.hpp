#include "pch.h"
#pragma once

#include "indexarray.hpp"
#include "vbo.hpp"
#include "vertexarray.hpp"

#define VERTEX_CUBE 8
#define MAX_CUBE_BUFFER_SIZE 1000 * VERTEX_CUBE
#define VERTEX_SIZE sizeof(Vertex)
#define MAX_VERTEX_BUFFER_SIZE MAX_CUBE_BUFFER_SIZE *INDEX_CUBE
#define INDEX_CUBE 24

namespace graphics {

class Cube;

class Renderer {
public:
  Renderer(const glm::mat4 &projectionMatrix);

  // void addRenderable();
  void addCube(Cube *cube);

  void flush();

private:
  VBO *m_Vbo;
  Ibo *m_Ibo;
  Vao m_Vao;

  uint32_t m_Count;
  std::array<uint8_t, MAX_CUBE_BUFFER_SIZE * VERTEX_SIZE> m_DataBuffer;
  std::array<uint32_t, MAX_VERTEX_BUFFER_SIZE> m_IndicesBuffer;

  glm::mat4 m_ProjectionMatrix;
};

} // namespace graphics