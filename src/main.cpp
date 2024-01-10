/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** main.cpp
*/

#include <SFML/Window/Event.hpp>

#include "Engine/Engine.hpp"
#include "R-Type/GameWorld/GameWorld.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv, [[maybe_unused]] char **env)
{
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();

    try {
        engine.setStartWorld("chooseIP");
        engine.addWorldFactory("menu", GameWorld::createMenuWorld);
        engine.addWorldFactory("game", GameWorld::createGameWorld);
        engine.addWorldFactory("chooseIP", GameWorld::createChooseIP);

        engine.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
