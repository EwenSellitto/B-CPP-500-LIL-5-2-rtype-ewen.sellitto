/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Engine.hpp
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstddef>
#include <functional>
#include <memory>
#include <unordered_map>

#include "ECS/Entity.hpp"

namespace ECS
{
    class World;
}

#define SHOW_HITBOX

#ifndef DEFAULT_WINDOW_SIZE_X
#define DEFAULT_WINDOW_SIZE_X 800
#endif

#ifndef DEFAULT_WINDOW_SIZE_Y
#define DEFAULT_WINDOW_SIZE_Y 600
#endif

#ifndef DEFAULT_WINDOW_NAME
#define DEFAULT_WINDOW_NAME "default"
#endif

#ifndef BIND_F11_TO_OTHER
#define BIND_F11_TO_FULLSCREEN
#endif

#ifndef BIND_ESC_TO_OTHER
#define BIND_ESC_TO_QUIT
#endif

#ifndef DONT_ADD_RENDERER_SYSTEM
#define ADD_RENDERER_SYSTEM
#endif

#define WINDOW Engine::EngineClass::getEngine().window
#define WORLD Engine::EngineClass::getEngine().world()

namespace Engine
{
    typedef std::unordered_map<std::string, std::function<ECS::World *()>> world_factories_t;
    typedef std::pair<std::string, ECS::World *>                           world_t;

    class EngineClass
    {
        public:
            /*===================//
            //  Singleton Logic  //
            //===================*/

            static EngineClass &getEngine();
            static EngineClass &getEngine(std::size_t x, std::size_t y, std::string name);

            EngineClass &operator=(const EngineClass &engine) = delete;
            EngineClass(const EngineClass &engine)            = delete;

        private:
            /*============================//
            //  Constructor / Destructor  //
            //============================*/

            EngineClass(std::size_t x = DEFAULT_WINDOW_SIZE_X, std::size_t y = DEFAULT_WINDOW_SIZE_Y,
                        std::string name = DEFAULT_WINDOW_NAME, std::string start_world = DEFAULT_WINDOW_NAME);

            ~EngineClass();

        public:
            /*===================//
            //  Getters/Setters  //
            //===================*/

            void setStartWorld(const std::string &name);

            std::size_t getWindowSizeX();
            std::size_t getWindowSizeY();

            /*===================//
            //  Worlds Handling  //
            //===================*/

            void createEmptyWorld(std::string name);

            void addWorldFactory(std::string name, std::function<ECS::World *()>);

            void switchWorld(std::string name);

            std::vector<std::string> getWorldsNames();

            ECS::World &world();

            /*=================//
            //  General Logic  //
            //=================*/

            void run();

            void toggleFullscreen();

            /*==================//
            //  Event Handling  //
            //==================*/

            void handleEvents();

            /*=====================//
            //  Public Attributes  //
            //=====================*/

            sf::RenderWindow window;

            /*===================//
            //  Private Methods  //
            //===================*/

            id_t                     addGlobalEntity(std::unique_ptr<ECS::GlobalEntity> entity);
            void                     removeGlobalEntity(id_t id);
            const ECS::GlobalEntity &getGlobalEntity(id_t id);
            ECS::GlobalEntity       &getMutGlobalEntity(id_t id);

            template <typename T> std::unordered_map<ECS::GlobalEntity *, ECS::ComponentHandle<T>> getGlobal();

            template <typename T> void each(std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<T>)> func);

            template <typename... Types>
            void each(std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<Types...>)> func);

            template <typename... Types> std::vector<ECS::GlobalEntity *> getGlobalEntitiesWithComponents();
            template <typename... Types> ECS::GlobalEntity               *getGlobalEntityWithComponents();

        private:
            /*==============//
            //  Attributes  //
            //==============*/

            bool                                                         _running;
            bool                                                         _fullscreen;
            world_factories_t                                            _worldsFactories;
            world_t                                                      _currentWorld;
            std::vector<world_t>                                         _pending_destroy;
            std::string                                                  _startWorld;
            std::size_t                                                  _windowSizeX;
            std::size_t                                                  _windowSizeY;
            std::unordered_map<id_t, std::unique_ptr<ECS::GlobalEntity>> _global_entities;

            /*===================//
            //  Private Methods  //
            //===================*/

            void destroyPendingWorlds();

            template <typename T>
            void _eachHelper(ECS::GlobalEntity                                                *g_entity,
                             std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<T>)> func);

            template <typename T, typename V, typename... Types>
            void _eachHelper(ECS::GlobalEntity                                                *g_entity,
                             std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<T>)> func);
    };
} // namespace Engine
