#include <iostream>
#include <memory>
#include <cstdint>

#include "physics.h"
#include "particle.h"
#include "render.h"

int Physics::boardWidth = 0;
int Physics::boardHeight = 0;
int** Physics::board;

void Physics::init(int w, int h)
{
    Physics::boardWidth = w;
    Physics::boardHeight = h;

    Physics::board = (int**)malloc(sizeof(int*) * w);
    for (int i = 0; i < w; i++)
    {
        Physics::board[i] = (int*)malloc(sizeof(int) * h);
        for (int j = 0; j < h; j++) Physics::board[i][j] = 0;
    }
}

void Physics::update()
{
    int* partBuf = (int*)malloc(sizeof(int) * 3);
    int* liqBuf = (int*)malloc(sizeof(int) * 5);
    for (int x = 0; x < Physics::boardWidth; x++)
    {
        for (int y = Physics::boardHeight - 1; y >= 0; y--)
        {
            if (Physics::board[x][y] != 0)
            {
                particle p = Particle::particles[Physics::board[x][y]];
                
                if (p.state == MatterState::DUST)
                {
                    if (y < Physics::boardHeight - 1)
                    {
                        int temp = 0;
                        if (x > 0 && Physics::board[x - 1][y + 1] == 0)
                        { partBuf[temp] = 0; temp++; }
                        if (Physics::board[x][y + 1] == 0)
                        { partBuf[temp] = 1; temp++; }
                        if (x < Physics::boardWidth - 1 && Physics::board[x + 1][y + 1] == 0)
                        { partBuf[temp] = 2; temp++; }
                        if (temp > 0)
                        {
                            int sel = rand() % temp;

                            switch (partBuf[sel])
                            {
                                case 0:
                                {
                                    Physics::board[x - 1][y + 1] = Physics::board[x][y];
                                    Physics::board[x][y] = 0;
                                    break;
                                }
                                case 1:
                                {
                                    Physics::board[x][y + 1] = Physics::board[x][y];
                                    Physics::board[x][y] = 0;
                                    break;
                                }
                                case 2:
                                {
                                    Physics::board[x + 1][y + 1] = Physics::board[x][y];
                                    Physics::board[x][y] = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                else if (p.state == MatterState::LIQUID)
                {
                    int temp = 0;
                    if (x > 0 && Physics::board[x - 1][y] == 0)
                    { liqBuf[temp] = 0; temp++; }
                    if (x > 0 && y < Physics::boardHeight - 1 && Physics::board[x - 1][y + 1] == 0)
                    { liqBuf[temp] = 1; temp++; }
                    if (y < Physics::boardHeight - 1 && Physics::board[x][y + 1] == 0)
                    { liqBuf[temp] = 2; temp++; }
                    if (x < Physics::boardWidth - 1 && y < Physics::boardHeight - 1 && Physics::board[x + 1][y + 1] == 0)
                    { liqBuf[temp] = 3; temp++; }
                    if (x < Physics::boardWidth - 1 && Physics::board[x + 1][y] == 0)
                    { liqBuf[temp] = 4; temp++; }
                    if (temp > 0)
                    {
                        int sel = rand() % temp;

                        switch (liqBuf[sel])
                        {
                            case 0:
                            {
                                Physics::board[x - 1][y] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                            }
                            case 1:
                            {
                                Physics::board[x - 1][y + 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                            }
                            case 2:
                            {
                                Physics::board[x][y + 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                            }
                            case 3:
                            {
                                Physics::board[x + 1][y + 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                            }
                            case 4:
                            {
                                Physics::board[x + 1][y] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    free(partBuf);
}

void Physics::render(int _x, int _y, uint8_t scale)
{
    for (int x = 0; x < Physics::boardWidth; x++)
    {
        for (int y = 0; y < Physics::boardHeight; y++)
        {
            if (Physics::board[x][y] != 0)
            {
                particle p = Particle::particles[Physics::board[x][y]];
                if (scale == 1) Render::drawPixel(x + _x, y + _y, p.c);
                else
                {
                    Render::fillRect(x * scale + _x, y * scale + _y, scale, scale, p.c);
                }
            }
        }
    }
}