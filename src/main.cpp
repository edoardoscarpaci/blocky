#include "Graphics/window.hpp"
#include "Graphics/cube.hpp"
#include "Graphics/renderer.hpp"
#include "Entity/player.hpp"
#include "util/keybinding.hpp"

#include "util/gamemanager.hpp"

using namespace graphics;
int main(int argc, char **argv)
{

  GameManager *g = GameManager::createInstance(640, 320);
  graphics::Renderer *r = graphics::Window::getInstance()->getRenderer();

  Player *m_Player = new Player(Vector3(100, 0, 0), 0.1f);

  for (int i = 0; i < 1024; i++)
  {
    for (int j = -20; j < 0; j++)
    {
      graphics::Cube c = graphics::Cube(Vector3(i, 0, j));
      r->addCube(c);
    }
  }

  g->Run();
  std::cout << "OpenGL VERSION" << GLVersion.major << "." << GLVersion.minor;
}