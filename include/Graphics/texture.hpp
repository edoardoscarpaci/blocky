#include "pch.h"
#pragma once

namespace graphics
{

class Texture
{
public:
    Texture(const std::string &path);
    Texture();

    void open(const std::string &path);
    inline uint32_t getId() const { return m_Id; };

    inline void bind() const;
    inline void unbind() const;

private:
    std::tuple<uint8_t *, uint32_t, uint32_t> readPng(const std::string &path);
    uint32_t m_Id;
};
} // namespace graphics