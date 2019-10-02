#include "pch.h"
#pragma once

#include "Entity/entity.hpp"
#include "Graphics/camera.hpp"

class Player : Entity
{
public:
    Player(graphics::Camera *camera, const Vector3 &pos, float speed);
    Player(const Vector3 &pos, float speed);

    virtual ~Player() override { delete m_Camera; };

    inline graphics::Camera *getCamera() const { return m_Camera; };

    virtual void Die() override{};
    virtual void getDamage(float amount) override{};

    void Update(float elapsedTime) override;

private:
    graphics::Camera *m_Camera;

    void setKeybinding();

    void moveRight();
    void moveForward();
    void moveLeft();
    void moveBack();
    void moveUp();
    void moveDown();
};