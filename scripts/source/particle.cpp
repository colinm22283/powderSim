#include "particle.h"

particle Particle::particles[5] = {
    { { 0, 0, 0, 0 }, MatterState::GAS, 0, "AIR", -1, -1, false },
    { { 255, 170, 90, 255 }, MatterState::DUST, 2, "SAND", -1, -1, false },
    { { 0, 0, 255, 255 }, MatterState::LIQUID, 1, "WATR", -1, -1, false },
    { { 255, 0, 0, 255 }, MatterState::PLASMA, 0.01, "FIRE", 10, 50, false },
    { { 255, 180, 100, 255 }, MatterState::DUST, 0.8, "DUST", -1, -1, true}
};

renderStyle Particle::style[5] = {
    { 0 },
    { 0 },
    { 0 },
    { 10 },
    { 0 }
};