#include "pch.h"
#pragma once

namespace graphics
{

class VBO
{
public:
  VBO(uint32_t size, GLenum usage);
  VBO(uint32_t size, void *data, GLenum usage);
  ~VBO();

  void fillBuffer(uint32_t size, void *data);

  void inline bind() const { glCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id)); };
  void inline unbind() const { glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); };

  inline uint32_t getId() const { return m_Id; };
  inline void *getData() const { return m_Data; };
  inline const uint32_t getSize() const { return m_Size; };

private:
  uint32_t m_Id;
  void *m_Data;
  const uint32_t m_Size;
};
} // namespace graphics