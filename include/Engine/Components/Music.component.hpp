/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Audio.hpp>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct MusicComponent : public ECS::BaseComponent {
        public:
            MusicComponent(std::string path, float _volume = 50) : _volume(_volume)
            {
                music.openFromFile(path);
                music.setVolume(_volume);
                music.setLoop(true);
                music.play();
            }

            ~MusicComponent() override = default;

            float     _volume;
            sf::Music music;
    };
} // namespace Engine::Components
