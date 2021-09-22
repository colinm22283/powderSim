#include "particle.h"

particle Particle::particles[3] = {
    { { 0, 0, 0, 0 }, MatterState::GAS, "Air" },
    { { 255, 170, 90, 255 }, MatterState::DUST, "Sand" },
    { { 0, 255, 0, 255 }, MatterState::LIQUID, "Water" }
};