# V2 to V3: IPassenger Interface Introduction

## Overview
This document details the introduction of the `IPassenger` interface to decouple the Engine layer from the Game layer. This breaking change fixes an architectural violation where the Engine directly depended on Game-layer types.

---

## The Problem: Dependency Inversion Violation

### Before (v2):
```
Engine/Vehicles/Vehicle.h
    └── #include "../../Game/Vehicles/Person.h"  // VIOLATION!
```

The Engine layer was directly including and depending on a Game layer class (`Person`). This creates several problems:

| Problem | Impact |
|---------|--------|
| **Circular dependency risk** | Engine cannot be built independently |
| **Tight coupling** | Any change to `Person` requires Engine recompilation |
| **Reusability blocked** | Engine cannot be used with different passenger types |
| **Architecture violation** | Breaks the Engine/Game separation principle |

---

## The Solution: IPassenger Interface

### After (v3):
```
Engine/Interfaces/IPassenger.h  (NEW)
    ^
    |
Engine/Vehicles/Vehicle.h ──────┘

Game/Vehicles/Person.h
    └── implements IPassenger
```

The Engine now depends only on its own interface. The Game layer provides concrete implementations.

---

## Summary of Changes

| Component | Before (v2) | After (v3) |
|-----------|-------------|------------|
| Engine include | `#include "Game/Vehicles/Person.h"` | `#include "Engine/Interfaces/IPassenger.h"` |
| Vehicle passenger type | `const Person*` | `const IPassenger*` |
| Person class | Standalone class | Implements `IPassenger` |
| Dependency direction | Engine → Game (wrong) | Game → Engine (correct) |

---

## Breaking Changes

### 1. New Interface: IPassenger

```cpp
// Engine/Interfaces/IPassenger.h
namespace engine {
namespace interfaces {

class IPassenger
{
public:
    virtual ~IPassenger() = default;

    virtual const std::string& GetName() const = 0;
    virtual unsigned int GetWeight() const = 0;
};

} // namespace interfaces
} // namespace engine
```

### 2. Vehicle API Changes

#### Before (v2):
```cpp
#include "../../Game/Vehicles/Person.h"

class Vehicle
{
public:
    bool AddPassenger(std::unique_ptr<const Person> passenger);
    const Person* GetPassenger(unsigned int i) const;
    std::vector<std::unique_ptr<const Person>> ReleaseAllPassengers();

private:
    std::vector<std::unique_ptr<const Person>> mPassengers;
};
```

#### After (v3):
```cpp
#include "../Interfaces/IPassenger.h"

class Vehicle
{
public:
    bool AddPassenger(std::unique_ptr<const engine::interfaces::IPassenger> passenger);
    const engine::interfaces::IPassenger* GetPassenger(unsigned int i) const;
    std::vector<std::unique_ptr<const engine::interfaces::IPassenger>> ReleaseAllPassengers();

private:
    std::vector<std::unique_ptr<const engine::interfaces::IPassenger>> mPassengers;
};
```

### 3. Person Now Implements IPassenger

#### Before (v2):
```cpp
namespace game {
namespace vehicles {

class Person
{
public:
    Person(const char* name, unsigned int weight);

    const std::string& GetName() const;
    unsigned int GetWeight() const;

private:
    std::string mName;
    unsigned int mWeight;
};

} // namespace vehicles
} // namespace game
```

#### After (v3):
```cpp
#include "../../Engine/Interfaces/IPassenger.h"

namespace game {
namespace vehicles {

class Person : public engine::interfaces::IPassenger
{
public:
    Person(const char* name, unsigned int weight);
    virtual ~Person();

    virtual const std::string& GetName() const override;
    virtual unsigned int GetWeight() const override;

private:
    std::string mName;
    unsigned int mWeight;
};

} // namespace vehicles
} // namespace game
```

---

## Migration Steps

### Step 1: Create the Interface
Add `Engine/Interfaces/IPassenger.h` with pure virtual methods for passenger behavior.

### Step 2: Update Vehicle
- Change include from `Person.h` to `IPassenger.h`
- Replace all `Person` references with `IPassenger`
- Update method signatures and member types

### Step 3: Update Person
- Add inheritance: `class Person : public engine::interfaces::IPassenger`
- Add `virtual` and `override` keywords to methods
- Add virtual destructor

### Step 4: Update Game Layer Code
- Ensure `Airplane::operator+` and `Boat::operator+` handle `IPassenger*` correctly
- Cast to `Person*` only if Person-specific behavior is needed (avoid if possible)

---

## Impact Analysis

### Engine Layer Changes
| File | Changes |
|------|---------|
| `Engine/Interfaces/IPassenger.h` | **NEW FILE** - Interface definition |
| `Engine/Vehicles/Vehicle.h` | Changed include, updated all `Person` → `IPassenger` |
| `Engine/Vehicles/Vehicle.cpp` | Updated passenger handling logic |

### Game Layer Changes
| File | Changes |
|------|---------|
| `Game/Vehicles/Person.h` | Added IPassenger inheritance, virtual/override keywords |
| `Game/Vehicles/Airplane.cpp` | Updated passenger transfer in `operator+` |
| `Game/Vehicles/Boat.cpp` | Updated passenger transfer in `operator+` |
| `Game/Vehicles/Boatplane.h` | Added IPassenger include for clarity |

---

## Benefits Achieved

1. **Correct Dependency Direction**: Engine no longer depends on Game layer
2. **Dependency Inversion Principle**: High-level modules (Engine) depend on abstractions (IPassenger), not concrete types (Person)
3. **Extensibility**: New passenger types can be added in Game layer without Engine changes
4. **Testability**: Engine can be unit tested with mock passengers
5. **Independent Compilation**: Engine can be built as a standalone library

---

## Lessons Learned

1. **Interface Segregation**: `IPassenger` contains only what Vehicle needs (name, weight)
2. **Namespace Organization**: Interfaces go in `engine::interfaces` namespace
3. **Folder Structure**: `Engine/Interfaces/` folder for engine-level abstractions
4. **Breaking Change Strategy**: Change Engine first, then fix compilation errors in Game
5. **Forward Declaration Limits**: Cannot forward-declare when you need the full type for `unique_ptr<T>`

---

## Design Principles Applied

| Principle | Application |
|-----------|-------------|
| **Dependency Inversion (DIP)** | Engine depends on IPassenger abstraction |
| **Interface Segregation (ISP)** | IPassenger has only passenger-specific methods |
| **Open/Closed (OCP)** | New passenger types don't require Engine changes |
| **Single Responsibility (SRP)** | IPassenger defines only passenger contract |

---

## Discussion Points

- Why interface instead of template? (Runtime polymorphism needed for heterogeneous containers)
- Why in Engine layer? (Engine defines what it needs, Game provides implementations)
- Could we have more interfaces? (Yes: `IVehicle`, `ITraveler`, etc. for future expansion)
- Performance impact of virtual calls? (Minimal - passenger operations are not performance-critical)
