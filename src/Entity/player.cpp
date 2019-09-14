#include "Entity/player.hpp"
#include "util/keybinding.hpp"

Player::Player(graphics::Camera *camera, const Vector3 &pos) : m_Camera(camera)
{
    m_Position = pos;
    graphics::Window::getInstance()->attachCamera(m_Camera);
    setKeybinding();
}

Player::Player(const Vector3 &pos)
{
    m_Position = pos;
    m_Camera = new graphics::Camera(Vector3(m_Position.x, m_Position.y, -1));
    graphics::Window::getInstance()
        ->attachCamera(m_Camera);
    setKeybinding();
}

Player::~Player()
{
    delete m_Camera;
}

void Player::setKeybinding()
{
    Keybinding *instance = Keybinding::getInstance();
    int a = glfwGetKeyScancode(GLFW_KEY_A);
    int w = glfwGetKeyScancode(GLFW_KEY_W);
    int s = glfwGetKeyScancode(GLFW_KEY_S);
    int d = glfwGetKeyScancode(GLFW_KEY_D);

    instance->setCallBack(w, std::make_pair((func)&Player::moveForward, "moveForward"));
    instance->setCallBack(a, std::make_pair((func)&Player::moveLeft, "moveLeft"));
    instance->setCallBack(s, std::make_pair((func)&Player::moveBack, "moveBack"));
    instance->setCallBack(d, std::make_pair((func)&Player::moveRight, "moveRight"));
}

void Player::moveLeft()
{
    m_Position.x -= 1;
    m_Camera->moveAdd(0, -1, 0);
}
void Player::moveRight()
{
    m_Position.x += 1;
    m_Camera->moveAdd(0, +1, 0);
}
void Player::moveForward()
{
    m_Position.z += 1;
    m_Camera->moveAdd(0, 0, 1);
}
void Player::moveBack()
{
    m_Position.z -= 1;
    m_Camera->moveAdd(0, 0, -1);
}
