// ParallaxComponent.hpp

#pragma once
#include "ECS/Components.hpp"

enum class ParallaxLayer {
    FarBackground, // Le fond le plus éloigné, qui bouge le plus lentement
    MidBackground, // Le fond intermédiaire
    NearBackground // Le fond le plus proche, qui bouge le plus vite
};

namespace Engine::Components
{
    struct ParallaxComponent : public ECS::BaseComponent {
        ParallaxLayer layer;
        float speed;
        sf::Vector2f offset; // Utilisé pour le calcul du décalage cumulé

        ParallaxComponent(ParallaxLayer layer, float speed)
            : layer(layer), speed(speed), offset(0, 0) {}
    };
} // namespace Engine::Components