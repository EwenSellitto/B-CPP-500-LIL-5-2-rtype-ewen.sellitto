cmake_minimum_required(VERSION 3.20.5)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(R-TYPE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -std=c++20 -O2")

include_directories(include)

find_package(SFML 2.6 COMPONENTS graphics network QUIET)

if (NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif ()

# if (NOT LIBCONFIG_FOUND)
#     include(FetchContent)
#     FetchContent_Declare(LIBCONFIG
#             GIT_REPOSITORY https://github.com/hyperrealm/libconfig.git
#             GIT_TAG master)
#     FetchContent_MakeAvailable(LIBCONFIG)
# endif()

add_executable(r-type
        include/ECS/Components.hpp
        include/ECS/EventSubscriber.hpp
        include/ECS/Clock.hpp
        include/ECS/System.hpp
        include/ECS/World.hpp
        include/ECS/Entity.hpp
        include/ECS/Utilities.hpp
        include/R-Type/GameWorld/GameWorld.hpp
        include/R-Type/GameWorld/Entities.hpp
        include/R-Type/GameWorld/EnemyMakers.hpp
        include/R-Type/GameWorld/Subscribers.hpp
        include/R-Type/GameWorld/Systems.hpp

        include/Engine/Systems/UI.system.hpp
        include/Engine/Systems/Renderer.system.hpp
        include/Engine/Systems/Physics.system.hpp
        include/Engine/Systems/Parallax.system.hpp
        include/Engine/Systems/WorldMove.system.hpp
        include/Engine/Systems/Animation.system.hpp
        include/Engine/Components/Button.component.hpp
        include/Engine/Components/Renderable.component.hpp
        include/R-Type/Components/Enemy.component.hpp
        include/Engine/Components/View.component.hpp
        include/Engine/Components/Moving.component.hpp
        include/Engine/Components/Collision.component.hpp
        include/R-Type/Components/Player.component.hpp
        include/Engine/Components/Parallax.component.hpp
        include/R-Type/Components/EnemyQueue.component.hpp
        include/Engine/Components/Speed.component.hpp
        include/R-Type/Components/EnemyAttack.component.hpp
        include/Engine/Components/WorldMoveProgress.component.hpp
        include/R-Type/Components/EnemyMovements.component.hpp
        include/Engine/Components/Animation.component.hpp
        include/Engine/Engine.hpp
        include/Engine/Events/KeyPressed.event.hpp
        include/Engine/Events/KeyReleased.event.hpp
        src/Engine/Engine.cpp
        src/Engine/Systems/UI.system.cpp
        src/Engine/Systems/Renderer.system.cpp
        src/Engine/Systems/Physics.system.cpp
        src/Engine/Systems/Parallax.system.cpp
        src/Engine/Systems/WorldMove.system.cpp
        src/Engine/Systems/Animation.system.cpp

        include/R-Type/Systems/MovePlayer.system.hpp
        include/R-Type/Systems/Bullets.system.hpp
        include/R-Type/Systems/Enemy.system.hpp
        include/R-Type/Subscribers/Collision.subscriber.hpp
        include/R-Type/Subscribers/PlayerMove.subscriber.hpp
        include/R-Type/Subscribers/ShootPlayer.subscriber.hpp
        src/R-Type/EnemyMakers.cpp
        src/R-Type/Systems/MovePlayer.system.cpp
        src/R-Type/Systems/Enemy.system.cpp
        src/R-Type/Systems/Bullets.system.cpp

        include/Server/Server.hpp
        src/Server.cpp

        src/main.cpp
)

target_link_libraries(r-type PRIVATE sfml-graphics sfml-network)

install(TARGETS r-type DESTINATION bin)
