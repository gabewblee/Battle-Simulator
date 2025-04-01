#ifndef MANAGER
#define MANAGER

#include "ScreenManager.h"

ScreenManager::ScreenManager(unsigned int width, unsigned int height) : window(sf::VideoMode({width, height}), "Battle Simulator") {}

#endif 