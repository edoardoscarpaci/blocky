#include "pch.h"
#pragma once

class Dynamic
{
public:
    virtual void Update(float elapsedTime);

protected:
    Dynamic();
    virtual ~Dynamic();
};