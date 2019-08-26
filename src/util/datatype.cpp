#include "util/datatype.hpp"

namespace util {

DataTypeManager::DataTypeManager(DataType type) : m_Type(type) {
  switch (type) {
  case DataType::DuInt:
    m_GlType = GL_UNSIGNED_INT;
    m_TypeSize = sizeof(uint32_t);
    break;
  case DataType::Dint:
    m_GlType = GL_INT;
    m_TypeSize = sizeof(int32_t);
    break;
  case DataType::Dfloat:
    m_GlType = GL_FLOAT;
    m_TypeSize = sizeof(float);
    break;
  case DataType::DuByte:
    m_GlType = GL_UNSIGNED_BYTE;
    m_TypeSize = sizeof(uint8_t);
    break;
  case DataType::Dbyte:
    m_GlType = GL_BYTE;
    m_TypeSize = sizeof(int8_t);
    break;
  case DataType::Dbool:
    m_GlType = GL_BOOL;
    m_TypeSize = sizeof(bool);
    break;
  default:
    m_GlType = GL_FLOAT;
    m_TypeSize = sizeof(float);
  }
}
} // namespace util