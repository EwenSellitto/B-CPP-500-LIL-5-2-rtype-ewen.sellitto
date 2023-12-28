/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/Animation.system.hpp"

#include <map>

#include "ECS/World.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace Engine::System;

void AnimationSystem::configure(ECS::World &world)
{
    nullptr;
}

void AnimationSystem::unconfigure()
{
    nullptr;
}

void AnimationSystem::tick()
{
    using namespace Engine::Components;

    ECS::World                                                           &world  = getWorld();
    sf::RenderWindow                                                     &window = WINDOW;
    std::map<int, std::vector<ECS::ComponentHandle<RenderableComponent>>> renderables{};
    std::map<int, std::vector<ECS::ComponentHandle<AnimationComponent>>>  animation{};
}
