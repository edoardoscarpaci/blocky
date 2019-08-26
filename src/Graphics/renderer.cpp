#include "Graphics/renderer.hpp"
#include "Graphics/cube.hpp"
#include "Graphics/indexarray.hpp"
namespace graphics {

Renderer::Renderer(const glm::mat4 &projectionMatrix)
    : m_Count(0), m_ProjectionMatrix(projectionMatrix) {

  m_Vbo = new VBO(MAX_VERTEX_BUFFER_SIZE * sizeof(Vertex), GL_DYNAMIC_DRAW);
  m_Ibo = new Ibo(MAX_VERTEX_BUFFER_SIZE * sizeof(uint32_t), GL_DYNAMIC_DRAW);
}

void Renderer::addCube(Cube *cube) {
  VBO *cubeVBO = cube->getVBO();
  Ibo *cubeIbo = cube->getIbo();
  if (m_DataBuffer.size() + cubeVBO->getSize() < m_DataBuffer.max_size()) {

    std::memcpy(m_DataBuffer.end(), cubeVBO->getData(), cubeVBO->getSize());

    const uint32_t *data = cubeIbo->getData();
    uint32_t offset = VERTEX_CUBE * m_Count;

    for (uint32_t i = 0; i < cubeIbo->getCount(); i++) {
      m_IndicesBuffer[i + offset] = *data + offset;
    };

    m_Count += cubeVBO->getSize() / VERTEX_SIZE;

  } else {
    flush();
    std::memcpy(m_DataBuffer.end(), cubeVBO->getData(), cubeVBO->getSize());

    const uint32_t *data = cubeIbo->getData();
    uint32_t offset = VERTEX_CUBE * m_Count;

    for (uint32_t i = 0; i < cubeIbo->getCount(); i++) {
      m_IndicesBuffer[i + offset] = *data + offset;
    };

    m_Count += cubeVBO->getSize();
  }
}

void Renderer::flush() {
  m_Vbo->fillBuffer(m_Count * VERTEX_SIZE, m_DataBuffer.data());
  m_Ibo->fillIbo(m_Count * VERTEX_CUBE, m_IndicesBuffer.data());

  m_Vao.bind();
  m_Vbo->bind();
  m_Ibo->bind();

  glCall(glDrawElements(GL_TRIANGLES, m_Count * INDEX_CUBE, GL_UNSIGNED_INT,
                        nullptr));
  m_Vao.unbind();
  m_Vbo->unbind();
  m_Ibo->bind();
};

} // namespace graphics