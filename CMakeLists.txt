cmake_minimum_required(VERSION 3.20.5)

project(R-TYPE)

set(CMAKE_CXX_STANDARD 20)
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -std=c++20 -g -Og")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++20 -O2")
endif()

include_directories(include)

find_package(SFML 2.6 COMPONENTS graphics audio network system window QUIET)

if (NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif ()

add_executable(r-type
        ##===============##
        ##  ECS Headers  ##
        ##===============##

        include/ECS/Clock.hpp
        include/ECS/EventSubscriber.hpp
        include/ECS/System.hpp
        include/ECS/Utilities.hpp
        include/ECS/World.hpp
        include/ECS/Components.hpp
        include/ECS/Entity.hpp

        ##==================##
        ##  Engine Headers  ##
        ##==================##

        include/Engine/Components/Button.component.hpp
        include/Engine/Components/CheckBox.component.hpp
        include/Engine/Components/ExcludeCollision.component.hpp
        include/Engine/Components/Moving.component.hpp
        include/Engine/Components/Parallax.component.hpp
        include/Engine/Components/Position.component.hpp
        include/Engine/Components/Speed.component.hpp
        include/Engine/Components/Type.component.hpp
        include/Engine/Components/View.component.hpp
        include/Engine/Components/WorldMoveProgress.component.hpp
        include/Engine/Components/Collision.component.hpp
        include/Engine/Components/Animation.component.hpp
        include/Engine/Components/Renderable.component.hpp
        include/Engine/Components/Drawable.component.hpp
        include/Engine/Components/LayeredAnimation.component.hpp
        include/Engine/Components/LayeredRenderable.component.hpp
        include/Engine/Events/Resize.event.hpp
        include/Engine/Events/Collision.event.hpp
        include/Engine/Events/KeyPressed.event.hpp
        include/Engine/Events/KeyReleased.event.hpp
        include/Engine/Systems/Animation.system.hpp
        include/Engine/Systems/Renderer.system.hpp
        include/Engine/Systems/Inputs.system.hpp
        include/Engine/Systems/Parallax.system.hpp
        include/Engine/Systems/UI.system.hpp
        include/Engine/Systems/WorldMove.system.hpp
        include/Engine/Systems/Physics.system.hpp
        include/Engine/Utils/Math.hpp
        include/Engine/Engine.hpp

        ##==================##
        ##  Engine Sources  ##
        ##==================##

        src/Engine/Systems/Parallax.system.cpp
        src/Engine/Systems/Renderer.system.cpp
        src/Engine/Systems/UI.system.cpp
        src/Engine/Systems/Sound.system.cpp
        src/Engine/Systems/Options.system.cpp
        src/Engine/Systems/Inputs.system.cpp
        src/Engine/Systems/WorldMove.system.cpp
        src/Engine/Systems/Animation.system.cpp
        src/Engine/Systems/Physics.system.cpp
        src/Engine/Engine.cpp

        ##==================##
        ##  R-Type Headers  ##
        ##==================##

        include/R-Type/sprites.hpp
        include/R-Type/Subscribers/PlayerMove.subscriber.hpp
        include/R-Type/Subscribers/ShootPlayer.subscriber.hpp
        include/R-Type/Subscribers/Collision.subscriber.hpp
        include/R-Type/Subscribers/Keyboard.subscriber.hpp
        include/R-Type/Components/BaseBullet.component.hpp
        include/R-Type/Components/Enemy.component.hpp
        include/R-Type/Components/EnemyAttack.component.hpp
        include/R-Type/Components/EnemyMovements.component.hpp
        include/R-Type/Components/Missile.component.hpp
        include/R-Type/Components/Player.component.hpp
        include/R-Type/Components/DeathAnimation.component.hpp
        include/R-Type/Components/EnemyQueue.component.hpp
        include/R-Type/Components/Health.component.hpp
        include/R-Type/GameWorld/Subscribers.hpp
        include/R-Type/GameWorld/Entities.hpp
        include/R-Type/GameWorld/GameWorld.hpp
        include/R-Type/GameWorld/Systems.hpp
        include/R-Type/Systems/Bullets.system.hpp
        include/R-Type/Systems/MovePlayer.system.hpp
        include/R-Type/Systems/DeathAnimation.system.hpp
        include/R-Type/Systems/Enemy.system.hpp
        include/R-Type/Systems/Health.system.hpp

        ##==================##
        ##  R-Type Sources  ##
        ##==================##

        src/R-Type/Systems/Bullets.system.cpp
        src/R-Type/Systems/MovePlayer.system.cpp
        src/R-Type/Systems/DeathAnimation.system.cpp
        src/R-Type/Systems/Enemy.system.cpp
        src/R-Type/Systems/Health.system.cpp

        src/main.cpp
)
if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_definitions(r-type PRIVATE DEBUG_MODE)
endif()

target_link_libraries(r-type PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
# TODO: Fix network for windows
# if (WIN32)
#     target_link_libraries(r-type, PRIVATE ws2_32.lib)
#     add_custom_command(TARGET r-type POST_BUILD
#             COMMAND ${CMAKE_COMMAND} -E copy
#             $<TARGET_RUNTIME_DLLS:r-type> $<TARGET_FILE_DIR:r-type> COMMAND_EXPAND_LISTS)
#     set(CPACK_PRE_BUILD_SCRIPTS "${CMAKE_CURRENT_SOURCE_DIR}")
# endif()

if (UNIX)
    set_target_properties(r-type PROPERTIES INSTALL_RPATH "$ORIGIN/lib")
endif()

install(TARGETS r-type DESTINATION .)

install(DIRECTORY assets DESTINATION .)

include(InstallRequiredSystemLibraries)
set(CPACK_BUNDLE_NAME "R-Type")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
include(CPack)
