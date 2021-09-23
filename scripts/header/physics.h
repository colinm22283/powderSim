#pragma once

#include <cstdint>

namespace Physics
{
    extern int boardWidth;
    extern int boardHeight;

    extern int** board;
    extern int** lifespan;

    extern int lifespanLength;

    void init(int w, int h);
    void update();
    void render(int _x, int _y, uint8_t scale);
    void createParticle(int x, int y, int id);
    void destroy();
}