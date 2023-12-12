/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** test.cpp
*/

#include "r-type.hpp"

struct Position {
        float x;
        float y;
};

struct Hello : public Position {
};

int main(int argc, char **argv)
{
    std::cout << typeid(Position).hash_code() << std::endl;
    std::cout << typeid(Hello).hash_code() << std::endl;

    ECS::World world;
    world.addEntity(std::make_unique<ECS::Entity>(world));
    ECS::Entity &entity        = world.getEntity(0);
    bool has_PositionComponent = entity.has<ECS::PositionComponent>();
    std::cout << "has PositionComponent " << has_PositionComponent << std::endl;
    entity.addComponent<ECS::PositionComponent>((ECS::PositionComponent){42, 64});
    has_PositionComponent                             = entity.has<ECS::PositionComponent>();
    ECS::ComponentHandle<ECS::PositionComponent> comp = entity.getComponent<ECS::PositionComponent>();
    std::cout << "has PositionComponent " << has_PositionComponent << std::endl;
    return (0);
}
