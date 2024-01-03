/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** main.cpp
*/

#include <SFML/Window/Event.hpp>
#include <thread>

#include "Engine/Engine.hpp"
#include "R-Type/GameWorld/GameWorld.hpp"
#include "Server/Server.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv, [[maybe_unused]] char **env) {
    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
    Server server(9555);

    // Création du thread pour le serveur
    std::thread serverThread([&](){
        server.run();
    });

    try {
        engine.setStartWorld("menu");
        GameWorld::createMenuWorld(engine);
        engine.addWorldFactory("game", GameWorld::createGameWorld);
        engine.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    // Attendre la fin du thread du serveur avant de fermer l'application
    serverThread.join();

    return 0;
}

