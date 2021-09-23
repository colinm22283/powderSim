#include "particle.h"

particle Particle::particles[4] = {
    { { 0, 0, 0, 0 }, MatterState::GAS, 0, "AIR", -1, -1 },
    { { 255, 170, 90, 255 }, MatterState::DUST, 2, "SAND", -1, -1 },
    { { 0, 0, 255, 255 }, MatterState::LIQUID, 1, "WATR", -1, -1 },
    { { 255, 0, 0, 255 }, MatterState::PLASMA, 0.1, "FIRE", 10, 50 }
};

renderStyle Particle::style[4] = {
    { 0 },
    { 0 },
    { 0 },
    { 10 }
};