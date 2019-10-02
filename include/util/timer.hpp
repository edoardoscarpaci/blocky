#include "pch.h"
#include <chrono>

class Timer
{
public:
    Timer();
    void Start();
    float GetTime();

private:
    std::chrono::high_resolution_clock::time_point m_Start;
};