#include "pch.h"
#pragma once

#include "Graphics/window.hpp"
using func = void (*)();

class Keybinding
{
public:
    static Keybinding *getInstance()
    {
        if (m_Instance)
        {
            return m_Instance;
        }
        m_Instance = new Keybinding();
        return m_Instance;
    };

    static void attachWindow(const graphics::Window *window)
    {
        Keybinding *instance = getInstance();
        instance->setWindow(window->getWindow());
    };

    Keybinding(Keybinding const &) = delete;
    void operator=(Keybinding const &) = delete;

public:
    void setCallBack(int scancode, std::pair<func, const std::string> function);
    void setCallBack(int scancode, func function, std::string &name);
    void deleteCallback(int scancode, const std::string &name);

private:
    Keybinding();
    static Keybinding *m_Instance;

    std::unordered_map<int, std::unique_ptr<std::vector<std::pair<func, const std::string>>>> m_Callback;
    GLFWwindow *m_Window;

    void callBack(GLFWwindow *window, int key, int scancode, int action, int mods);
    void setWindow(const GLFWwindow *window);

    static void setCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Keybinding::getInstance()->callBack(window, key, scancode, action, mods);
    }
};