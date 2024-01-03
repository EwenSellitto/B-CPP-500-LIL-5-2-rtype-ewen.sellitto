#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

struct WaitingRoom {
        std::vector<sf::IpAddress> players;
        bool                       inGame = false;

        void addPlayer(const sf::IpAddress &player)
        {
            players.push_back(player);
            // Vérifier si le nombre de joueurs est suffisant pour démarrer le jeu
            if (players.size() >= 2) {
                inGame = true;
                std::cout << "Salle d'attente complète, passage en mode INGAME." << std::endl;
                // Vous pouvez ici initialiser le jeu ou changer l'état des joueurs
            }
        }

        void removePlayer(const sf::IpAddress &player)
        {
            auto it = std::find(players.begin(), players.end(), player);
            if (it != players.end()) {
                players.erase(it);
                std::cout << "Joueur " << player << " supprimé de la salle d'attente" << std::endl;
            }
        }
};
