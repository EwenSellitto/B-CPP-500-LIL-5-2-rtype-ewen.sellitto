/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** test.cpp
*/

#include <iostream>

#include "ECS/Entity.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Systems/Server.system.hpp"
#include "r-type.hpp"

struct TestEvent {
        int x;
};

class TestSubscriber : public virtual ECS::EventSubscriber<TestEvent>
{
    public:
        TestSubscriber()  = default;
        ~TestSubscriber() = default;
        void receiveEvent(const std::string &name, const TestEvent &data) override
        {
            std::cout << "TestSubscriber received event " << name << std::endl;
            std::cout << "Entity id: " << data.x << std::endl;
        }
};

struct Position {
        float x;
        float y;
};

struct Hello : public Position {
};

void runServer()
{
    ECS::World             world;
    Engine::System::Server server(world);
    server.configure(world);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    std::thread serverThread(runServer);
    while (true) {
        std::cout << "Programme principal en cours d'exécution." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    // Rejoindre le thread du serveur avant de quitter le programme
    serverThread.join();
    return (0);
}
