/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** PlayerMove.subscriber.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/LayeredRenderable.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/Components/WeaponType.component.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"
#include "SFML/System/Clock.hpp"

namespace Rtype::Subscriber
{
    static sf::Clock *_shared_clock = new sf::Clock();
    static bool       _reset        = false;

    class ChangeWeapon : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            ChangeWeapon() : _clock(){};
            ~ChangeWeapon() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override
            {
                if (!(_clock.getElapsedTime().asMilliseconds() >= 200 && data.keyEvent.code == sf::Keyboard::R)) return;
                auto player = WORLD.getEntityWithComponents<
                    Engine::Components::PositionComponent, Engine::Components::LayeredRenderableComponent,
                    Engine::Components::PlayerComponent, Components::WeaponTypeComponent>();

                if (!player) return;
                auto weapon = player->getComponent<Components::WeaponTypeComponent>();
                auto render = player->getComponent<Engine::Components::LayeredRenderableComponent>();
                weapon->reset(weapon->type == Components::WeaponType::BASIC ? Components::WeaponType::BIG
                                                                            : Components::WeaponType::BASIC);
                render->renderable[1]->isDisplayed = weapon->type == Components::WeaponType::BIG;
                render->renderable[2]->isDisplayed = weapon->type == Components::WeaponType::BASIC;
                _clock.restart();
            }

        private:
            sf::Clock _clock;
    };

    class ShootPlayerPressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            ShootPlayerPressedSubscriber() : _clock(){};
            ~ShootPlayerPressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string     &name,
                              [[maybe_unused]] const KeyPressedEvent &data) override
            {
                if (data.keyEvent.code == sf::Keyboard::Space && _reset) {
                    _shared_clock->restart();
                    _reset = false;
                }
            }

        private:
            sf::Clock _clock;
    };

    class ShootPlayerReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            ShootPlayerReleasedSubscriber() : _clock(){};
            ~ShootPlayerReleasedSubscriber() override = default;

            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                using namespace Engine::Components;

                if (data.keyEvent.code != sf::Keyboard::Space) return;
                Engine::System::MovePlayer *movePlayerSystem =
                    dynamic_cast<Engine::System::MovePlayer *>(WORLD.getSystems()["MovePlayer"].get());
                Engine::System::Bullets *bulletsSystem =
                    dynamic_cast<Engine::System::Bullets *>(WORLD.getSystems()["BulletsSystem"].get());

                std::vector<ECS::Entity *> players = WORLD.getEntitiesWithComponents<PlayerComponent>();
                ECS::Entity               *player  = nullptr;
                for (auto &p : players) {
                    if (p->getComponent<PlayerComponent>()->playerNb ==
                        Engine::EngineClass::getEngine().getCurrentPlayer()) {
                        player = p;
                        break;
                    }
                }

                if (!player || !movePlayerSystem) return;

                if (!player->has<Engine::Components::PositionComponent, Engine::Components::RenderableComponent,
                                 Components::WeaponTypeComponent>())
                    return;
                ECS::ComponentHandle<Engine::Components::PositionComponent> pos =
                    player->getComponent<Engine::Components::PositionComponent>();
                ECS::ComponentHandle<Engine::Components::RenderableComponent> rend =
                    player->getComponent<Engine::Components::RenderableComponent>();
                ECS::ComponentHandle<Components::WeaponTypeComponent> weapon =
                    player->getComponent<Components::WeaponTypeComponent>();
                fire(pos, rend, weapon, bulletsSystem);
                _reset = true;
            }

        private:
            sf::Clock _clock;

            void fire(ECS::ComponentHandle<Engine::Components::PositionComponent>   &pos,
                      ECS::ComponentHandle<Engine::Components::RenderableComponent> &rend,
                      ECS::ComponentHandle<Components::WeaponTypeComponent>         &weapon,
                      Engine::System::Bullets                                       *bulletsSystem)
            {
                switch (weapon->type) {
                    case Components::BASIC:
                        if (_clock.getElapsedTime().asMilliseconds() < Components::rateOfFireLst[Components::BASIC])
                            return;
                        bulletsSystem->spawnBullet(
                            false, static_cast<float>(pos->x + static_cast<int>(rend->size.x / 2) - 20),
                            static_cast<float>(pos->y + static_cast<int>(rend->size.x / 2) - 2), {1000, 0}, 200, 50);
                        break;
                    case Components::BIG:
                        if (_clock.getElapsedTime().asMilliseconds() < Components::rateOfFireLst[Components::BIG])
                            return;
                        bulletsSystem->spawnBigBullet(
                            false, static_cast<float>(pos->x + static_cast<int>(rend->size.x / 2) - 54),
                            static_cast<float>(pos->y + static_cast<int>(rend->size.x / 2) - 16), {1000, 0}, 200, 0,
                            200);
                        break;
                }
                _clock.restart();
            }
    };
} // namespace Rtype::Subscriber
