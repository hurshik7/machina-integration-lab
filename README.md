# Machina Integration Lab

A C++ sandbox project for practicing engine-to-game integration workflows, API versioning, and large-scale system architecture.

## Overview

Machina Integration Lab is a deliberately simplified C++ project designed to explore and practice the challenges of maintaining clean architectural boundaries between engine and game code. Rather than building a feature-complete engine, this project focuses on **integration workflows** and **API evolution strategies**.

### What This Project Is

- A learning environment for practicing API design and versioning
- A sandbox for simulating breaking changes and refactoring workflows
- An exercise in maintaining engine/game separation at the architectural level
- A demonstration of modern C++ practices in a multi-layer system

### What This Project Is Not

- A production-ready game engine
- A feature-complete vehicle simulation
- Optimized for performance or scalability

## Architecture

The project maintains strict separation between two layers:

```
┌─────────────────────────────────┐
│         Game Layer              │
│                                 │
│  • Concrete implementations     │
│  • Application logic            │
│  • Consumes Engine API          │
└─────────────────────────────────┘
              ▲
              │ Depends on
              │
┌─────────────────────────────────┐
│        Engine Layer             │
│     (Static Library)            │
│                                 │
│  • Core systems                 │
│  • Abstract interfaces          │
│  • No game dependencies         │
└─────────────────────────────────┘
```

### Namespace Structure

```cpp
engine::core                    // Core engine systems
engine::vehicles                // Base classes and shared types
engine::vehicles::interfaces    // Abstract capability interfaces

game::vehicles                  // Game-specific implementations
```

This separation allows for realistic integration scenarios where engine changes can intentionally break game code, requiring systematic refactoring.

## Building the Project

### Prerequisites
- CMake 3.15+
- C++17-compatible compiler

### Build Instructions

```bash
# Configure
cmake -B build

# Build
cmake --build build

# Run
./build/bin/MachinaGame
```

The build produces:
- **MachinaEngine**: Static library containing engine code
- **MachinaGame**: Executable linking against the engine

## Current Features (v1.0)

### Engine Layer
- **DeusExMachina**: Singleton orchestrator for vehicle management
- **Vehicle**: Abstract base class with passenger management and state tracking
- **Movement Interfaces**: IDrivable, IFlyable, ISailable, IDivable

### Game Layer
- **Vehicle Types**: Airplane, Boat, Sedan, Motorcycle, UBoat, Boatplane
- **Composition**: Airplane + Boat fusion creates Boatplane
- **Attachments**: Trailers for certain vehicle types

## Planned Integration Exercises

The goal is to introduce **intentional breaking changes** to simulate real-world engine evolution:

### Exercise 1: Memory Ownership Refactor
- Replace raw pointers with smart pointers
- Update all game code to handle new ownership model
- Document migration strategy

### Exercise 2: API Signature Changes
- Add required parameters to core methods
- Deprecate old APIs
- Systematically refactor game layer

### Exercise 3: Interface Redesign
- Introduce new movement capability model
- Break existing implementations
- Track time-to-integration

Each exercise will be documented in `/IntegrationNotes/` with:
- Rationale for the change
- Impact analysis
- Migration steps
- Lessons learned

## Learning Objectives

This project practices:

- **Architectural Boundaries**: Enforcing clean separation between layers
- **API Evolution**: Managing breaking changes systematically
- **Integration Workflows**: Understanding dependency impacts across boundaries
- **Build System Design**: Multi-target CMake configuration
- **Documentation**: Writing clear migration guides for API consumers
- **C++ Best Practices**: Modern features, ownership models, interface design

## Why This Approach?

Most C++ learning projects focus on implementing features. This project instead focuses on **maintaining and evolving** a system with clear boundaries—a skill critical for working with large codebases where changes ripple across teams and components.

By intentionally introducing breaking changes, this project simulates the reality of engine development where:
- APIs evolve over time
- Backward compatibility isn't always possible
- Clear communication and documentation are essential
- Systematic refactoring strategies are needed

## Documentation

- **IntegrationNotes/**: Migration guides for API changes (to be created as exercises progress)

## Future Directions

- Thread-safety exercises (concurrent vehicle updates)
- Serialization system design and versioning
- Plugin architecture for runtime extensibility
- Performance profiling case studies
- Unit testing integration strategies

## Technical Notes

### Why Static Library + Executable?

This structure mimics real-world engine distribution where:
- Engine is compiled as a library (`.lib`/`.a`)
- Game code links against stable engine API
- Changes to game code don't require engine recompilation

### Why Interface-Based Design?

Capability interfaces (`IFlyable`, `IDrivable`) allow flexible composition without deep inheritance hierarchies—a pattern common in modern engine design.

---

**This is a learning project focused on integration workflows rather than feature completeness.**
