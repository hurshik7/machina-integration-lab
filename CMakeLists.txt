# Machina Integration Lab
cmake_minimum_required(VERSION 3.15)

project(MachinaIntegrationLab
    VERSION 1.0.0
    DESCRIPTION "C++ Engine Integration Sandbox for EA Frostbite Integration Prep"
    LANGUAGES CXX
)

# Set C++17 as the default standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build Engine as a static library
add_subdirectory(Engine)

# Collect all Game source files
set(GAME_SOURCES
    Game/main.cpp
    Game/Vehicles/Airplane.cpp
    Game/Vehicles/Boat.cpp
    Game/Vehicles/Boatplane.cpp
    Game/Vehicles/Motorcycle.cpp
    Game/Vehicles/Person.cpp
    Game/Vehicles/Sedan.cpp
    Game/Vehicles/Trailer.cpp
    Game/Vehicles/UBoat.cpp
)

# Collect all Game header files
set(GAME_HEADERS
    Game/Vehicles/Airplane.h
    Game/Vehicles/Boat.h
    Game/Vehicles/Boatplane.h
    Game/Vehicles/Motorcycle.h
    Game/Vehicles/Person.h
    Game/Vehicles/Sedan.h
    Game/Vehicles/Trailer.h
    Game/Vehicles/UBoat.h
)

# Create executable for the game
add_executable(MachinaGame
    ${GAME_SOURCES}
    ${GAME_HEADERS}
)

# Link the Engine library to the Game executable
target_link_libraries(MachinaGame PRIVATE MachinaEngine)

# Include directories for Game
target_include_directories(MachinaGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine
)

# Platform-specific compiler flags
if(MSVC)
    target_compile_options(MachinaGame PRIVATE /W4)
else()
    target_compile_options(MachinaGame PRIVATE -Wall -Wextra -pedantic)
endif()

# Set output directory
set_target_properties(MachinaGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Print build configuration
message(STATUS "===========================================")
message(STATUS "Machina Integration Lab Build Configuration")
message(STATUS "===========================================")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Engine Library: MachinaEngine (static)")
message(STATUS "Game Executable: MachinaGame")
message(STATUS "===========================================")
