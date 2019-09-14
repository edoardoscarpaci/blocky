#include "Graphics/vertexarray.hpp"
#include "Graphics/buffer.hpp"

namespace graphics
{

Vao::Vao()
{
  glCall(glad_glGenVertexArrays(1, &m_Id));
}

Vao::~Vao() { glCall(glDeleteBuffers(1, &m_Id)); }

void Vao::addBuffer(std::shared_ptr<Buffer> buffer)
{
  bind();
  buffer->bind();
  uint32_t nodeCount = buffer->getNodeCount();

  uint32_t offset = 0;
  for (uint32_t i = 0; i < nodeCount; i++)
  {
    Node const *node = buffer->getNode(i);
    util::DataTypeManager type(node->type);

    glEnableVertexAttribArray(m_Index);
    glCall(glVertexAttribPointer(m_Index++, node->componentCount,
                                 type.getGLType(), GL_FALSE, node->stride,
                                 (void *)offset));

    offset += node->componentCount * type.getSizeof();
  }

  buffer->unbind();
  unbind();
  m_Buffers.emplace_back(buffer);
}

std::shared_ptr<Buffer> Vao::getBuffer(uint32_t index) const
{
  if (index < m_Buffers.size())
  {
    return m_Buffers[index];
  }
  return nullptr;
}

void inline Vao::enableAttrib(uint32_t index)
{
  if (index < m_Index)
    glCall(glEnableVertexAttribArray(index));
}

void inline Vao::disableAttrib(uint32_t index)
{
  if (index < m_Index)
    glCall(glDisableVertexAttribArray(index));
}

} // namespace graphics
