#include <string>
#include <map>
#include <iostream>
#include "SDL/SDL.h"

#include "consoleParser.h"
#include "script.h"
#include "console.h"
#include "engine.h"
#include "global.h"

std::string bindMap[255];

bool ConsoleParser::parse(std::string code)
{
    std::string first = code.substr(0, code.find(' '));

    if (first == "exit")
    {
        Script::exit();
    }
    else if (first == "set")
    {
        std::string nstr = code.substr(code.find(' ') + 1);
        std::string second = nstr.substr(0, nstr.find(' '));
        std::string nstr2 = nstr.substr(nstr.find(' ') + 1);
        std::string third = nstr2.substr(0, nstr2.find(' '));
        if (second == "resx")
        {
            int w = std::stoi(third);
            int h;
            SDL_GetWindowSize(window, NULL, &h);
            SDL_SetWindowSize(window, w, h);
            Global::windowWidth = w;
        }
        else if (second == "resy")
        {
            int w;
            int h = std::stoi(third);
            SDL_GetWindowSize(window, &w, NULL);
            SDL_SetWindowSize(window, w, h);
            Global::windowHeight = h;
        }
        else if (second == "fpslimit") Global::fpsLimit = std::stoi(third);
        else if (second == "fpsoutput") Global::fpsOutput = third == "true";
        else if (second == "printkeys") Global::printKeys = third == "true";
        else Console::print("Variable \"" + second + "\" does not exist.");
    }
    else if (first == "bind")
    {
        std::string nstr = code.substr(code.find(' ') + 1);
        std::string second = nstr.substr(0, nstr.find(' '));
        std::string third = nstr.substr(nstr.find(' ') + 1);

        bindMap[(int)second[0]] = third;
    }
    else if (first == "time")
    {
        Console::print(std::to_string(Engine::currentTime));
    }
    else
    {
        Console::print("Command not found \"" + first + "\"");
        return false;
    }

    return true;
}

void ConsoleParser::keyDown(SDL_Keysym keysym)
{
    if ((int)keysym.sym >= 255) return;
    std::string temp = bindMap[(int)keysym.sym];
    if (temp != "") ConsoleParser::parse(temp);
}