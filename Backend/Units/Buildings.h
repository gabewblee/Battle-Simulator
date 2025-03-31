#ifndef BUILDING
#define BUILDING

#include "Entity.h"

class Building : public Entity {
public:
    Building(int ID, int team, int x, int y);

    virtual std::string getType() const override;
};

#endif