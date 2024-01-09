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
            bool      isDisplay;

            TextComponent(const std::string &str, const sf::Font newFont, unsigned int characterSize, sf::Vector2f pos,
                          bool centered = false, bool isDisplay = true)
                : isDisplay(isDisplay)
            {
                font = newFont;
                text.setString(str);
                text.setFont(font);
                text.setCharacterSize(characterSize);
                text.setPosition(pos);
                text.setFillColor(sf::Color::White);
                if (centered) {
                    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
                }
            }
            TextComponent(const std::string &str, const sf::Font newFont, unsigned int characterSize, sf::Vector2f pos,
                          const sf::Color &fillColor, bool centered = false, bool isDisplay = true)
                : isDisplay(isDisplay)
            {
                font = newFont;
                text.setString(str);
                text.setFont(font);
                text.setCharacterSize(characterSize);
                text.setPosition(pos);
                text.setFillColor(fillColor);
                if (centered) {
                    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
                }
            }
    };
} // namespace Engine::Components
