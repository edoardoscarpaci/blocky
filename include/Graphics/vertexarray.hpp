#include "pch.h"
#pragma once

namespace graphics
{

class Buffer;
class Vao
{
public:
  Vao();

  ~Vao();

  Vao(const Vao &v) = default;
  Vao(Vao &&v) = default;

  void addBuffer(std::shared_ptr<Buffer> buffer);
  inline std::shared_ptr<Buffer> getBuffer(uint32_t index) const;

  void inline bind() const { glCall(glBindVertexArray(m_Id)); };
  void inline unbind() const { glCall(glBindVertexArray(0)); };
  void inline disableAttrib(uint32_t index);
  void inline enableAttrib(uint32_t index);

  inline uint32_t getId() const { return m_Id; };

private:
  uint32_t m_Id;
  uint32_t m_Index;
  std::vector<std::shared_ptr<Buffer>> m_Buffers;
};
} // namespace graphics
