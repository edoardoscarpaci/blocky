#include "Graphics/vbo.hpp"

namespace graphics
{

VBO::VBO(uint32_t size, GLenum usage) : m_Size(size)
{
  glCall(glGenBuffers(1, &m_Id));
  bind();
  glCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage));
  unbind();
  m_Data = new uint8_t[size];
}

VBO::VBO(uint32_t size, void *data, GLenum usage) : m_Size(size)
{
  m_Data = new uint8_t[size];
  std::memcpy(m_Data, data, size);
  glCall(glGenBuffers(1, &m_Id));
  bind();
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
  unbind();
}
VBO::~VBO() { glCall(glDeleteBuffers(1, &m_Id)); }

void VBO::fillBuffer(uint32_t size, void *data)
{
  void *mydata;
  if (size <= m_Size)
  {
    std::memcpy(m_Data, data, size);
    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    /*glCallr(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), mydata);
    std::memcpy(mydata, data, size);
    glCall(glUnmapBuffer(GL_ARRAY_BUFFER));*/
    unbind();
  }
  else
  {
    std::memcpy(m_Data, data, m_Size);
    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    /*glCallr(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), mydata);
    std::memcpy(mydata, data, m_Size);
    glCall(glUnmapBuffer(GL_ARRAY_BUFFER));*/
    unbind();
  }
}

} // namespace graphics