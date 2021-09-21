#include <iostream>
#include <memory>

#include "physics.h"
#include "particle.h"
#include "render.h"

int Physics::boardWidth = 0;
int Physics::boardHeight = 0;
int** Physics::board;

void Physics::resizeBoard(int w, int h)
{
    Physics::boardWidth = w;
    Physics::boardHeight = h;

    free(Physics::board);

    Physics::board = (int**)malloc(sizeof(int*) * w);
    for (int i = 0; i < w; i++)
    {
        Physics::board[i] = (int*)malloc(sizeof(int) * h);
        for (int j = 0; j < h; j++) Physics::board[i][j] = 0;
    }
}

void Physics::init()
{
    Physics::resizeBoard(100, 100);
}

void Physics::update()
{
    int* partBuf = (int*)malloc(sizeof(int) * 3);
    for (int x = 0; x < Physics::boardWidth; x++)
    {
        for (int y = 0; y < Physics::boardHeight; y++)
        {
            if (Physics::board[x][y] != 0)
            {
                particle p = Particle::particles[Physics::board[x][y]];
                if (p.isPowder)
                {
                    std::cout << x << ", " << y << "\n";
                    int temp = 0;
                    if (Physics::board[x - 1][y - 1] == 0)
                    { partBuf[temp] = 0; temp++; }
                    if (Physics::board[x][y - 1] == 0)
                    { partBuf[temp] = 1; temp++; }
                    if (Physics::board[x + 1][y - 1] == 0)
                    { partBuf[temp] = 2; temp++; }
                    if (temp > 0)
                    {
                        std::cout << "test\n";
                        int sel = rand() % temp;

                        switch (partBuf[sel])
                        {
                            case 0:
                                Physics::board[x - 1][y - 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                            case 1:
                                Physics::board[x][y - 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                            case 2:
                                Physics::board[x + 1][y - 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                        }
                    }
                }
            }
        }
    }
    free(partBuf);
}

void Physics::render(int _x, int _y)
{
    for (int x = 0; x < Physics::boardWidth; x++)
    {
        for (int y = 0; y < Physics::boardHeight; y++)
        {
            if (Physics::board[x][y] != 0)
            {
                particle p = Particle::particles[Physics::board[x][y] - 1];
                Render::drawPixel(x + _x, y + _y, p.c);
            }
        }
    }
}