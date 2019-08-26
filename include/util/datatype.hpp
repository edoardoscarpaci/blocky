#pragma once
#include "pch.h"

namespace util {

enum class DataType { Dint, Dfloat, Dbyte, Dbool, DuInt, DuByte };

class DataTypeManager {
public:
  DataTypeManager(DataType type);

  DataTypeManager(const DataTypeManager &d) = default;
  DataTypeManager(DataTypeManager &&d) = delete;

  inline GLenum getGLType() const { return m_GlType; };
  inline uint8_t getSizeof() const { return m_TypeSize; };
  inline const DataType getType() const { return m_Type; };

private:
  DataType m_Type;
  GLenum m_GlType;
  uint8_t m_TypeSize;
};

}