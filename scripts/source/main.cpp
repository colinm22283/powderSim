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
#include "scriptGlobal.h"

bool erase = false;

void Script::exit()
{
    Console::print("Exit");
    Engine::quit = true;
}

void Script::keyDown(SDL_Keysym keysym) { }

float blockPos = 0;

void Script::start()
{
    Physics::init(200, 150);

    Global::fpsOutput = true;
}
void Script::update()
{
    Render::clearScreen({ 0, 0, 0, 255 });
    Physics::update();
    Physics::render(0, 0, ScriptGlobal::drawScale);

    Render::drawRect(
        Input::mouseX - (10 * ScriptGlobal::drawScale),
        Input::mouseY - (10 * ScriptGlobal::drawScale),
        20 * ScriptGlobal::drawScale, 20 * ScriptGlobal::drawScale, { 255, 255, 255, 255 }
    );
}

void Script::mouseDown(int button)
{
    for (
        int i = std::max(0, Input::mouseX / ScriptGlobal::drawScale - 10);
        i < std::min(Physics::boardWidth - 1, Input::mouseX / ScriptGlobal::drawScale + 10);
        i++
    ) {
        for (
            int j = std::max(0, Input::mouseY / ScriptGlobal::drawScale - 10);
            j < std::min(Physics::boardHeight - 1, Input::mouseY / ScriptGlobal::drawScale + 10);
            j++
        ) {
            if (button == SDL_BUTTON_LEFT)
            {
                if (erase) Physics::board[i][j] = 0;
                else Physics::board[i][j] = 1;
            }
        }
    }
}
void Script::mouseClick(int button)
{
    if (button == SDL_BUTTON_RIGHT)
    {
        erase = !erase;
    }
}