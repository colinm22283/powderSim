#include <iostream>
#include <memory>
#include <cstdint>
#include <math.h>

#include "physics.h"
#include "particle.h"
#include "render.h"
#include "engine.h"

int Physics::boardWidth = 0;
int Physics::boardHeight = 0;
int Physics::lifespanLength = 10;

int** Physics::board;
int** Physics::lifespan;

int lifespanClock = 0;

void Physics::init(int w, int h)
{
    Physics::boardWidth = w;
    Physics::boardHeight = h;

    Physics::board = (int**)malloc(sizeof(int*) * w);
    Physics::lifespan = (int**)malloc(sizeof(int*) * w);
    for (int i = 0; i < w; i++)
    {
        Physics::board[i] = (int*)malloc(sizeof(int) * h);
        Physics::lifespan[i] = (int*)malloc(sizeof(int) * h);
        for (int j = 0; j < h; j++)
        {
            Physics::board[i][j] = 0;
            Physics::lifespan[i][j] = -1;
        }
    }
}

void Physics::update()
{
    int* partBuf = (int*)malloc(sizeof(int) * 3);
    int* liqBuf = (int*)malloc(sizeof(int) * 9);
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
                        if (
                            x > 0 &&
                            Particle::particles[Physics::board[x - 1][y + 1]].weight < p.weight
                        ) { partBuf[temp] = 0; temp++; }
                        if (Particle::particles[Physics::board[x][y + 1]].weight < p.weight)
                        { partBuf[temp] = 1; temp++; }
                        if (
                            x < Physics::boardWidth - 1 &&
                            Particle::particles[Physics::board[x + 1][y + 1]].weight < p.weight
                        ) { partBuf[temp] = 2; temp++; }
                        if (temp > 0)
                        {
                            int sel = rand() % temp;

                            switch (partBuf[sel])
                            {
                                case 0:
                                {
                                    int temp2 = Physics::board[x][y];
                                    Physics::board[x][y] = Physics::board[x - 1][y + 1];
                                    Physics::board[x - 1][y + 1] = temp2;
                                    int temp3 = Physics::lifespan[x][y];
                                    Physics::lifespan[x][y] = Physics::lifespan[x - 1][y + 1];
                                    Physics::lifespan[x - 1][y + 1] = temp3;
                                    break;
                                }
                                case 1:
                                {
                                    int temp2 = Physics::board[x][y];
                                    Physics::board[x][y] = Physics::board[x][y + 1];
                                    Physics::board[x][y + 1] = temp2;
                                    int temp3 = Physics::lifespan[x][y];
                                    Physics::lifespan[x][y] = Physics::lifespan[x][y + 1];
                                    Physics::lifespan[x][y + 1] = temp3;
                                    break;
                                }
                                case 2:
                                {
                                    int temp2 = Physics::board[x][y];
                                    Physics::board[x][y] = Physics::board[x + 1][y + 1];
                                    Physics::board[x + 1][y + 1] = temp2;
                                    int temp3 = Physics::lifespan[x][y];
                                    Physics::lifespan[x][y] = Physics::lifespan[x + 1][y + 1];
                                    Physics::lifespan[x + 1][y + 1] = temp3;
                                    break;
                                }
                            }
                        }
                    }
                }
                else if (p.state == MatterState::LIQUID)
                {
                    int temp = 0;
                    if (x > 0 &&
                        Particle::particles[Physics::board[x - 1][y]].weight < p.weight
                    ) { for (int i = 0; i < 2; i++) { liqBuf[temp] = 0; temp++; } }
                    if (x > 0 && y < Physics::boardHeight - 1 &&
                        Particle::particles[Physics::board[x - 1][y + 1]].weight < p.weight
                    ) { for (int i = 0; i < 2; i++) { liqBuf[temp] = 1; temp++; } }
                    if (y < Physics::boardHeight - 1 &&
                        Particle::particles[Physics::board[x][y + 1]].weight < p.weight
                    ) { liqBuf[temp] = 2; temp++; }
                    if (x < Physics::boardWidth - 1 && y < Physics::boardHeight - 1 &&
                        Particle::particles[Physics::board[x + 1][y + 1]].weight < p.weight
                    ) { for (int i = 0; i < 2; i++) { liqBuf[temp] = 3; temp++; } }
                    if (x < Physics::boardWidth - 1 &&
                        Particle::particles[Physics::board[x + 1][y]].weight < p.weight
                    ) { for (int i = 0; i < 2; i++) { liqBuf[temp] = 4; temp++; } }
                    if (temp > 0)
                    {
                        int sel = rand() % temp;

                        switch (liqBuf[sel])
                        {
                            case 0:
                            {
                                int temp2 = Physics::board[x - 1][y];
                                Physics::board[x - 1][y] = Physics::board[x][y];
                                Physics::board[x][y] = temp2;
                                int temp3 = Physics::lifespan[x - 1][y];
                                Physics::lifespan[x - 1][y] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = temp3;
                                break;
                            }
                            case 1:
                            {
                                int temp2 = Physics::board[x - 1][y + 1];
                                Physics::board[x - 1][y + 1] = Physics::board[x][y];
                                Physics::board[x][y] = temp2;
                                int temp3 = Physics::lifespan[x - 1][y + 1];
                                Physics::lifespan[x - 1][y + 1] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = temp3;
                                break;
                            }
                            case 2:
                            {
                                int temp2 = Physics::board[x][y + 1];
                                Physics::board[x][y + 1] = Physics::board[x][y];
                                Physics::board[x][y] = temp2;
                                int temp3 = Physics::lifespan[x][y + 1];
                                Physics::lifespan[x][y + 1] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = temp3;
                                break;
                            }
                            case 3:
                            {
                                int temp2 = Physics::board[x + 1][y + 1];
                                Physics::board[x + 1][y + 1] = Physics::board[x][y];
                                Physics::board[x][y] = temp2;
                                int temp3 = Physics::lifespan[x + 1][y + 1];
                                Physics::lifespan[x + 1][y + 1] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = temp3;
                                break;
                            }
                            case 4:
                            {
                                int temp2 = Physics::board[x + 1][y];
                                Physics::board[x + 1][y] = Physics::board[x][y];
                                Physics::board[x][y] = temp2;
                                int temp3 = Physics::lifespan[x + 1][y];
                                Physics::lifespan[x + 1][y] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = temp3;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int x = 0; x < Physics::boardWidth; x++)
    {
        for (int y = 0; y < Physics::boardHeight; y++)
        {
            if (Physics::board[x][y] != 0)
            {
                particle p = Particle::particles[Physics::board[x][y]];
                
                if (p.state == MatterState::PLASMA)
                {
                    int temp = 0;
                    if (x > 0 && Physics::board[x - 1][y] == 0)
                    { liqBuf[temp] = 0; temp++; }
                    if (x > 0 && y > 0 && Physics::board[x - 1][y - 1] == 0)
                    { liqBuf[temp] = 1; temp++; }
                    if (y > 0 && Physics::board[x][y - 1] == 0)
                    { liqBuf[temp] = 2; temp++; }
                    if (x < Physics::boardWidth - 1 && y > 0 && Physics::board[x + 1][y - 1] == 0)
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
                                Physics::lifespan[x - 1][y] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = -1;
                                break;
                            }
                            case 1:
                            {
                                Physics::board[x - 1][y - 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                Physics::lifespan[x - 1][y - 1] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = -1;
                                break;
                            }
                            case 2:
                            {
                                Physics::board[x][y - 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                Physics::lifespan[x][y - 1] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = -1;
                                break;
                            }
                            case 3:
                            {
                                Physics::board[x + 1][y - 1] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                Physics::lifespan[x + 1][y - 1] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = -1;
                                break;
                            }
                            case 4:
                            {
                                Physics::board[x + 1][y] = Physics::board[x][y];
                                Physics::board[x][y] = 0;
                                Physics::lifespan[x + 1][y] = Physics::lifespan[x][y];
                                Physics::lifespan[x][y] = -1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    free(partBuf);
    free(liqBuf);

    lifespanClock += Engine::deltaTime;
    if (lifespanClock >= Physics::lifespanLength)
    {
        for (int i = 0; i < Physics::boardWidth; i++)
        {
            for (int j = 0; j < Physics::boardHeight; j++)
            {
                if (Physics::lifespan[i][j] > 0) Physics::lifespan[i][j]--;
                else
                {
                    if (Physics::lifespan[i][j] != -1)
                    {
                        Physics::board[i][j] = 0;
                        Physics::lifespan[i][j] = -1;
                    }
                }
            }
        }

        lifespanClock -= Physics::lifespanLength;
    }
}

void Physics::render(int _x, int _y, uint8_t scale)
{
    int** glowMap = (int**)malloc(sizeof(int*) * Physics::boardWidth);
    for (int i = 0; i < Physics::boardWidth; i++)
    {
        glowMap[i] = (int*)malloc(sizeof(int) * Physics::boardHeight);
        for (int j = 0; j < Physics::boardHeight; j++)
        {
            glowMap[i][j] = 0;
        }
    }

    for (int x = 0; x < Physics::boardWidth; x++)
    {
        for (int y = 0; y < Physics::boardHeight; y++)
        {
            if (Physics::board[x][y] != 0)
            {
                renderStyle style = Particle::style[Physics::board[x][y]];
                particle p = Particle::particles[Physics::board[x][y]];
                if (scale == 1)
                {
                    Render::drawPixel(x + _x, y + _y, p.c);
                    if (style.glow > 0 && false)
                    {
                        for (int i = x + _x - style.glow; i < x + _x + style.glow; i++)
                        {
                            for (int j = y + _y - style.glow; j < y + _y + style.glow; j++)
                            {
                                //glowMap[i][j];
                                Render::drawPixel(i, j, {
                                    255,
                                    0,
                                    0,
                                    (uint8_t)(sqrt(pow(i - x - _x, 2) + pow(j - y - _y, 2)) * 30)
                                });
                            }
                        }
                    }
                }
                else
                {
                    Render::fillRect(x * scale + _x, y * scale + _y, scale, scale, p.c);
                }
            }
        }
    }

    free(glowMap);
}

void Physics::createParticle(int x, int y, int id)
{
    Physics::board[x][y] = id;
    if (Particle::particles[id].lifespanMin == -1) Physics::lifespan[x][y] = -1;
    else Physics::lifespan[x][y] = (int)(
        rand() % (Particle::particles[id].lifespanMax - Particle::particles[id].lifespanMin) +
        Particle::particles[id].lifespanMin
    );
}

void Physics::destroy()
{
    free(Physics::board);
    free(Physics::lifespan);
}