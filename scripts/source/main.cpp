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
    Physics::init(100, 100);

    Global::fpsLimit = 20;
    Global::fpsOutput = true;
}
void Script::update()
{
    Render::clearScreen({ 0, 0, 0, 255 });
    Physics::update();
    Physics::render(0, 0, 5);
}

void Script::mouseDown(int button)
{
    for (
        int i = std::max(0, Input::mouseX / 5 - 10);
        i < std::min(Physics::boardWidth - 1, Input::mouseX / 5 + 10);
        i++
    ) {
        for (
            int j = std::max(0, Input::mouseY / 5 - 10);
            j < std::min(Physics::boardHeight - 1, Input::mouseY / 5 + 10);
            j++
        ) {
            Physics::board[i][j] = 1;
        }
    }
}
void Script::mouseClick(int button) { }