#include "menu.h"
#include "render.h"
#include "global.h"

int Menu::items[3] = {
    0, 1, 2
};

void Menu::update()
{
    Render::setColor({ 255, 255, 255, 255 });
    Render::drawRect(Global::windowWidth - 100, 0, 100, Global::windowHeight);

    for (int i = 0; i < Menu::items; i++)
    {
        Render::drawRect(Global::windowWidth - 90, i * 25 + 10, 80, 20);
    }
}