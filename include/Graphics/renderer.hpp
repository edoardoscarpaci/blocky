#include "pch.h"
#pragma once

#include "indexarray.hpp"
#include "vbo.hpp"
#include "vertexarray.hpp"
#include "shader.hpp"
#include "Graphics/camera.hpp"

#define VERTEX_CUBE 8
#define MAX_CUBE_BUFFER_SIZE 1000 * VERTEX_CUBE
#define VERTEX_SIZE sizeof(Vertex)
#define MAX_VERTEX_BUFFER_SIZE MAX_CUBE_BUFFER_SIZE *INDEX_CUBE
#define INDEX_CUBE 36

namespace graphics
{

class Cube;

class Renderer
{
public:
  Renderer(const glm::mat4 projectionMatrix, graphics::Camera *camera);

  // void addRenderable();
  void addCube(Cube &cube);

  void flush();
  void attachCamera(graphics::Camera *camera);

private:
  VBO *m_Vbo;
  Ibo *m_Ibo;
  Vao m_Vao;

  graphics::Camera *m_ActiveCamera;

  Shader *m_Shader;
  uint32_t m_VertexCount;
  std::array<uint8_t, MAX_CUBE_BUFFER_SIZE * VERTEX_SIZE> m_DataBuffer;
  std::array<uint32_t, MAX_VERTEX_BUFFER_SIZE> m_IndicesBuffer;

  glm::mat4 m_ProjectionMatrix;

  void uploadUniform();
};

} // namespace graphics