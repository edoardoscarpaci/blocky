#include "pch.h"
#pragma once

namespace graphics {

struct Node {
  uint8_t componentCount;
  uint32_t stride;
  util::DataType type;

  Node(uint8_t componentCount, uint32_t stride, util::DataType type)
      : componentCount(componentCount), stride(stride), type(type){};

  Node(uint8_t componentCount)
      : componentCount(componentCount), stride(0),
        type(util::DataType::Dfloat){};
  Node() : componentCount(1), stride(0), type(util::DataType::Dfloat){};

  /*
    Node(uint8_t componentCount, util::DataType type)
        : componentCount(componentCount), type(type){};

    Node(uint8_t componentCount)
        : componentCount(componentCount), type(util::DataType::Dfloat){};

    Node() : componentCount(1), type(util::DataType::Dfloat){};
    */
};

class Buffer {
public:
  Buffer(Node *nodes, uint32_t count, void *data, uint32_t size, GLenum usage);
  Buffer(Node node, void *data, uint32_t size, GLenum usage);

  Buffer(const Buffer &buffer) = default;
  Buffer(Buffer &&buffer) = default;

  ~Buffer();

  inline void bind() const;
  inline void unbind() const;

  void replaceBuffer(Node *nodes, uint32_t count, void *data, uint32_t size,
                     GLenum usage);
  void replaceBuffer(Node node, void *data, uint32_t size, GLenum usage);
  void *getData() const;

  inline uint32_t getId() const { return m_Id; };

  inline Node const *getNode(uint32_t index) const {
    if (index < m_Nodes.size())
      return &m_Nodes[index];
    return nullptr;
  }

  inline uint32_t getNodeCount() const { return m_Nodes.size(); };

private:
  uint32_t m_Id;
  uint32_t m_Size;
  std::vector<Node> m_Nodes;
};

} // namespace graphics