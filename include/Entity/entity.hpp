#include "pch.h"
#include "Entity/dynamic.hpp"
#pragma once

class Entity : Dynamic
{
public:
    virtual ~Entity() override;
    virtual void getDamage(float amount) = 0;
    virtual void Die() = 0;
    virtual void Update(float elapsedTime) override;

protected:
    Entity();

    Vector3 m_Position;
    float m_Speed;
    float m_Health;
    int m_Armor;
};