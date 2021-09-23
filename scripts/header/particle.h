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
    float weight;
    std::string name;
    int lifespanMin;
    int lifespanMax;
};

struct renderStyle
{
    bool glow;
};

namespace Particle
{
    extern particle particles[4];
    extern renderStyle style[4];
}