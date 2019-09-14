#include "Graphics/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace graphics
{

Camera::Camera(const Vector3 &pos)
{
    m_ViewMatrix = glm::translate(m_ViewMatrix, pos);
}

void Camera::move(const Vector3 &pos)
{
    m_ViewMatrix = glm::translate(m_ViewMatrix, pos);
}

void Camera::moveAdd(const Vector3 &pos)
{
    Vector3 p = Vector3(m_ViewMatrix[3].x, m_ViewMatrix[3].y, m_ViewMatrix[3].z);
    Vector3 position = p + pos;
    m_ViewMatrix = glm::translate(m_ViewMatrix, position);
}

void Camera::moveAdd(int x, int y, int z)
{
    Vector3 p = Vector3(m_ViewMatrix[3].x, m_ViewMatrix[3].y, m_ViewMatrix[3].z);
    Vector3 position = p + Vector3(x, y, z);
    m_ViewMatrix = glm::translate(m_ViewMatrix, position);
}

glm::mat4 Camera::getViewMatrix()
{
    return m_ViewMatrix;
}

} // namespace graphics