#include "Graphics/window.hpp"
#include "pch.h"
#include <glm/gtc/matrix_transform.hpp>
namespace graphics {
Window::Window(uint32_t width, uint32_t height)
    : m_Width(width), m_Height(height), m_Fov(70) {

  if (!glfwInit()) {
    std::cout << "failed to inizialize glfw";
    return;
  }

  m_Window = glfwCreateWindow(m_Width, m_Height, "Blocky", 0, 0);
  glfwMakeContextCurrent(m_Window);

  if (!m_Window)
    return;

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "failed to inizialize glad";
  }
  glm::mat4 per = glm::perspectiveFov((float)m_Fov, (float)m_Width,
                                      (float)m_Height, 0.f, 10000.f);
  m_Renderer = new Renderer(per);
}

Window::Window(uint32_t height, uint32_t width, uint32_t FOV)
    : m_Width(width), m_Height(height), m_Fov(FOV) {

  assert(glfwInit());
  m_Window = glfwCreateWindow(m_Width, m_Height, "Blocky", nullptr, nullptr);
  assert(m_Window);

  glfwMakeContextCurrent(m_Window);

  if (!gladLoadGL()) {
    std::cout << "failed to inizialize glad";
  }
  m_Renderer = new Renderer(
      glm::perspectiveFov<float>(m_Fov, m_Width, m_Height, 0, 10000));
}
void Window::render() {
  while (!glfwWindowShouldClose(m_Window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    m_Renderer->flush();
    glfwSwapBuffers(m_Window);
  }
}

} // namespace graphics