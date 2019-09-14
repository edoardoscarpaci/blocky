#include "Graphics/renderer.hpp"
#include "Graphics/cube.hpp"
#include "Graphics/indexarray.hpp"
#include "Graphics/vbo.hpp"
#include "Graphics/vertexarray.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace graphics
{

Renderer::Renderer(const glm::mat4 projectionMatrix, graphics::Camera *camera)
    : m_VertexCount(0), m_ProjectionMatrix(projectionMatrix), m_ActiveCamera(camera)
{

  m_Shader = new Shader("Shader/vertex.shader", "Shader/fragment.shader");
  m_Shader->bind();

  m_Vbo = new VBO(MAX_VERTEX_BUFFER_SIZE * sizeof(Vertex), GL_DYNAMIC_DRAW);
  m_Ibo = new Ibo(MAX_VERTEX_BUFFER_SIZE * sizeof(uint32_t), GL_DYNAMIC_DRAW);

  m_Vao.bind();
  m_Vbo->bind();
  glCall(glEnableVertexAttribArray(0));
  glCall(glEnableVertexAttribArray(1));
  glCall(glVertexAttribPointer(0, 3,
                               GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                               0));
  glCall(glVertexAttribPointer(1, 2,
                               GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                               (void *)12));
  m_Vao.unbind();
  m_Vbo->unbind();
}

void Renderer::addCube(Cube &cube)
{
  VBO *cubeVBO = cube.getVBO();
  Ibo *cubeIbo = cube.getIbo();

  if (m_VertexCount * VERTEX_SIZE + cubeVBO->getSize() < m_DataBuffer.max_size())
  {

    std::memcpy(m_DataBuffer.begin(), cubeVBO->getData(), cubeVBO->getSize());

    const uint32_t *data = cubeIbo->getData();
    uint32_t offset = VERTEX_CUBE * m_VertexCount;

    for (uint32_t i = 0; i < cubeIbo->getCount(); i++)
    {
      m_IndicesBuffer[i + offset] = *(data + i) + offset;
    };

    m_VertexCount += cubeVBO->getSize() / VERTEX_SIZE;
  }
  else
  {
    flush();
    std::memcpy(m_DataBuffer.end(), cubeVBO->getData(), cubeVBO->getSize());

    const uint32_t *data = cubeIbo->getData();
    uint32_t offset = VERTEX_CUBE * m_VertexCount;

    for (uint32_t i = 0; i < cubeIbo->getCount(); i++)
    {
      m_IndicesBuffer[i + offset] = *data + offset;
    };

    m_VertexCount += cubeVBO->getSize();
  }
} // namespace graphics

void Renderer::flush()
{

  m_Vbo->fillBuffer(m_VertexCount * VERTEX_SIZE, m_DataBuffer.data());
  m_Ibo->fillIbo((m_VertexCount / 8) * INDEX_CUBE, m_IndicesBuffer.data());
  m_Vao.bind();
  m_Ibo->bind();
  m_Vbo->bind();

  uploadUniform();
  glCall(glDrawElements(GL_TRIANGLES, (m_VertexCount / 8) * INDEX_CUBE, GL_UNSIGNED_INT, nullptr));

  m_Vao.unbind();
  m_Vbo->unbind();
  m_Ibo->bind();
}

void Renderer::attachCamera(graphics::Camera *camera)
{
  m_ActiveCamera = camera;
}

void Renderer::uploadUniform()
{
  m_Shader->setUniformMat4(m_Shader->getUniform("projection"), m_ProjectionMatrix);
  m_Shader->setUniformMat4(m_Shader->getUniform("view"), m_ActiveCamera->getViewMatrix());
}

} // namespace graphics