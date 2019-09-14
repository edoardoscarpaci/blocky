#include "pch.h"
#pragma once
namespace graphics
{
class Ibo
{
public:
  Ibo(uint32_t count, GLenum usage);
  Ibo(uint32_t *indices, uint32_t count, GLenum usage);

  Ibo(const Ibo &ibo) = default;
  Ibo(Ibo &&ibo) = default;

  ~Ibo();
  void fillIbo(uint32_t count, uint32_t *indices);

  inline void bind() const
  {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
  };
  inline void unbind() const
  {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  };

  inline const uint32_t *getData() const { return m_Indices.data(); };
  inline const uint32_t getCount() const { return m_Indices.size(); };

private:
  uint32_t m_Id;
  std::vector<uint32_t> m_Indices;
};
} // namespace graphics