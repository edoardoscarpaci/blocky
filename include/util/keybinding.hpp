#include "pch.h"
#pragma once

#include "Graphics/window.hpp"
#include "util/callback.hpp"

class Keybinding
{

public:
    enum Keycode
    {
        None,
        Alpha0,
        Alpha1,
        Alpha2,
        Alpha3,
        Alpha4,
        Alpha5,
        Alpha6,
        Alpha7,
        Alpha8,
        Alpha9,
        Minus,
        BackSpace,
        Tab,
        Q,
        W,
        E,
        R,
        T,
        Y,
        U,
        I,
        O,
        P,
        //OpenSquareBracket =GLFW_KEY_Br,
        //CloseSquareBracket,
        Caps,
        A,
        S,
        D,
        F,
        G,
        H,
        J,
        K,
        L,
        Semicolon,
        Singlequote,
        Doublequote,
        Backslash,
        Leftshift,
        Z,
        X,
        C,
        V,
        B,
        N,
        M,
        Comma,
        FullStop,
        Slash,
        Enter,
        RightShift,
        LeftCtrl,
        LeftAlt,
        RightAlt,
        RightCtrl
    };

public:
    static Keybinding *
    getInstance()
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

    static bool isKeyPress(Keycode key)
    {
        m_Instance->isPress(key);
    }

    static bool isKeyPress(Keycode key, bool alt, bool ctrl)
    {
        m_Instance->isPress(key);
    }

    Keybinding(Keybinding const &) = delete;
    void operator=(Keybinding const &) = delete;

public:
    void setCallBack(Keycode key, std::pair<callbackWrapper *, const std::string> function);
    //void setCallBack(int scancode, func function, std::string &name);
    void deleteCallback(int scancode, const std::string &name);

private:
    Keybinding();
    static Keybinding *m_Instance;

    std::unordered_map<int, std::unique_ptr<std::vector<std::pair<callbackWrapper *, const std::string>>>> m_Callback;
    GLFWwindow *m_Window;
    bool m_SetCallback;

    std::array<bool, 55> m_Keys;

    void callBack(GLFWwindow *window, int key, int scancode, int action, int mods);
    void setWindow(const GLFWwindow *window);

    bool isPress(Keycode key);
    bool isPress(Keycode key, bool alt, bool ctrl);

    bool setKey(bool state);

    static void setCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Keybinding::getInstance()->callBack(window, key, scancode, action, mods);
    }

    int getCode(Keycode key);
    Keycode getKey(int glfwCode);
};