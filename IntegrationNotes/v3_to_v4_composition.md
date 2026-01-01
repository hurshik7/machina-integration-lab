# v3 to v4: Composition over Inheritance

## Overview

This migration replaces the interface-based multiple inheritance pattern with a composition-based capability system. This is a **major architectural change** that affects all Vehicle classes in the Game layer.

## What Changed

### Before (v3): Multiple Inheritance with Interfaces

```cpp
// Engine Layer - Interfaces
class IDrivable { virtual unsigned int GetDriveSpeed() const = 0; };
class IFlyable  { virtual unsigned int GetFlySpeed() const = 0; };
class ISailable { virtual unsigned int GetSailSpeed() const = 0; };
class IDivable  { virtual unsigned int GetDiveSpeed() const = 0; };

// Game Layer - Multiple Inheritance
class Airplane : public Vehicle, public IFlyable, public IDrivable { ... };
class Boatplane : public Vehicle, public IFlyable, public ISailable { ... };
```

### After (v4): Composition with Capability Classes

```cpp
// Engine Layer - Capability Classes
class DrivingCapability { unsigned int GetDriveSpeed() const; };
class FlyingCapability  { unsigned int GetFlySpeed() const; };
class SailingCapability { unsigned int GetSailSpeed() const; };
class DivingCapability  { unsigned int GetDiveSpeed() const; };

// Game Layer - Composition
class Airplane : public Vehicle {
    FlyingCapability mFlying;
    DrivingCapability mDriving;
};
```

## Files Changed

### Engine Layer (Added)
- `Engine/Capabilities/DrivingCapability.h/cpp`
- `Engine/Capabilities/FlyingCapability.h/cpp`
- `Engine/Capabilities/SailingCapability.h/cpp`
- `Engine/Capabilities/DivingCapability.h/cpp`

### Engine Layer (Removed)
- `Engine/Interfaces/IDrivable.h`
- `Engine/Interfaces/IFlyable.h`
- `Engine/Interfaces/ISailable.h`
- `Engine/Interfaces/IDivable.h`

### Engine Layer (Kept)
- `Engine/Interfaces/IPassenger.h` - Still used for passenger abstraction

### Game Layer (Modified)
| File | Change |
|------|--------|
| Airplane.h/cpp | `IFlyable, IDrivable` → `FlyingCapability, DrivingCapability` |
| Boat.h/cpp | `ISailable` → `SailingCapability` |
| Boatplane.h/cpp | `IFlyable, ISailable` → `FlyingCapability, SailingCapability` |
| UBoat.h/cpp | `ISailable, IDivable` → `SailingCapability, DivingCapability` |
| Sedan.h/cpp | `IDrivable` → `DrivingCapability` |
| Motorcycle.h/cpp | `IDrivable` → `DrivingCapability` |

## Migration Steps

### Step 1: Create Capability Classes in Engine Layer

```cpp
// Engine/Capabilities/FlyingCapability.h
class FlyingCapability {
public:
    explicit FlyingCapability(unsigned int flySpeed);
    unsigned int GetFlySpeed() const;
    void SetFlySpeed(unsigned int speed);
private:
    unsigned int mFlySpeed;
};
```

### Step 2: Update CMakeLists.txt

Remove old interface files, add new capability files:

```cmake
set(ENGINE_SOURCES
    # ... existing sources
    Capabilities/DrivingCapability.cpp
    Capabilities/FlyingCapability.cpp
    Capabilities/SailingCapability.cpp
    Capabilities/DivingCapability.cpp
)
```

### Step 3: Refactor Game Layer Vehicles

Replace inheritance with composition:

```cpp
// Before
class Airplane : public Vehicle, public IFlyable, public IDrivable

// After
class Airplane : public Vehicle {
    FlyingCapability mFlying;
    DrivingCapability mDriving;
};
```

### Step 4: Update Speed Calculation Methods

Speed methods now delegate to capability objects:

```cpp
unsigned int Airplane::GetFlySpeed() const {
    unsigned int baseParam = mFlying.GetFlySpeed();
    return static_cast<unsigned int>(
        200.0 * exp((static_cast<double>(baseParam) - GetPassengersWeight()) / 500.0) + 0.5
    );
}
```

### Step 5: Delete Old Interface Files

Remove the following files:
- `Engine/Interfaces/IDrivable.h`
- `Engine/Interfaces/IFlyable.h`
- `Engine/Interfaces/ISailable.h`
- `Engine/Interfaces/IDivable.h`

## Why This Change?

### Problems with Multiple Inheritance

1. **Diamond Problem Risk**: Adding shared functionality to interfaces could cause ambiguity
2. **Tight Coupling**: Vehicles were forced to inherit from specific interfaces
3. **Inflexibility**: Couldn't add/remove capabilities at runtime
4. **Testing Difficulty**: Hard to mock/test individual capabilities

### Benefits of Composition

1. **Flexibility**: Capabilities can be mixed and matched freely
2. **Encapsulation**: Each capability manages its own state
3. **Testability**: Capabilities can be unit tested independently
4. **Modern Design**: Aligns with "Composition over Inheritance" principle
5. **Game Engine Pattern**: Similar to component-based architecture used in Frostbite and other AAA engines

## Namespace Changes

New namespace added:
```cpp
namespace engine {
namespace capabilities {
    class DrivingCapability;
    class FlyingCapability;
    class SailingCapability;
    class DivingCapability;
}
}
```

## Breaking Changes Summary

| Change | Impact |
|--------|--------|
| Removed `IDrivable`, `IFlyable`, `ISailable`, `IDivable` | All vehicles must be updated |
| Added Capability classes as members | Constructors must initialize capabilities |
| Changed include paths | Update from `Interfaces/` to `Capabilities/` |

## Lessons Learned

1. **Composition over Inheritance**: Prefer "has-a" relationships over "is-a" when dealing with capabilities
2. **Engine/Game Boundary**: Capability classes live in Engine, but Game decides which capabilities each Vehicle has
3. **Base Parameters**: Store configuration in Capability, compute dynamic values in Vehicle
4. **Breaking Changes Are Educational**: This migration required touching every Vehicle class, providing practice with large-scale refactoring
