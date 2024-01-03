#pragma once
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <string>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Text.hpp"

namespace Engine::Components
{
    struct TextComponent : public ECS::BaseComponent {
            sf::Text  text;
            sf::Font  font;
            sf::Color fillColor;

            TextComponent(const std::string &str, const sf::Font newFont, unsigned int characterSize, sf::Vector2f pos)
            {
                font = newFont;
                text.setString(str);
                text.setFont(font);
                text.setCharacterSize(characterSize);
                text.setPosition(pos);
                text.setFillColor(sf::Color::White);
            }
            TextComponent(const std::string &str, const sf::Font newFont, unsigned int characterSize, sf::Vector2f pos,
                          const sf::Color &fillColor, bool centered = false)
            {
                font = newFont;
                if (centered) {
                    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
                }
                text.setString(str);
                text.setFont(font);
                text.setCharacterSize(characterSize);
                text.setPosition(pos);
                text.setFillColor(fillColor);
            }
    };
} // namespace Engine::Components
