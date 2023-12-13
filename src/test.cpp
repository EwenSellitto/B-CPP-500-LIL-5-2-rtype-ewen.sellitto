/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** test.cpp
*/

#include "ECS/Entity.hpp"
#include "ECS/World.hpp"
#include "r-type.hpp"
#include <iostream>

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
    world.addEntity(std::make_unique<ECS::Entity>(world));
    ECS::Entity &entity        = world.getEntity(0);
    bool has_PositionComponent = entity.has<PositionComponent>();
    std::cout << "has PositionComponent " << has_PositionComponent << std::endl;
    entity.addComponent<PositionComponent>((PositionComponent){42, 64});
    has_PositionComponent                        = entity.has<PositionComponent>();
    ECS::ComponentHandle<PositionComponent> comp = entity.getComponent<PositionComponent>();
    std::cout << "has PositionComponent " << has_PositionComponent << std::endl;
    return (0);
}
