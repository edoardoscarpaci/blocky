#include "Graphics/window.hpp"
int main(int argc, char **argv) {

  graphics::Window *w = new graphics::Window(266, 150);
  std::cout << "OpenGL VERSION" << GLVersion.major << "." << GLVersion.minor;
}