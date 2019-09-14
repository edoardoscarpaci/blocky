#include "pch.h"
#pragma once
#include "renderer.hpp"
namespace graphics
{
class Window
{
public:
  static Window *createInstance(uint32_t height, uint32_t width)
  {
    if (!m_Instance)
    {
      m_Instance = new Window(height, width);
    }
    return m_Instance;
  }

  static Window *getInstance()
  {
    if (!m_Instance)
    {
      m_Instance = new Window(640, 440);
    }
    return m_Instance;
  }

  ~Window() { glfwTerminate(); };
  void render();

  inline void enableVSync() const;
  inline void disableVSync() const;

  inline Renderer *getRenderer() const { return m_Renderer; };
  inline const GLFWwindow *const getWindow() const { return m_Window; }

  void attachCamera(graphics::Camera *camera);

protected:
  Window(uint32_t height, uint32_t width);
  Window(uint32_t height, uint32_t width, uint32_t FOV);

private:
  static Window *m_Instance;

  Renderer *m_Renderer;
  GLFWwindow *m_Window;

  uint32_t m_Fov;
  uint32_t m_Height;
  uint32_t m_Width;
};

} // namespace graphics