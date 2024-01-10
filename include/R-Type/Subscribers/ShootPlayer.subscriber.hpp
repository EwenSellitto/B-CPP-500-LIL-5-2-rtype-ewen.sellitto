/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** PlayerMove.subscriber.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include <ctime>

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/LayeredRenderable.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"
#include "SFML/System/Clock.hpp"

namespace Rtype::Subscriber
{
    class ShootPlayerPressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            ShootPlayerPressedSubscriber() : _clock(){};
            ~ShootPlayerPressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override
            {
                using namespace Engine::Components;

                if (_clock.getElapsedTime().asMilliseconds() < 200) return;
                _clock.restart();
                if (data.keyEvent.code != sf::Keyboard::Space) return;
                Engine::System::MovePlayer *movePlayerSystem =
                    dynamic_cast<Engine::System::MovePlayer *>(WORLD.getSystems()["MovePlayer"].get());
                Engine::System::Bullets *bulletsSystem =
                    dynamic_cast<Engine::System::Bullets *>(WORLD.getSystems()["BulletsSystem"].get());

                std::vector<ECS::Entity *> players = WORLD.getEntitiesWithComponents<PlayerComponent>();
                ECS::Entity               *player  = nullptr;

                for (auto &p : players) {
                    if (!p->has<PlayerComponent>()) continue;
                    if (p->getComponent<PlayerComponent>()->playerNb ==
                        Engine::EngineClass::getEngine().getCurrentPlayer()) {
                        player = p;
                        break;
                    }
                }
                if (!player || !movePlayerSystem) return;

                ECS::ComponentHandle<Engine::Components::PositionComponent> pos =
                    player->getComponent<Engine::Components::PositionComponent>();
                ECS::ComponentHandle<Engine::Components::RenderableComponent> rend =
                    player->getComponent<Engine::Components::RenderableComponent>();
                bulletsSystem->spawnBullet(false, static_cast<float>(pos->x + static_cast<int>(rend->size.x / 2) - 20),
                                           static_cast<float>(pos->y + static_cast<int>(rend->size.x / 2) - 2),
                                           {1000, 0}, 200);
            }

        private:
            sf::Clock _clock;
    };

    class ShootPlayerReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            ShootPlayerReleasedSubscriber()           = default;
            ~ShootPlayerReleasedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                using namespace Engine::Components;

                if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                      data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                    return;
            }
    };
} // namespace Rtype::Subscriber
