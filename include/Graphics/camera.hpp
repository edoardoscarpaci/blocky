#include "pch.h"
#pragma once

namespace graphics
{

class Camera
{
public:
    Camera(const Vector3 &position);
    void move(const Vector3 &pos);
    void moveAdd(const Vector3 &pos);
    void moveAdd(int x, int y, int z);

    glm::mat4 getViewMatrix();

private:
    glm::mat4 m_ViewMatrix;
};
} // namespace graphics