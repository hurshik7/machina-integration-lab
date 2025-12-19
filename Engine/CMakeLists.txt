# Engine Static Library
cmake_minimum_required(VERSION 3.15)

# Collect all Engine source files
set(ENGINE_SOURCES
    Core/DeusExMachina.cpp
    Vehicles/Vehicle.cpp
)

# Collect all Engine header files
set(ENGINE_HEADERS
    Core/DeusExMachina.h
    Core/TravelContext.h
    Vehicles/Vehicle.h
    Interfaces/IPassenger.h
    Interfaces/IDrivable.h
    Interfaces/IFlyable.h
    Interfaces/ISailable.h
    Interfaces/IDivable.h
)

# Create static library
add_library(MachinaEngine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

# Set C++ standard
target_compile_features(MachinaEngine PUBLIC cxx_std_17)

# Include directories for the engine
target_include_directories(MachinaEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Platform-specific compiler flags
if(MSVC)
    target_compile_options(MachinaEngine PRIVATE /W4)
else()
    target_compile_options(MachinaEngine PRIVATE -Wall -Wextra -pedantic)
endif()
