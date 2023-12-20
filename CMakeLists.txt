cmake_minimum_required(VERSION 3.20.5)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(R-TYPE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -std=c++20")

include_directories(include)

find_package(SFML 2.6 COMPONENTS graphics QUIET)

if (NOT SFML_FOUND AND (UNIX OR APPLE))
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(r-type_client
               include/ECS/Components.hpp
               include/ECS/EventSubscriber.hpp
               include/ECS/Clock.hpp
               include/ECS/System.hpp
               include/ECS/World.hpp
               include/ECS/Entity.hpp
               include/ECS/Utilities.hpp
               include/r-type.hpp
               include/Engine/Systems/Renderer.system.hpp
               include/Engine/Systems/Server.system.hpp
               include/Engine/Components/Renderable.component.hpp
               include/Engine/Engine.hpp
               src/test.cpp
               src/Engine/Engine.cpp
               src/Engine/Systems/Renderer.systems.cpp
               src/Engine/Systems/Server.systems.cpp
)

target_compile_features(r-type_client PRIVATE cxx_std_17)

    target_link_libraries(r-type_client PRIVATE sfml-graphics)

if (UNIX OR APPLE)
    install(TARGETS r-type_client DESTINATION bin)
endif (UNIX OR APPLE)
