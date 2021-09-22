#include "particle.h"

particle Particle::particles[3] = {
    { { 0, 0, 0, 0 }, MatterState::GAS, 0, "AIR" },
    { { 255, 170, 90, 255 }, MatterState::DUST, 2, "SAND" },
    { { 0, 0, 255, 255 }, MatterState::LIQUID, 1, "WATR" }
};