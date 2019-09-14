#include "Graphics/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace graphics
{
Cube::Cube(Vector3 position) : m_Position(position), Renderable()
{

    m_Transform = glm::translate(m_Transform, position);

    Vertex vertices[] = {
        Vertex(Vector3(-1, -1, 0), Vector2(0, 0)), //First Vertex
        Vertex(Vector3(-1, -1, 1), Vector2(0, 0)), //Second Vertex
        Vertex(Vector3(1, -1, 1), Vector2(1, 0)),  //Third Vertex
        Vertex(Vector3(1, -1, 0), Vector2(1, 0)),  //Fourth Vertex
        Vertex(Vector3(-1, 1, 0), Vector2(0, 1)),  //Fifth Vertex
        Vertex(Vector3(-1, 1, 1), Vector2(0, 1)),  //Sixth Vertex
        Vertex(Vector3(1, 1, 1), Vector2(1, 1)),   //Seventh Vertex
        Vertex(Vector3(1, 1, 0), Vector2(1, 1)),   //Eight Vertex
    };

    uint32_t indices[] =
        {
            0, 1, 2, 2, 3, 0, //Bottom
            4, 5, 6, 6, 7, 4, //Top
            0, 4, 7, 7, 3, 0, //Front
            1, 5, 6, 6, 2, 1, //Back
            0, 4, 5, 5, 1, 0, //Left
            3, 7, 6, 6, 2, 3  //Right
        };

    m_Vbo = new VBO(sizeof(vertices), vertices, GL_STATIC_DRAW);
    m_Ibo = new Ibo(indices, sizeof(indices) / sizeof(uint32_t), GL_STATIC_DRAW);

    m_Position = m_Transform * glm::vec4(m_Position, 1);
}
Cube::Cube(Vector3 position, Texture tex) : m_Position(position), m_Texture(tex), Renderable()
{

    m_Transform = glm::translate(m_Transform, position);

    Vertex vertices[] = {
        Vertex(Vector3(-1, -1, 0), Vector2(0, 0)), //First Vertex
        Vertex(Vector3(-1, -1, 1), Vector2(0, 0)), //Second Vertex
        Vertex(Vector3(1, -1, 1), Vector2(1, 0)),  //Third Vertex
        Vertex(Vector3(1, -1, 0), Vector2(1, 0)),  //Fourth Vertex
        Vertex(Vector3(-1, 1, 0), Vector2(0, 1)),  //Fifth Vertex
        Vertex(Vector3(-1, 1, 1), Vector2(0, 1)),  //Sixth Vertex
        Vertex(Vector3(1, 1, 1), Vector2(1, 1)),   //Seventh Vertex
        Vertex(Vector3(1, 1, 0), Vector2(1, 1)),   //Eight Vertex
    };

    uint32_t indices[] =
        {
            0, 1, 2, 2, 3, 0, //Bottom
            4, 5, 6, 6, 7, 4, //Top
            0, 4, 7, 7, 3, 0, //Front
            1, 5, 6, 6, 2, 1, //Back
            0, 4, 5, 5, 1, 0, //Left
            3, 7, 6, 6, 2, 3  //Right
        };

    m_Vbo = new VBO(sizeof(vertices), vertices, GL_STATIC_DRAW);
    m_Ibo = new Ibo(indices, sizeof(indices) / sizeof(uint32_t), GL_STATIC_DRAW);

    m_Position = m_Transform * glm::vec4(m_Position, 1);
}

void Cube::setPosition(const Vector3 &pos)
{
    m_Transform = glm::translate(m_Transform, pos);
    m_Position = m_Transform * glm::vec4(m_Position, 1);
}

void Cube::setScale(const Vector3 &scale)
{
    m_Transform = glm::scale(m_Transform, scale);
    m_Position = m_Transform * glm::vec4(m_Position, 1);
}

void Cube::setRotation(const Vector3 &scale)
{
    //TO DO
}

Cube::~Cube()
{
    delete m_Ibo;
    delete m_Vbo;
}
} // namespace graphics