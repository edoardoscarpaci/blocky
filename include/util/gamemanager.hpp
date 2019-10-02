#include "pch.h"
#include "Graphics/window.hpp"
#include "util/timer.hpp"
#include "Entity/player.hpp"

#pragma once

class Dynamic;
class GameManager
{
public:
    static GameManager *createInstance(uint32_t width, uint32_t height)
    {
        m_Instance = new GameManager(width, height);
        return m_Instance;
    }

    static GameManager *getInstance()
    {
        if (m_Instance)
            return m_Instance;
        m_Instance = new GameManager(1366, 720);
        return m_Instance;
    }

    void UpdateEntity(Dynamic *e);
    void RemoveEntity(Dynamic *e);

    void Run();

protected:
    GameManager(uint32_t width, uint32_t height);
    ~GameManager();
    void Tick(float elapsedTime);

private:
    static GameManager *m_Instance;
    //Player *m_Player;
    graphics::Window *m_Window;
    Timer m_Timer;
    std::vector<Dynamic *> m_Dynamic;
};