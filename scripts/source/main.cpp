#include <math.h>
#include <iostream>

#include "global.h"
#include "script.h"
#include "engine.h"
#include "console.h"
#include "render.h"
#include "input.h"
#include "physics.h"
#include "consoleParser.h"

void Script::exit()
{
    Console::print("Exit");
    Engine::quit = true;
}

void Script::keyDown(SDL_Keysym keysym) { }

float blockPos = 0;

void Script::start()
{
    Physics::init();
    for (int i = 40; i < 60; i++)
    {
        for (int j = 40; j < 60; j++)
        {
            Physics::board[i][j] = 1;
        }
    }
}
void Script::update()
{
    Physics::update();
    Physics::render(0, 0);
}

void Script::mouseDown(int button) { }
void Script::mouseClick(int button) { }