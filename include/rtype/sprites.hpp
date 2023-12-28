#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class SpriteData
{
    public:

        SpriteData() {
            initResources();
        }
        ~SpriteData() = default;

        std::map<std::string, sf::Texture> getTextures() const
        {
            return _textures;
        }

        std::map<std::string, sf::Sprite> getSprites() const
        {
            return _sprites;
        }

        void loadResources(const std::map<std::string, std::string>& files)
        {
            for (const auto& pair : files) {
                const std::string& name = pair.first;
                const std::string& file = pair.second;

                // Charge la texture et la stocke dans la map
                sf::Texture texture;
                if (!texture.loadFromFile(file)) {
                    std::cerr << "Failed to load texture: " << file << std::endl;
                    continue;
                }
                _textures[name] = std::move(texture);

                // Crée le sprite associé à la texture et le stocke dans la map
                sf::Sprite sprite;
                sprite.setTexture(_textures[name]);
                _sprites[name] = std::move(sprite);
            }
        }

            // Fonction pour configurer un sprite (position, rect, etc.)
        void configureSprite(const std::string& name, int width, int height, int offsetX, int offsetY)
        {
            if (_sprites.find(name) == _sprites.end()) {
                std::cerr << "Sprite not found: " << name << std::endl;
                return;
            }
            sf::Sprite& sprite = _sprites[name];
            sprite.setTextureRect(sf::IntRect(0, 0, width, height));
            sprite.setPosition(static_cast<float>(offsetX), static_cast<float>(offsetY));
        }

        void initResources()
        {
            std::map<std::string, std::string> files = {
                {"Asteroid-Flame", "./assets/Environnement/assets/Environnement/Asteroid-Flame.png"},
                {"Asteroid01-Base", "./assets/Environnement/assets/Environnement/Asteroid01-Base.png"},
                {"Asteroid01-Explode", "./assets/Environnement/assets/Environnement/Asteroid01-Explode.png"},
                {"Earth-Likeplanet-Withoutbackglow", "./assets/Environnement/assets/Environnement/Earth-Likeplanet-Withoutbackglow.png"},
                {"Earth-Likeplanet", "./assets/Environnement/assets/Environnement/Earth-Likeplanet.png"},
                {"Starrybackground-Layer01-Solidcolour", "./assets/Environnement/assets/Environnement/Starrybackground-Layer01-Solidcolour.png"},
                {"Starrybackground-Layer01-Void", "./assets/Environnement/assets/Environnement/Starrybackground-Layer01-Void.png"},
                {"Starrybackground-Layer02-Shadows", "./assets/Environnement/assets/Environnement/Starrybackground-Layer02-Shadows.png"},
                {"Starrybackground-Layer02-Shadows2", "./assets/Environnement/assets/Environnement/Starrybackground-Layer02-Shadows2.png"},
                {"Starrybackground-Layer02-Stars", "./assets/Environnement/assets/Environnement/Starrybackground-Layer02-Stars.png"},
                {"Starrybackground-Layer03-Stars", "./assets/Environnement/assets/Environnement/Starrybackground-Layer03-Stars.png"},
                {"Starrybackground-Layer03-Stars2", "./assets/Environnement/assets/Environnement/Starrybackground-Layer03-Stars2.png"},
                {"Starrybackground-LayerX-BigStar", "./assets/Environnement/assets/Environnement/Starrybackground-LayerX-BigStar.png"},
                {"Starrybackground-LayerX-BigStar2", "./assets/Environnement/assets/Environnement/Starrybackground-LayerX-BigStar2.png"},
                {"Starrybackground-LayerX-Blackhole", "./assets/Environnement/assets/Environnement/Starrybackground-LayerX-Blackhole.png"},
                {"Starrybackground-LayerX-RotaryStar", "./assets/Environnement/assets/Environnement/Starrybackground-LayerX-RotaryStar.png"},
                {"Starrybackground-LayerX-RotaryStar2", "./assets/Environnement/assets/Environnement/Starrybackground-LayerX-RotaryStar2.png"},
                {"Klaed-Battlecruiser-Base", "./assets/klaed/assets/klaed/Klaed-Battlecruiser-Base.png"},
                {"Klaed-Battlecruiser-Destruction", "./assets/klaed/assets/klaed/Klaed-Battlecruiser-Destruction.png"},
                {"Klaed-Battlecruiser-Engine", "./assets/klaed/assets/klaed/Klaed-Battlecruiser-Engine.png"},
                {"Klaed-Battlecruiser-Shield", "./assets/klaed/assets/klaed/Klaed-Battlecruiser-Shield.png"},
                {"Klaed-Battlecruiser-Weapons", "./assets/klaed/assets/klaed/Klaed-Battlecruiser-Weapons.png"},
                {"Klaed-BigBullet", "./assets/klaed/assets/klaed/Klaed-BigBullet.png"},
                {"Klaed-Bomber-Base", "./assets/klaed/assets/klaed/Klaed-Bomber-Base.png"},
                {"Klaed-Bomber-Destruction", "./assets/klaed/assets/klaed/Klaed-Bomber-Destruction.png"},
                {"Klaed-Bomber-Engine", "./assets/klaed/assets/klaed/Klaed-Bomber-Engine.png"},
                {"Klaed-Bomber-Shield", "./assets/klaed/assets/klaed/Klaed-Bomber-Shield.png"},
                {"Klaed-Dreadnought-Base", "./assets/klaed/assets/klaed/Klaed-Dreadnought-Base.png"},
                {"Klaed-Dreadnought-Destruction", "./assets/klaed/assets/klaed/Klaed-Dreadnought-Destruction.png"},
                {"Klaed-Dreadnought-Engine", "./assets/klaed/assets/klaed/Klaed-Dreadnought-Engine.png"},
                {"Klaed-Dreadnought-Shield", "./assets/klaed/assets/klaed/Klaed-Dreadnought-Shield.png"},
                {"Klaed-Dreadnought-Weapons", "./assets/klaed/assets/klaed/Klaed-Dreadnought-Weapons.png"},
                {"Klaed-Fighter-Base", "./assets/klaed/assets/klaed/Klaed-Fighter-Base.png"},
                {"Klaed-Fighter-Destruction", "./assets/klaed/assets/klaed/Klaed-Fighter-Destruction.png"},
                {"Klaed-Fighter-Engine", "./assets/klaed/assets/klaed/Klaed-Fighter-Engine.png"},
                {"Klaed-Fighter-Shield", "./assets/klaed/assets/klaed/Klaed-Fighter-Shield.png"},
                {"Klaed-Fighter-Weapons", "./assets/klaed/assets/klaed/Klaed-Fighter-Weapons.png"},
                {"Klaed-Frigate-Base", "./assets/klaed/assets/klaed/Klaed-Frigate-Base.png"},
                {"Klaed-Frigate-Destruction", "./assets/klaed/assets/klaed/Klaed-Frigate-Destruction.png"},
                {"Klaed-Frigate-Engine", "./assets/klaed/assets/klaed/Klaed-Frigate-Engine.png"},
                {"Klaed-Frigate-Shield", "./assets/klaed/assets/klaed/Klaed-Frigate-Shield.png"},
                {"Klaed-Frigate-Weapons", "./assets/klaed/assets/klaed/Klaed-Frigate-Weapons.png"},
                {"Klaed-Ray", "./assets/klaed/assets/klaed/Klaed-Ray.png"},
                {"Klaed-Scout-Base", "./assets/klaed/assets/klaed/Klaed-Scout-Base.png"},
                {"Klaed-Scout-Destruction", "./assets/klaed/assets/klaed/Klaed-Scout-Destruction.png"},
                {"Klaed-Scout-Engine", "./assets/klaed/assets/klaed/Klaed-Scout-Engine.png"},
                {"Klaed-Scout-Shield", "./assets/klaed/assets/klaed/Klaed-Scout-Shield.png"},
                {"Klaed-Scout-Weapons", "./assets/klaed/assets/klaed/Klaed-Scout-Weapons.png"},
                {"Klaed-Supportship-Base", "./assets/klaed/assets/klaed/Klaed-Supportship-Base.png"},
                {"Klaed-Supportship-Destruction", "./assets/klaed/assets/klaed/Klaed-Supportship-Destruction.png"},
                {"Klaed-Supportship-Engine", "./assets/klaed/assets/klaed/Klaed-Supportship-Engine.png"},
                {"Klaed-Torpedo", "./assets/klaed/assets/klaed/Klaed-Torpedo.png"},
                {"Klaed-TorpedoShip-Base", "./assets/klaed/assets/klaed/Klaed-TorpedoShip-Base.png"},
                {"Klaed-TorpedoShip-Destruction", "./assets/klaed/assets/klaed/Klaed-TorpedoShip-Destruction.png"},
                {"Klaed-TorpedoShip-Engine", "./assets/klaed/assets/klaed/Klaed-TorpedoShip-Engine.png"},
                {"Klaed-TorpedoShip-Shield", "./assets/klaed/assets/klaed/Klaed-TorpedoShip-Shield.png"},
                {"Klaed-TorpedoShip-Weapons", "./assets/klaed/assets/klaed/Klaed-TorpedoShip-Weapons.png"},
                {"Klaed-Wave", "./assets/klaed/assets/klaed/Klaed-Wave.png"},
                {"MainShip-Base-Damaged", "./assets/MainShip/assets/MainShip/MainShip-Base-Damaged.png"},
                {"MainShip-Base-Fullhealth", "./assets/MainShip/assets/MainShip/MainShip-Base-Fullhealth.png"},
                {"MainShip-Base-Slightdamage", "./assets/MainShip/assets/MainShip/MainShip-Base-Slightdamage.png"},
                {"MainShip-Base-Verydamaged", "./assets/MainShip/assets/MainShip/MainShip-Base-Verydamaged.png"},
                {"MainShip-Engines-BaseEngine-Idle", "./assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine-Idle.png"},
                {"MainShip-Engines-BaseEngine-Powering", "./assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine-Powering.png"},
                {"MainShip-Engines-BaseEngine", "./assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine.png"},
                {"MainShip-Engines-BigPulseEngine-Idle", "./assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine-Idle.png"},
                {"MainShip-Engines-BigPulseEngine-Powering", "./assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine-Powering.png"},
                {"MainShip-Engines-BigPulseEngine", "./assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine.png"},
                {"MainShip-Engines-BurstEngine-Idle", "./assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine-Idle.png"},
                {"MainShip-Engines-BurstEngine-Powering", "./assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine-Powering.png"},
                {"MainShip-Engines-BurstEngine", "./assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine.png"},
                {"MainShip-Engines-SuperchargedEngine-Idle", "./assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine-Idle.png"},
                {"MainShip-Engines-SuperchargedEngine-Powering", "./assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine-Powering.png"},
                {"MainShip-Engines-SuperchargedEngine", "./assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine.png"},
                {"MainShip-Shields-FrontandSideShield", "./assets/MainShip/assets/MainShip/MainShip-Shields-FrontandSideShield.png"},
                {"MainShip-Shields-FrontShield", "./assets/MainShip/assets/MainShip/MainShip-Shields-FrontShield.png"},
                {"MainShip-Shields-InvincibilityShield", "./assets/MainShip/assets/MainShip/MainShip-Shields-InvincibilityShield.png"},
                {"MainShip-Shields-RoundShield", "./assets/MainShip/assets/MainShip/MainShip-Shields-RoundShield.png"},
                {"MainShip-Weapons-AutoCannon", "./assets/MainShip/assets/MainShip/MainShip-Weapons-AutoCannon.png"},
                {"MainShip-Weapons-BigSpaceGun", "./assets/MainShip/assets/MainShip/MainShip-Weapons-BigSpaceGun.png"},
                {"MainShip-Weapons-Rockets", "./assets/MainShip/assets/MainShip/MainShip-Weapons-Rockets.png"},
                {"MainShip-Weapons-Zapper", "./assets/MainShip/assets/MainShip/MainShip-Weapons-Zapper.png"},
                {"MainshipWeapon-Projectile-Autocannonbullet", "./assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Autocannonbullet.png"},
                {"MainshipWeapon-Projectile-BigSpaceGun", "./assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-BigSpaceGun.png"},
                {"MainshipWeapon-Projectile-Rocket", "./assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Rocket.png"},
                {"MainshipWeapon-Projectile-Zapper", "./assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Zapper.png"},
                {"Nairan-Battlecruiser-Base", "./assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Base.png"},
                {"Nairan-Battlecruiser-Destruction", "./assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Destruction.png"},
                {"Nairan-Battlecruiser-Engine", "./assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Engine.png"},
                {"Nairan-Battlecruiser-Shield", "./assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Shield.png"},
                {"Nairan-Battlecruiser-Weapons", "./assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Weapons.png"},
                {"Nairan-Bolt", "./assets/Nairan/assets/Nairan/Nairan-Bolt.png"},
                {"Nairan-Bomber-Base", "./assets/Nairan/assets/Nairan/Nairan-Bomber-Base.png"},
                {"Nairan-Bomber-Destruction", "./assets/Nairan/assets/Nairan/Nairan-Bomber-Destruction.png"},
                {"Nairan-Bomber-Engine", "./assets/Nairan/assets/Nairan/Nairan-Bomber-Engine.png"},
                {"Nairan-Bomber-Shield", "./assets/Nairan/assets/Nairan/Nairan-Bomber-Shield.png"},
                {"Nairan-Dreadnought-Base", "./assets/Nairan/assets/Nairan/Nairan-Dreadnought-Base.png"},
                {"Nairan-Dreadnought-Destruction", "./assets/Nairan/assets/Nairan/Nairan-Dreadnought-Destruction.png"},
                {"Nairan-Dreadnought-Engine", "./assets/Nairan/assets/Nairan/Nairan-Dreadnought-Engine.png"},
                {"Nairan-Dreadnought-Shield", "./assets/Nairan/assets/Nairan/Nairan-Dreadnought-Shield.png"},
                {"Nairan-Dreadnought-Weapons", "./assets/Nairan/assets/Nairan/Nairan-Dreadnought-Weapons.png"},
                {"Nairan-Fighter-Base", "./assets/Nairan/assets/Nairan/Nairan-Fighter-Base.png"},
                {"Nairan-Fighter-Destruction", "./assets/Nairan/assets/Nairan/Nairan-Fighter-Destruction.png"},
                {"Nairan-Fighter-Engine", "./assets/Nairan/assets/Nairan/Nairan-Fighter-Engine.png"},
                {"Nairan-Fighter-Shield", "./assets/Nairan/assets/Nairan/Nairan-Fighter-Shield.png"},
                {"Nairan-Fighter-Weapons", "./assets/Nairan/assets/Nairan/Nairan-Fighter-Weapons.png"},
                {"Nairan-Frigate-Base", "./assets/Nairan/assets/Nairan/Nairan-Frigate-Base.png"},
                {"Nairan-Frigate-Destruction", "./assets/Nairan/assets/Nairan/Nairan-Frigate-Destruction.png"},
                {"Nairan-Frigate-Engine", "./assets/Nairan/assets/Nairan/Nairan-Frigate-Engine.png"},
                {"Nairan-Frigate-Shield", "./assets/Nairan/assets/Nairan/Nairan-Frigate-Shield.png"},
                {"Nairan-Frigate-Weapons", "./assets/Nairan/assets/Nairan/Nairan-Frigate-Weapons.png"},
                {"Nairan-Ray", "./assets/Nairan/assets/Nairan/Nairan-Ray.png"},
                {"Nairan-Rocket", "./assets/Nairan/assets/Nairan/Nairan-Rocket.png"},
                {"Nairan-Scout-Base", "./assets/Nairan/assets/Nairan/Nairan-Scout-Base.png"},
                {"Nairan-Scout-Destruction", "./assets/Nairan/assets/Nairan/Nairan-Scout-Destruction.png"},
                {"Nairan-Scout-Engine", "./assets/Nairan/assets/Nairan/Nairan-Scout-Engine.png"},
                {"Nairan-Scout-Shield", "./assets/Nairan/assets/Nairan/Nairan-Scout-Shield.png"},
                {"Nairan-Scout-Weapons", "./assets/Nairan/assets/Nairan/Nairan-Scout-Weapons.png"},
                {"Nairan-SupportShip-Base", "./assets/Nairan/assets/Nairan/Nairan-SupportShip-Base.png"},
                {"Nairan-SupportShip-Destruction", "./assets/Nairan/assets/Nairan/Nairan-SupportShip-Destruction.png"},
                {"Nairan-SupportShip-Engine", "./assets/Nairan/assets/Nairan/Nairan-SupportShip-Engine.png"},
                {"Nairan-Torpedo", "./assets/Nairan/assets/Nairan/Nairan-Torpedo.png"},
                {"Nairan-TorpedoShip-Base", "./assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Base.png"},
                {"Nairan-TorpedoShip-Destruction", "./assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Destruction.png"},
                {"Nairan-TorpedoShip-Engine", "./assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Engine.png"},
                {"Nairan-TorpedoShip-Shield", "./assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Shield.png"},
                {"Nairan-TorpedoShip-Weapons", "./assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Weapons.png"},
                {"PickupIcon-Engines-BaseEngine", "./assets/Pickup/assets/Pickup/PickupIcon-Engines-BaseEngine.png"},
                {"PickupIcon-Engines-BigPulseEngine", "./assets/Pickup/assets/Pickup/PickupIcon-Engines-BigPulseEngine.png"},
                {"PickupIcon-Engines-BurstEngine", "./assets/Pickup/assets/Pickup/PickupIcon-Engines-BurstEngine.png"},
                {"PickupIcon-Engines-SuperchargedEngine", "./assets/Pickup/assets/Pickup/PickupIcon-Engines-SuperchargedEngine.png"},
                {"PickupIcon-ShieldGenerator-Allaroundshield", "./assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-Allaroundshield.png"},
                {"PickupIcon-ShieldGenerator-FrontandSideShield", "./assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-FrontandSideShield.png"},
                {"PickupIcon-ShieldGenerator-FrontShield", "./assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-FrontShield.png"},
                {"PickupIcon-ShieldGenerator-InvincibilityShield", "./assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-InvincibilityShield.png"},
                {"PickupIcon-Weapons-AutoCannons", "./assets/Pickup/assets/Pickup/PickupIcon-Weapons-AutoCannons.png"},
                {"PickupIcon-Weapons-BigSpaceGun2000", "./assets/Pickup/assets/Pickup/PickupIcon-Weapons-BigSpaceGun2000.png"},
                {"PickupIcon-Weapons-Rockets", "./assets/Pickup/assets/Pickup/PickupIcon-Weapons-Rockets.png"},
                {"PickupIcon-Weapons-Zapper", "./assets/Pickup/assets/Pickup/PickupIcon-Weapons-Zapper.png"},
            };
            loadResources(files);
            configureSprite("Asteroid-Flame", 64, 64, 500, 500);
        }
    private:
        std::map<std::string, sf::Texture> _textures = {};
        std::map<std::string, sf::Sprite> _sprites = {};
};

// Plus tard dans votre code, vous pourriez charger toutes les ressources comme ceci :