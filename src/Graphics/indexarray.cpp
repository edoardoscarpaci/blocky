#include "Graphics/indexarray.hpp"

namespace graphics {
Ibo::Ibo(uint32_t count, GLenum usage) {
  m_Indices.reserve(count);
  glCall(glGenBuffers(1, &m_Id));
  bind();
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t),
                      nullptr, usage));
  unbind();
}

Ibo::Ibo(uint32_t *indices, uint32_t count, GLenum usage) {
  m_Indices.reserve(count);
  std::copy(indices, indices + count, std::back_inserter(m_Indices));
  glCall(glGenBuffers(1, &m_Id));
  bind();
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t),
                      indices, usage));
  unbind();
}

Ibo::~Ibo() { glCall(glDeleteBuffers(1, &m_Id)); }

void Ibo::fillIbo(uint32_t count, uint32_t *indices) {
  void *mydata;
  if (count <= m_Indices.max_size()) {
    std::memcpy(m_Indices.data(), indices,
                count); // Change all memcpy to copy or emplace back
    bind();
    glCallr(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY), mydata);
    std::memcpy(mydata, m_Indices.data(), m_Indices.size());
    glCall(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
    unbind();
  } else {
    std::memcpy(m_Indices.data(), indices, m_Indices.max_size());
    bind();
    glCallr(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY), mydata);
    std::memcpy(mydata, m_Indices.data(), m_Indices.size());
    glCall(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
    unbind();
  }
}

// inline const uint32_t *Ibo::getData() const { return m_Indices.data(); }

inline void Ibo::bind() const {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
}
inline void Ibo::unbind() const {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
} // namespace graphics
