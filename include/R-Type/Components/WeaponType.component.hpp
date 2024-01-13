/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** WeaponType.component.hpp
*/

#pragma once

#include <array>

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
    static const std::array<int, 2>  rateOfFireLst = {200, 1000};

    struct WeaponTypeComponent : ECS::BaseComponent {
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

            WeaponType type;
            bool       isChargeable = false;
            int        chargeTime   = 0;
            int        damage       = 0;
            int        duration     = 0;
            int        rateOfFire   = 0;
    };
} // namespace Rtype::Components
