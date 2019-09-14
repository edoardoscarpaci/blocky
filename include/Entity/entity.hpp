#include "pch.h"
#pragma once

class Entity
{
public:
    virtual ~Entity(){};

    virtual void getDamage(float amount) = 0;
    virtual void Die() = 0;

protected:
    Entity(){};

    Vector3 m_Position;
    float m_Speed;
    float m_Health;
    int m_Armor;
};