#include "Engine/Systems/Inputs.system.hpp"

#include <algorithm>

#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/CheckBox.component.hpp"
#include "Engine/Components/Menu.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
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
    world.each<TextComponent, TextInputComponent>([&]([[maybe_unused]] ECS::Entity            *entity,
                                                      ECS::ComponentHandle<TextComponent>      textComp,
                                                      ECS::ComponentHandle<TextInputComponent> textInputComp) {
        if (textInputComp->isFocused && entity->has<TextComponent>()) {
            entity->getComponent<TextComponent>()->addText(text);
        }
    });
}

void InputsSystem::handleSend(std::vector<std::string> args)
{
    ECS::World &world = getWorld();
    world.each<TextComponent, TextInputComponent>([&]([[maybe_unused]] ECS::Entity            *entity,
                                                      ECS::ComponentHandle<TextComponent>      textComp,
                                                      ECS::ComponentHandle<TextInputComponent> textInputComp) {
        std::string id = textInputComp->text;
        if (entity->has<TextComponent>()) {
            if (std::find(args.begin(), args.end(), id) != args.end())
                std::cout << id << ": " << entity->getComponent<TextComponent>()->content << std::endl;
        }
    });
}
