/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** WeaponType.component.hpp
*/

#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "ECS/Components.hpp"

namespace Rtype::Components
{
    enum WeaponType {
        BASIC,
        BIG
    };

    static const std::array<bool, 2> canCharge     = {false, true};
    static const std::array<int, 2>  chargeTimeLst = {0, 2000};
    static const std::array<int, 2>  damageLst     = {1, 2};
    static const std::array<int, 2>  durationLst   = {0, 5000};
    static const std::array<int, 2>  rateOfFireLst = {200, 1500};

    struct WeaponTypeComponent : ECS::BaseComponent {

            WeaponTypeComponent()
                : type(BASIC), isChargeable(canCharge[BASIC]), chargeTime(chargeTimeLst[BASIC]),
                  damage(damageLst[BASIC]), duration(durationLst[BASIC]), rateOfFire(rateOfFireLst[BASIC])
            {
            }

            explicit WeaponTypeComponent(WeaponType type)
                : type(type), isChargeable(canCharge[type]), chargeTime(chargeTimeLst[type]), damage(damageLst[type]),
                  duration(durationLst[type]), rateOfFire(rateOfFireLst[type])
            {
            }
            ~WeaponTypeComponent() override = default;

            void reset(WeaponType type)
            {
                this->type         = type;
                this->isChargeable = canCharge[type];
                this->chargeTime   = chargeTimeLst[type];
                this->damage       = damageLst[type];
                this->duration     = durationLst[type];
                this->rateOfFire   = rateOfFireLst[type];
            }

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&type), sizeof(type));
                oss.write(reinterpret_cast<const char *>(&isChargeable), sizeof(isChargeable));
                oss.write(reinterpret_cast<const char *>(&chargeTime), sizeof(chargeTime));
                oss.write(reinterpret_cast<const char *>(&damage), sizeof(damage));
                oss.write(reinterpret_cast<const char *>(&duration), sizeof(duration));
                oss.write(reinterpret_cast<const char *>(&rateOfFire), sizeof(rateOfFire));

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                WeaponTypeComponent *weaponTypeComponent;
                if (component == nullptr) {
                    weaponTypeComponent = new WeaponTypeComponent();
                } else {
                    weaponTypeComponent = dynamic_cast<WeaponTypeComponent *>(component);
                    if (weaponTypeComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->type), sizeof(weaponTypeComponent->type));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->isChargeable),
                         sizeof(weaponTypeComponent->isChargeable));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->chargeTime),
                         sizeof(weaponTypeComponent->chargeTime));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->damage), sizeof(weaponTypeComponent->damage));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->duration),
                         sizeof(weaponTypeComponent->duration));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->rateOfFire),
                         sizeof(weaponTypeComponent->rateOfFire));

                return weaponTypeComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::WeaponTypeComponent;
            }

            WeaponType type;
            bool       isChargeable = false;
            int        chargeTime   = 0;
            int        damage       = 0;
            int        duration     = 0;
            int        rateOfFire   = 0;
    };
} // namespace Rtype::Components
