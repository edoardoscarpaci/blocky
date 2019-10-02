#include "util/gamemanager.hpp"
#include "Graphics/window.hpp"
#include "util/keybinding.hpp"
#include "Entity/dynamic.hpp"

GameManager *GameManager::m_Instance = nullptr;

GameManager::GameManager(uint32_t width, uint32_t height)
{
    m_Window = graphics::Window::createInstance(width, height);
    Keybinding::attachWindow(m_Window);
}

GameManager::~GameManager()
{
    delete m_Window;
}

void GameManager::Run()
{

    float time = 1000.f / 30.f;

    float frameTime = 1000;

    float elapsedTime = 0;
    uint16_t framexSecond = 0;

    while (!glfwWindowShouldClose((GLFWwindow *)m_Window->getWindow()))
    {

        m_Timer.Start();
        m_Window->render();

        elapsedTime = m_Timer.GetTime();

        time -= elapsedTime;
        frameTime -= elapsedTime;
        framexSecond++;

        if (time <= 0)
        {
            Tick(1);
            time = 1000 / 30;
        }

        if (frameTime <= 0)
        {
            std::cout << "FPS: " << framexSecond << std::endl;
            framexSecond = 0;
            frameTime = 1000;
        }
    }
}

void GameManager::Tick(float elapsedTime)
{
    for (Dynamic *dynamic : m_Dynamic)
    {
        dynamic->Update(elapsedTime);
    }
}

void GameManager::UpdateEntity(Dynamic *e)
{
    m_Dynamic.emplace_back(e);
    if (std::find(m_Dynamic.begin(), m_Dynamic.end(), e) != m_Dynamic.end())
    {
        m_Dynamic.emplace_back(e);
    }
}

void GameManager::RemoveEntity(Dynamic *e)
{
    auto it = std::find(m_Dynamic.begin(), m_Dynamic.end(), e);
    if (it != m_Dynamic.end())
    {
        m_Dynamic.erase(it);
        m_Dynamic.shrink_to_fit();
    }
}