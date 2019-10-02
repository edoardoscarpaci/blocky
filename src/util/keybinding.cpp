#include "util/keybinding.hpp"

Keybinding *Keybinding::m_Instance = nullptr;

Keybinding::Keybinding() : m_SetCallback(0)
{
    std::memset(m_Keys.data(), false, m_Keys.size());
}

void Keybinding::setCallBack(Keycode key, std::pair<callbackWrapper *, const std::string> function)
{
    int scancode = glfwGetKeyScancode(getCode(key));
    //If there is another callback binded to the scancode
    if (m_Callback.find(scancode) != m_Callback.end())
    {

        bool found = false;
        for (int i = 0; i < m_Callback[scancode]->size(); i++)
        {
            if (std::get<const std::string>(m_Callback[scancode]->at(i)) == std::get<const std::string>(function))
            {
                found = true;
                break;
            }
        }

        if (!found)
            m_Callback[scancode]->emplace_back(function);
    }
    else
    {
        m_Callback[scancode] = std::unique_ptr<std::vector<std::pair<callbackWrapper *, const std::string>>>(new std::vector<std::pair<callbackWrapper *, const std::string>>());
        m_Callback[scancode]->emplace_back(function);
    }
}

void Keybinding::deleteCallback(int scancode, const std::string &name)
{

    if (m_Callback.find(scancode) != m_Callback.end())
    {
        /*
        bool found = false;
        for (int i = 0; i < m_Callback[scancode]->size(); i++)
        {
            if (std::get<const std::string>(m_Callback[scancode]->at(i)) == name)
            {
                m_Callback[scancode]->erase(m_Callback[scancode]->begin() + i);
                m_Callback[scancode]->shrink_to_fit();
            }
        }*/
    }
}
void Keybinding::callBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    if (action != GLFW_RELEASE)
    {
        m_Keys[getKey(key)] = true;

        if (m_Callback.find(scancode) != m_Callback.end())
        {
            for (int i = 0; i < m_Callback[scancode]->size(); i++)
                std::get<callbackWrapper *>(m_Callback[scancode]->at(i))->execute();
        }
    }
    else
    {
        m_Keys[getKey(key)] = false;
    }
}
void Keybinding::setWindow(const GLFWwindow *window)
{
    m_Window = (GLFWwindow *)window;
    if (!m_SetCallback)
    {
        std::cout << "Callback setted" << std::endl;
        glfwSetKeyCallback(m_Window, setCallback);
        m_SetCallback = true;
    }
}

bool Keybinding::isPress(Keycode key)
{
    return m_Keys[key];
}

bool Keybinding::isPress(Keycode key, bool alt, bool ctrl)
{
    if ((m_Keys[key] & ctrl) | (m_Keys[key] & alt))
    {
        return m_Keys[key];
    }
}

int Keybinding::getCode(Keycode key)
{
    switch (key)
    {
    case Keycode::Alpha0:
        return GLFW_KEY_0;

    case Keycode::Alpha1:
        return GLFW_KEY_1;

    case Keycode::Alpha2:
        return GLFW_KEY_2;

    case Keycode::Alpha3:
        return GLFW_KEY_3;

    case Keycode::Alpha4:
        return GLFW_KEY_4;

    case Keycode::Alpha5:
        return GLFW_KEY_5;

    case Keycode::Alpha6:
        return GLFW_KEY_6;

    case Keycode::Alpha7:
        return GLFW_KEY_7;

    case Keycode::Alpha8:
        return GLFW_KEY_8;

    case Keycode::Alpha9:
        return GLFW_KEY_9;

    case Keycode::W:
        return GLFW_KEY_W;

    case Keycode::E:
        return GLFW_KEY_E;

    case Keycode::R:
        return GLFW_KEY_R;

    case Keycode::T:
        return GLFW_KEY_T;

    case Keycode::Y:
        return GLFW_KEY_Y;

    case Keycode::U:
        return GLFW_KEY_U;

    case Keycode::I:
        return GLFW_KEY_I;

    case Keycode::O:
        return GLFW_KEY_O;

    case Keycode::P:
        return GLFW_KEY_P;

    case Keycode::A:
        return GLFW_KEY_A;

    case Keycode::S:
        return GLFW_KEY_S;

    case Keycode::D:
        return GLFW_KEY_D;

    case Keycode::F:
        return GLFW_KEY_F;

    case Keycode::G:
        return GLFW_KEY_G;

    case Keycode::H:
        return GLFW_KEY_H;

    case Keycode::J:
        return GLFW_KEY_J;

    case Keycode::K:
        return GLFW_KEY_K;

    case Keycode::L:
        return GLFW_KEY_L;

    case Keycode::Semicolon:
        return GLFW_KEY_SEMICOLON;

    case Keycode::Singlequote:
        return GLFW_KEY_GRAVE_ACCENT;

    case Keycode::Backslash:
        return GLFW_KEY_BACKSLASH;

    case Keycode::Leftshift:
        return GLFW_KEY_LEFT_SHIFT;

    case Keycode::Z:
        return GLFW_KEY_Z;

    case Keycode::X:
        return GLFW_KEY_X;

    case Keycode::C:
        return GLFW_KEY_C;

    case Keycode::V:
        return GLFW_KEY_V;

    case Keycode::B:
        return GLFW_KEY_B;

    case Keycode::N:
        return GLFW_KEY_N;

    case Keycode::M:
        return GLFW_KEY_M;

    case Keycode::Comma:
        return GLFW_KEY_COMMA;

    case Keycode::FullStop:
        return GLFW_KEY_PERIOD;

    case Keycode::Slash:
        return GLFW_KEY_SLASH;

    case Keycode::RightShift:
        return GLFW_KEY_RIGHT_SHIFT;

    case Keycode::LeftCtrl:
        return GLFW_KEY_LEFT_CONTROL;

    case Keycode::LeftAlt:
        return GLFW_KEY_LEFT_ALT;

    case Keycode::RightAlt:
        return GLFW_KEY_RIGHT_ALT;

    case Keycode::RightCtrl:
        return GLFW_KEY_RIGHT_CONTROL;

    default:
        return GLFW_KEY_UNKNOWN;
    }
}

