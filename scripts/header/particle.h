#pragma once

#include <string>

#include "color.h"

enum MatterState
{
    SOLID, DUST, LIQUID, GAS, PLASMA
};

struct particle
{
    color c;
    MatterState state;
    std::string name;
};

namespace Particle
{
    extern particle particles[3];
}