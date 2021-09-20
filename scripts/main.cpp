#include <math.h>
#include <iostream>

#include "global.h"
#include "script.h"
#include "engine.h"
#include "console.h"
#include "render.h"
#include "input.h"

void Script::exit()
{
    Console::print("Exit");
    Engine::quit = true;
}

void Script::keyDown(SDL_Keysym keysym)
{
    Console::print("Key: " + std::to_string(keysym.sym));
}

float blockPos = 0;

void Script::start() { }
void Script::update()
{
    Render::clearScreen({ 255, 255, 255, 255 });

    Render::setColor({0, 0, 0, 255 });
    Render::fillRect(cos(blockPos) * 200 + 300, sin(blockPos) * 200 + 300, 50, 50);
    Render::fillRect(Input::mouseX - 20, Input::mouseY - 20, 40, 40);

    blockPos += 0.001 * PI * Engine::deltaTime;
}

void Script::mouseDown(int button) { }
void Script::mouseClick(int button) { }