#include <string>

#include "../header/menu.h"
#include "render.h"
#include "global.h"
#include "font.h"
#include "../header/particle.h"

int Menu::selectedTool = 1;
int Menu::items[3] = {
    0, 1, 2
};

void Menu::update()
{
    Render::setColor({ 255, 255, 255, 255 });
    Render::drawRect(Global::windowWidth - 100, 0, 100, Global::windowHeight, { 0, 0, 0, 255 });
    Render::drawRect(Global::windowWidth - 100, 0, 100, Global::windowHeight);

    for (int i = 0; i < (int)(sizeof(Menu::items) / sizeof(int)); i++)
    {
        Render::drawRect(Global::windowWidth - 90, i * 25 + 10, 80, 20);
        Render::drawText(Global::windowWidth - 85, i * 25 + 11, Font::consolas, Particle::particles[i].name, 0.9);
    }
}

void Menu::onClick(int x, int y)
{
    for (int i = 0; i < (int)(sizeof(Menu::items) / sizeof(int)); i++)
    {
        if (
            x >= Global::windowWidth - 90 && x <= Global::windowWidth - 10 &&
            y >= i * 25 + 10 && i * 25 + 30
        )
        {
            selectedTool = Menu::items[i];
            break;
        }
    }
}