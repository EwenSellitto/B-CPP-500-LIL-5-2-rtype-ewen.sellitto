#include "Engine/Systems/Inputs.system.hpp"

#include <algorithm>
#include <iostream>

#include "ECS/World.hpp"
#include "Engine/Components/Text.component.hpp"
#include "Engine/Components/TextInput.component.hpp"

using namespace Engine::System;
using namespace Engine::Components;

void InputsSystem::configure([[maybe_unused]] ECS::World &world) {}

void InputsSystem::unconfigure() {}

void InputsSystem::tick() {}

void InputsSystem::changeText(std::string &text)
{
    ECS::World &world = getWorld();
    world.each<TextComponent, TextInputComponent>([&]([[maybe_unused]] ECS::Entity                        *entity,
                                                      [[maybe_unused]] ECS::ComponentHandle<TextComponent> textComp,
                                                      ECS::ComponentHandle<TextInputComponent> textInputComp) {
        if (textInputComp->isFocused && entity->has<TextComponent>()) {
            if (entity->getComponent<TextComponent>()->content.size() <= 15)
                entity->getComponent<TextComponent>()->addText(text);
        }
    });
}

void InputsSystem::removeText()
{
    ECS::World &world = getWorld();
    world.each<TextComponent, TextInputComponent>([&]([[maybe_unused]] ECS::Entity                        *entity,
                                                      [[maybe_unused]] ECS::ComponentHandle<TextComponent> textComp,
                                                      ECS::ComponentHandle<TextInputComponent> textInputComp) {
        if (textInputComp->isFocused && entity->has<TextComponent>()) {
            if (entity->getComponent<TextComponent>()->content.size() > 0)
                entity->getComponent<TextComponent>()->removeText();
        }
    });
}

void InputsSystem::handleSend(std::vector<std::string> args)
{
    ECS::World &world = getWorld();
    world.each<TextComponent, TextInputComponent>([&]([[maybe_unused]] ECS::Entity                        *entity,
                                                      [[maybe_unused]] ECS::ComponentHandle<TextComponent> textComp,
                                                      ECS::ComponentHandle<TextInputComponent> textInputComp) {
        std::string id = textInputComp->text;
        if (entity->has<TextComponent>()) {
            if (std::find(args.begin(), args.end(), id) != args.end())
                std::cout << "id :" << entity->getComponent<TextComponent>()->content << std::endl;
        }
    });
}
