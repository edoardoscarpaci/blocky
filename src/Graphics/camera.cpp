#include "Graphics/camera.hpp"
#include "Graphics/window.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace graphics
{

Camera::Camera(const Vector3 &pos) : m_CameraHeight(2), m_ViewMatrix(1), m_Position(pos)
{
}

void Camera::move(const Vector3 &pos)
{
    m_Position = pos;
}

void Camera::moveAdd(const Vector3 &pos)
{

    m_Position += pos;
    std::cout << "X:" << m_Position.x << " Y: " << m_Position.y << " Z: " << m_Position.z << std::endl;
}

void Camera::moveAdd(int x, int y, int z)
{
    m_Position += Vector3(x, y, z);
    std::cout << "X:" << m_Position.x << " Y: " << m_Position.y << " Z: " << m_Position.z << std::endl;
}

glm::mat4 Camera::getViewMatrix()
{
    Window *w = Window::getInstance();

    //std::cout << glm::to_string(glm::lookAt(m_Position, Vector3(w->getWidth() / 2, w->getHeight() / 2, -1), Vector3(0, 1, 0))) << std::endl;
    return glm::lookAt(m_Position, m_Position + glm::vec3(0, 0, -1), Vector3(0, 1, 0));
}

} // namespace graphics