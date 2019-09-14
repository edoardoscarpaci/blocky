#pragma once
#ifdef DEBUG
#define glCall(x)                                                                   \
  x;                                                                                \
  {                                                                                 \
    unsigned int err = 0;                                                           \
    while ((err = glGetError()) != GL_NO_ERROR)                                     \
    {                                                                               \
      std::cout << "ERROR: 0x" << std::hex << err << " in file" << __FILE__ << ": " \
                << std::dec << __LINE__ << '\n';                                    \
    }                                                                               \
  }
#define glCallr(x, y)                                                               \
  y = x;                                                                            \
  {                                                                                 \
    unsigned int err = 0;                                                           \
    while ((err = glGetError()) != GL_NO_ERROR)                                     \
    {                                                                               \
      std::cout << "ERROR: 0x" << std::hex << err << " in file" << __FILE__ << ": " \
                << std::dec << __LINE__ << '\n';                                    \
    }                                                                               \
  }
#else
#define glCall(x) x;
#define glCallr(x, y) y = x;
#endif
