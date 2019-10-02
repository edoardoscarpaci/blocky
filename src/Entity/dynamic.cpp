#include "Entity/dynamic.hpp"
#include "util/gamemanager.hpp"

Dynamic::Dynamic()
{
    GameManager::getInstance()->UpdateEntity(this);
}

Dynamic::~Dynamic(){};
void Dynamic::Update(float elapsedTime){};
