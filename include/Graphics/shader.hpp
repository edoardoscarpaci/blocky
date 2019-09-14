#include "pch.h"
#pragma once

namespace graphics
{

class Shader
{
public:
    Shader(const std::string &vertexShader, const std::string &fragmentShader);
    ~Shader();

    void bind() const;
    void unbind() const;
    int32_t getUniform(const std::string &loc);

    void setUniformMat4(int32_t loc, const glm::mat4x4 &values);
    void setUniformMat3(int32_t loc, const glm::mat3x3 &values);
    void setUniform(int32_t loc, const Vector3 &v);
    void setUniform(int32_t loc, const Vector2 &v);
    void setUniform(int32_t loc, float x);

private:
    std::unordered_map<std::string, int32_t> m_Cache;
    uint32_t m_Id;

    uint32_t compileShader(GLenum shaderType, const std::string &shader);
    std::string readFile(const std::string &path);
};
} // namespace graphics