#include "Graphics/window.hpp"
#include "Graphics/cube.hpp"
#include "Graphics/renderer.hpp"
#include "Entity/player.hpp"
#include "util/keybinding.hpp"

int main(int argc, char **argv)
{

  graphics::Window *w = graphics::Window::createInstance(600, 300);
  Keybinding::attachWindow(w);

  Player player(Vector3(300, 150, 0));
  graphics::Renderer *r = w->getRenderer();

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 128; j++)
    {
      graphics::Cube c(Vector3(j, -1, i));
      r->addCube(c);
    }
  }

  w->render();
  std::cout << "OpenGL VERSION" << GLVersion.major << "." << GLVersion.minor;
}