Keybinding::Keycode Keybinding::getKey(int glfwCode)
{
    switch (glfwCode)
    {
    case GLFW_KEY_0:
        return Keycode::Alpha0;

    case GLFW_KEY_1:
        return Keycode::Alpha1;

    case GLFW_KEY_2:
        return Keycode::Alpha2;

    case GLFW_KEY_3:
        return Keycode::Alpha3;

    case GLFW_KEY_4:
        return Keycode::Alpha4;

    case GLFW_KEY_5:
        return Keycode::Alpha5;

    case GLFW_KEY_6:
        return Keycode::Alpha6;

    case GLFW_KEY_7:
        return Keycode::Alpha7;

    case GLFW_KEY_8:
        return Keycode::Alpha8;

    case GLFW_KEY_9:
        return Keycode::Alpha9;

    case GLFW_KEY_W:
        return Keycode::W;

    case GLFW_KEY_E:
        return Keycode::E;

    case GLFW_KEY_R:
        return Keycode::R;

    case GLFW_KEY_T:
        return Keycode::T;

    case GLFW_KEY_Y:
        return Keycode::Y;

    case GLFW_KEY_U:
        return Keycode::U;

    case GLFW_KEY_I:
        return Keycode::I;

    case GLFW_KEY_O:
        return Keycode::O;

    case GLFW_KEY_P:
        return Keycode::P;

    case GLFW_KEY_A:
        return Keycode::A;

    case GLFW_KEY_S:
        return Keycode::S;

    case GLFW_KEY_D:
        return Keycode::D;

    case GLFW_KEY_F:
        return Keycode::F;

    case GLFW_KEY_G:
        return Keycode::G;

    case GLFW_KEY_H:
        return Keycode::H;

    case GLFW_KEY_J:
        return Keycode::J;

    case GLFW_KEY_K:
        return Keycode::K;

    case GLFW_KEY_L:
        return Keycode::L;

    case GLFW_KEY_SEMICOLON:
        return Keycode::Semicolon;

    case GLFW_KEY_GRAVE_ACCENT:
        return Keycode::Singlequote;

    case GLFW_KEY_BACKSLASH:
        return Keycode::Backslash;

    case GLFW_KEY_LEFT_SHIFT:
        return Keycode::Leftshift;

    case GLFW_KEY_Z:
        return Keycode::Z;

    case GLFW_KEY_X:
        return Keycode::X;

    case GLFW_KEY_C:
        return Keycode::C;

    case GLFW_KEY_V:
        return Keycode::V;

    case GLFW_KEY_B:
        return Keycode::B;

    case GLFW_KEY_N:
        return Keycode::N;

    case GLFW_KEY_M:
        return Keycode::M;

    case GLFW_KEY_COMMA:
        return Keycode::Comma;

    case GLFW_KEY_PERIOD:
        return Keycode::FullStop;

    case GLFW_KEY_SLASH:
        return Keycode::Slash;

    case GLFW_KEY_RIGHT_SHIFT:
        return Keycode::RightShift;

    case GLFW_KEY_LEFT_CONTROL:
        return Keycode::LeftCtrl;

    case GLFW_KEY_LEFT_ALT:
        return Keycode::LeftAlt;

    case GLFW_KEY_RIGHT_ALT:
        return Keycode::RightAlt;

    case GLFW_KEY_RIGHT_CONTROL:
        return Keycode::RightCtrl;

    default:
        return Keycode::None;
    }
}