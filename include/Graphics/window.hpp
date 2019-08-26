#include "pch.h"

#include "renderer.hpp"
namespace graphics {
class Window {
public:
  Window(uint32_t height, uint32_t width);
  Window(uint32_t height, uint32_t width, uint32_t FOV);
  ~Window() { glfwTerminate(); };
  void render();

  inline void enableVSync() const;
  inline void disableVSync() const;

  inline Renderer *getRenderer() const { return m_Renderer; };
  inline const GLFWwindow *const getWindow() const { return m_Window; }

private:
  Renderer *m_Renderer;
  GLFWwindow *m_Window;

  uint32_t m_Fov;
  uint32_t m_Height;
  uint32_t m_Width;
};

} // namespace graphics