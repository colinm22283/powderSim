#pragma once

namespace Physics
{
    extern int boardWidth;
    extern int boardHeight;

    extern int** board;

    void resizeBoard(int w, int h);
    void init();
    void update();
    void render(int _x, int _y);
}