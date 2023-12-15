/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** test.cpp
*/

#include <iostream>
#include <iterator>

#include "ECS/Entity.hpp"
#include "ECS/World.hpp"
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

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    std::cout << typeid(Position).hash_code() << std::endl;
    std::cout << typeid(Hello).hash_code() << std::endl;

    ECS::World world;
    std::cout << world.getWorldTime() << std::endl;
    world.addEntity(std::make_unique<ECS::Entity>());

    TestEvent event{42};
    auto     *sub = new TestSubscriber();
    world.subscribe<TestEvent>(sub);
    try {
        world.broadcastEvent<TestEvent>(event);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    ECS::Entity &entity                = world.getMutEntity(0);
    bool         has_PositionComponent = entity.has<PositionComponent>();

    std::cout << "has PositionComponent " << has_PositionComponent << std::endl;
    entity.addComponent<PositionComponent>((PositionComponent){42, 64});

    has_PositionComponent                        = entity.has<PositionComponent>();
    ECS::ComponentHandle<PositionComponent> comp = entity.getComponent<PositionComponent>();
    std::cout << "has PositionComponent " << has_PositionComponent << std::endl;
    std::cout << world.getWorldTime() << std::endl;
    return (0);
}
