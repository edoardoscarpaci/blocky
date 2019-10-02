#include "Entity/player.hpp"
#include "util/keybinding.hpp"

Player::Player(graphics::Camera *camera, const Vector3 &pos, float speed) : m_Camera(camera)
{
    m_Speed = speed;
    m_Position = pos;
    graphics::Window::getInstance()->attachCamera(m_Camera);
    setKeybinding();
}

Player::Player(const Vector3 &pos, float speed)
{
    m_Speed = speed;
    m_Position = pos;
    Vector3 p = Vector3(m_Position.x, m_Position.y, m_Position.z);

    m_Camera = new graphics::Camera(p);
    graphics::Window::getInstance()->attachCamera(m_Camera);

    //setKeybinding();
}

void Player::Update(float elapsedTime)
{
    if (Keybinding::isKeyPress(Keybinding::Keycode::A))
    {
        Vector3 add = Vector3(-1 * m_Speed * elapsedTime, 0, 0);
        m_Position += add;
        m_Camera->moveAdd(add);
        std::cout << "X : " << m_Position.x << " Y: " << m_Position.y << " Z:" << m_Position.z << std::endl;
    }
    if (Keybinding::isKeyPress(Keybinding::Keycode::D))
    {
        Vector3 add = Vector3(1 * m_Speed * elapsedTime, 0, 0);
        m_Position += add;
        m_Camera->moveAdd(add);
        std::cout << "X : " << m_Position.x << " Y: " << m_Position.y << " Z:" << m_Position.z << std::endl;
    }

    if (Keybinding::isKeyPress(Keybinding::Keycode::W))
    {
        Vector3 add = Vector3(0, 0, -1 * m_Speed * elapsedTime);
        m_Position += add;
        m_Camera->moveAdd(add);

        std::cout << "X : " << m_Position.x << " Y: " << m_Position.y << " Z:" << m_Position.z << std::endl;
    }

    if (Keybinding::isKeyPress(Keybinding::Keycode::S))
    {
        Vector3 add = Vector3(0, 0, 1 * m_Speed * elapsedTime);
        m_Position += add;
        m_Camera->moveAdd(add);
        std::cout << "X : " << m_Position.x << " Y: " << m_Position.y << " Z:" << m_Position.z << std::endl;
    }

    if (Keybinding::isKeyPress(Keybinding::Keycode::Z))
    {
        Vector3 add = Vector3(0, 1 * m_Speed * elapsedTime, 0);
        m_Position += add;
        m_Camera->moveAdd(add);
        std::cout << "X : " << m_Position.x << " Y: " << m_Position.y << " Z:" << m_Position.z << std::endl;
    }

    if (Keybinding::isKeyPress(Keybinding::Keycode::X))
    {
        Vector3 add = Vector3(0, -1 * m_Speed * elapsedTime, 0);
        m_Position += add;
        m_Camera->moveAdd(add);
        std::cout << "X : " << m_Position.x << " Y: " << m_Position.y << " Z:" << m_Position.z << std::endl;
    }
}

void Player::setKeybinding()
{
    Keybinding *instance = Keybinding::getInstance();

    /*int a = glfwGetKeyScancode(GLFW_KEY_A);
    int w = glfwGetKeyScancode(GLFW_KEY_W);
    int s = glfwGetKeyScancode(GLFW_KEY_S);
    int d = glfwGetKeyScancode(GLFW_KEY_D);
    int z = glfwGetKeyScancode(GLFW_KEY_Z);
    int x = glfwGetKeyScancode(GLFW_KEY_X);

    instance->setCallBack(w, std::make_pair((callbackWrapper *)new Callback<Player>(this, &Player::moveForward), "moveForward"));
    instance->setCallBack(a, std::make_pair((callbackWrapper *)new Callback<Player>(this, &Player::moveLeft), "moveLeft"));
    instance->setCallBack(s, std::make_pair((callbackWrapper *)new Callback<Player>(this, &Player::moveBack), "moveBack"));
    instance->setCallBack(d, std::make_pair((callbackWrapper *)new Callback<Player>(this, &Player::moveRight), "moveRight"));
    instance->setCallBack(z, std::make_pair((callbackWrapper *)new Callback<Player>(this, &Player::moveUp), "moveUp"));
    instance->setCallBack(x, std::make_pair((callbackWrapper *)new Callback<Player>(this, &Player::moveDown), "moveDown"));
*/
}

void Player::moveRight()
{
    m_Position.x += 1;
    m_Camera->moveAdd(+1, 0, 0);
}
void Player::moveForward()
{
    m_Position.z -= 1;
    m_Camera->moveAdd(0, 0, -1);
}
void Player::moveBack()
{
    m_Position.z += 1;
    m_Camera->moveAdd(0, 0, +1);
}

void Player::moveUp()
{
    m_Position.y += 1;
    m_Camera->moveAdd(0, 1, 0);
}

void Player::moveDown()
{
    m_Position.y -= 1;
    m_Camera->moveAdd(0, -1, 0);
}
