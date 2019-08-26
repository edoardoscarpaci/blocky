#pragma once
#ifdef DEBUG
#define glCall(x)                                                              \
  x;                                                                           \
  {                                                                            \
    unsigned int err = 0;                                                      \
    while (err != glGetError()) {                                              \
      std::cout << std::hex << err << " in file" << __FILE__ << ": "           \
                << __LINE__;                                                   \
    }                                                                          \
  }
#define glCallr(x, y)                                                          \
  y = x;                                                                       \
  {                                                                            \
    unsigned int err = 0;                                                      \
    while (err != glGetError()) {                                              \
      std::cout << std::hex << err << " in file" << __FILE__ << ": "           \
                << __LINE__;                                                   \
    }                                                                          \
  }
#else
#define glCall(x) x;
#define glCallr(x, y) y = x;
#endif
