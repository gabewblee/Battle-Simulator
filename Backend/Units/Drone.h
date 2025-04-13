#ifndef DRONE_H
#define DRONE_H

#include "Unit.h"

class Drone : public Unit {
public:
    Drone(int team, int x, int y);
};

#endif