/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Position.component.hpp
*/

#pragma once

#include <vector>
#include <sstream>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct TypeComponent : public ECS::BaseComponent {
            // TODO class vouée à être supprimée
        public:
            typedef enum entityType {
                player,
                wall,
                missile,
                enemy
            } entityType_t;

            explicit TypeComponent(entityType_t type) : type(type){};
            ~TypeComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                auto               typeInt = static_cast<std::underlying_type<entityType_t>::type>(type);
                oss.write(reinterpret_cast<const char *>(&typeInt), sizeof(typeInt));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr)
            {
                TypeComponent *typeComponent;
                if (component == nullptr) {
                    typeComponent = new TypeComponent(player); // 'player' est un choix par défaut
                } else {
                    typeComponent = dynamic_cast<TypeComponent *>(component);
                    if (typeComponent == nullptr) return nullptr;
                }

                std::istringstream                       iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                std::underlying_type<entityType_t>::type typeInt;
                iss.read(reinterpret_cast<char *>(&typeInt), sizeof(typeInt));
                typeComponent->type = static_cast<entityType_t>(typeInt);

                return typeComponent;
            }

            entityType_t type;
    };
} // namespace Engine::Components
