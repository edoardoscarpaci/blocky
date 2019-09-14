#include "util/keybinding.hpp"

Keybinding *Keybinding::m_Instance = nullptr;

Keybinding::Keybinding()
{
    if (m_Window)
        glfwSetKeyCallback(m_Window, setCallback);
}

void Keybinding::setCallBack(int scancode, std::pair<func, const std::string> function)
{
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
        m_Callback[scancode] = std::unique_ptr<std::vector<std::pair<func, const std::string>>>(new std::vector<std::pair<func, const std::string>>());
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
    //Calling all the function binded to keys
    if (m_Callback.find(scancode) != m_Callback.end())
    {
        for (int i = 0; i < m_Callback[scancode]->size(); i++)
            std::get<func>(m_Callback[scancode]->at(i))();
    }
}

void Keybinding::setWindow(const GLFWwindow *window)
{
    m_Window = (GLFWwindow *)window;
    glfwSetKeyCallback(m_Window, setCallback);
}