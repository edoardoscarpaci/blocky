#include "pch.h"
#pragma once

using func = void (*)();

class callbackWrapper
{
public:
    virtual ~callbackWrapper() = default;
    virtual void execute() = 0;

protected:
    callbackWrapper();
};

template <class T>
class Callback : callbackWrapper
{
    using funWrapper = void (T::*)();

public:
    Callback(T *instance, funWrapper function) : m_Function(function), m_Instance(instance){};
    virtual void execute() { (m_Instance->*m_Function)(); };

    Callback(const Callback &callback) = default;
    Callback(Callback &&callback) = default;
    ~Callback(){};

private:
    funWrapper m_Function;
    T *m_Instance;
};