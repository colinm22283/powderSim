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
    bool flamable;
};

struct renderStyle
{
    int glow;
};

namespace Particle
{
    extern particle particles[5];
    extern renderStyle style[5];
}