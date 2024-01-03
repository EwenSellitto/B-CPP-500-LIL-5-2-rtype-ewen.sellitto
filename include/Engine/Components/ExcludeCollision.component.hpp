/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** ExcludeCollision.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
namespace Engine::Components
{
    class ExcludeCollisionComponent : public ECS::BaseComponent
    {
        public:
            ExcludeCollisionComponent(std::size_t id) : id(id) {}
            ~ExcludeCollisionComponent() override = default;

            std::vector<char> serialize(void) override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&id), sizeof(id));

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr)
            {
                ExcludeCollisionComponent *excludeCollisionComponent;
                if (component == nullptr) {
                    excludeCollisionComponent = new ExcludeCollisionComponent(0);
                } else {
                    excludeCollisionComponent = dynamic_cast<ExcludeCollisionComponent *>(component);
                    if (excludeCollisionComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&excludeCollisionComponent->id),
                         sizeof(excludeCollisionComponent->id));

                return excludeCollisionComponent;
            }

            std::size_t id;
    };
} // namespace Engine::Components
