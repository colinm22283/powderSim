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
#include "font.h"
#include "particle.h"
#include "../header/menu.h"

bool erase = false;

void Script::exit()
{
    Console::print("Exit");

    Physics::destroy();

    Engine::quit = true;
}

void Script::keyDown(SDL_Keysym keysym) { }

float blockPos = 0;

void Script::start()
{
    Physics::init(350, 300);

    Global::fpsOutput = true;
}
void Script::update()
{
    Render::clearScreen({ 0, 0, 0, 255 });
    Physics::update();
    Physics::render(0, 0, ScriptGlobal::drawScale);

    Render::drawRect( // draw cursor
        Input::mouseX - (10 * ScriptGlobal::drawScale),
        Input::mouseY - (10 * ScriptGlobal::drawScale),
        20 * ScriptGlobal::drawScale, 20 * ScriptGlobal::drawScale, { 255, 255, 255, 255 }
    );

    Render::setColor({ 255, 255, 255, 255 });
    if (
        Input::mouseX > 0 && Input::mouseX < Physics::boardWidth * ScriptGlobal::drawScale &&
        Input::mouseY > 0 && Input::mouseY < Physics::boardHeight * ScriptGlobal::drawScale
    )
    {
        Render::drawText(
            5, 5, Font::consolas,
            Particle::particles[
                Physics::board[Input::mouseX / ScriptGlobal::drawScale][Input::mouseY / ScriptGlobal::drawScale]
            ].name + " (" +
                std::to_string(Input::mouseX / ScriptGlobal::drawScale) + ", " +
                std::to_string(Input::mouseY / ScriptGlobal::drawScale) + ")",
            0.7
        );
    }

    Menu::update();
}

void Script::mouseDown(int button)
{
    if (Input::mouseX / ScriptGlobal::drawScale < Physics::boardWidth)
    for (
        int i = std::max(0, Input::mouseX / ScriptGlobal::drawScale - 10);
        i < std::min(Physics::boardWidth, (int)(Input::mouseX / ScriptGlobal::drawScale + 10));
        i++
    ) {
        for (
            int j = std::max(0, Input::mouseY / ScriptGlobal::drawScale - 10);
            j < std::min(Physics::boardHeight, (int)(Input::mouseY / ScriptGlobal::drawScale + 10));
            j++
        ) {
            if (button == SDL_BUTTON_LEFT)
            {
                if (erase) Physics::createParticle(i, j, 0);
                else Physics::createParticle(i, j, Menu::selectedTool);
            }
        }
    }
}
void Script::mouseClick(int button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        Menu::onClick(Input::mouseX, Input::mouseY);
        break;
    case SDL_BUTTON_RIGHT:
        erase = !erase;
        break;
    }
}