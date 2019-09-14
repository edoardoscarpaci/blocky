#include "Graphics/shader.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace graphics
{

Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    uint32_t vShader = compileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glCallr(glCreateProgram(), m_Id);
    glCall(glAttachShader(m_Id, vShader));
    glCall(glAttachShader(m_Id, fShader));

    glCall(glBindAttribLocation(m_Id, 0, "pos"));
    glCall(glBindAttribLocation(m_Id, 1, "uv"));

    glCall(glLinkProgram(m_Id));

    int32_t error = 0;
    glCall(glGetProgramiv(m_Id, GL_LINK_STATUS, &error));
    if (!error)
    {
        int32_t maxLenght;
        glCall(glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &maxLenght));
        std::vector<char> errorLog(maxLenght);
        glCall(glGetProgramInfoLog(m_Id, maxLenght, &maxLenght, &errorLog[0]));
        std::string printError(errorLog.begin(), errorLog.end());
        std::cout << "Error linking program " << printError << '\n';

        glCall(glDeleteProgram(m_Id));
        glCall(glDeleteShader(vShader));
        glCall(glDeleteShader(fShader));
        return;
    }

    glCall(glDetachShader(m_Id, vShader));
    glCall(glDetachShader(m_Id, fShader));
    glCall(glDeleteShader(vShader));
    glCall(glDeleteShader(fShader));
    glCall(glUseProgram(m_Id));
};

Shader::~Shader()
{
    glCall(glDeleteProgram(m_Id));
}

std::string Shader::readFile(const std::string &path)
{
    std::ifstream in(path, std::ios::binary | std::ios::ate | std::ios::in);
    if (in)
    {
        std::string shader;
        shader.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&shader[0], shader.size());
        in.close();
        return shader;
    }
    return nullptr;
}
uint32_t Shader::compileShader(GLenum shaderType, const std::string &shader)
{
    uint32_t idShader;
    glCallr(glCreateShader(shaderType), idShader);
    const std::string source = readFile(shader);
    int32_t size;
    const char *shadersource = source.c_str();
    glCall(glShaderSource(idShader, 1, &shadersource, &size));
    glCall(glCompileShader(idShader));

    int32_t error = 0;
    glCall(glGetShaderiv(idShader, GL_COMPILE_STATUS, &error));
    if (!error)
    {
        int32_t maxLenght;
        glCall(glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &maxLenght));
        std::vector<char> errorLog(maxLenght);
        glCall(glGetShaderInfoLog(idShader, maxLenght, &maxLenght, &errorLog[0]));
        std::string printError(errorLog.begin(), errorLog.end());
        if (shaderType == GL_VERTEX_SHADER)
            std::cout << "Shader Vertex Shader Compilation Error:  " << printError << '\n';
        else
            std::cout << "Shader Fragment Shader Compilation Error:  " << printError << '\n';
    }
    return idShader;
}

int32_t Shader::getUniform(const std::string &loc)
{

    if (m_Cache.find(loc) != m_Cache.end())
    {

        return m_Cache[loc];
    }
    int found = -1;
    glCallr(glGetUniformLocation(m_Id, loc.c_str()), found);
    if (found == -1)
    {
        std::cout << "ERROR UNIFORM NOT FOUND: " << loc << '\n';
        return -1;
    }

    m_Cache[loc] = found;
    std::cout << loc << ": " << found << std::endl;

    return m_Cache[loc];
}

void Shader::setUniform(int32_t loc, const Vector3 &v)
{
    glCall(glUniform3f(loc, v.x, v.y, v.z));
}

void Shader::setUniform(int32_t loc, const Vector2 &v)
{
    glCall(glUniform2f(loc, v.x, v.y));
}

void Shader::setUniform(int32_t loc, float x)
{
    glCall(glUniform1f(loc, x));
}

void Shader::setUniformMat3(int32_t loc, const glm::mat3x3 &values)
{
    glCall(glUniformMatrix3fv(loc, 1, false, glm::value_ptr(values)));
}

void Shader::setUniformMat4(int32_t loc, const glm::mat4x4 &values)
{
    glCall(glUniformMatrix4fv(loc, 1, false, glm::value_ptr(values)));
}

void Shader::bind() const
{
    glCall(glUseProgram(m_Id));
}
void Shader::unbind() const
{
    glCall(glUseProgram(0));
}

} // namespace graphics