#pragma once

#include "color.h"

struct particle
{
    color c;
    int weight;
    bool isPowder;
};

namespace Particle
{
    extern particle particles[1];
}