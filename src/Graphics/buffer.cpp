#include "Graphics/buffer.hpp"

namespace graphics {

Buffer::Buffer(Node *nodes, uint32_t count, void *data, uint32_t size,
               GLenum usage)
    : m_Size(size) {
  m_Nodes.reserve(count);
  std::copy_n(nodes, count, std::back_inserter(m_Nodes));

  glCall(glGenBuffers(1, &m_Id));
  bind();
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
  unbind();
}

Buffer::Buffer(Node node, void *data, uint32_t size, GLenum usage)
    : m_Size(size) {

  m_Nodes.emplace_back(node);
  glCall(glGenBuffers(1, &m_Id));
  bind();
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
  unbind();
}

Buffer::~Buffer() { glCall(glDeleteBuffers(1, &m_Id)); }

void *Buffer::getData() const {
  void *data;
  void *mydata = new uint8_t[m_Size];
  bind();
  glCallr(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY), data);
  std::memcpy(mydata, data, m_Size);
  glCall(glUnmapBuffer(GL_ARRAY_BUFFER));
  unbind();

  return mydata;
}

void Buffer::replaceBuffer(Node *nodes, uint32_t count, void *data,
                           uint32_t size, GLenum usage) {
  m_Nodes.resize(count);
  std::copy_n(nodes, count, std::back_inserter(m_Nodes));
  if (m_Size == size) {
    bind();
    glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data));
    unbind();
  } else {
    m_Size = size;
    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    unbind();
  }
}

void Buffer::replaceBuffer(Node node, void *data, uint32_t size, GLenum usage) {
  m_Nodes.resize(1);
  m_Nodes.emplace_back(node);

  if (m_Size == size) {
    bind();
    glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data));
    unbind();
  } else {
    m_Size = size;
    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    unbind();
  }
}

inline void Buffer::bind() const {
  glCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
}

inline void Buffer::unbind() const { glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
} // namespace graphics