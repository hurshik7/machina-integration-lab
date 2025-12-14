# V1 API Baseline

## Overview
This document captures the Engine API state before the TravelContext breaking change.

---

## Vehicle API (v1)

### File: `Engine/Vehicles/Vehicle.h`

```cpp
namespace engine {
namespace vehicles {

class Vehicle
{
public:
    // Core travel method - NO PARAMETERS
    virtual void TravelByMachina() = 0;

    // Movement time tracking
    unsigned int GetIdleTime() const;
    void AddIdleTime();
    void ResetIdleTIme();  // Note: typo in original
    unsigned int GetMoveTime() const;
    void AddMoveTime();
    void ResetMoveTime();

    // Odometer
    unsigned int GetOdo() const;
    void AddOdo(unsigned int distance);
};

} // namespace vehicles
} // namespace engine
```

### Key Characteristics:
- `TravelByMachina()` takes **no parameters**
- Each vehicle implementation hardcodes its own move/idle cycle logic
- No external control over travel duration or conditions

---

## DeusExMachina API (v1)

### File: `Engine/Core/DeusExMachina.h`

```cpp
namespace engine {
namespace core {

class DeusExMachina
{
public:
    void Travel() const;  // Calls TravelByMachina() on all vehicles
};

} // namespace core
} // namespace engine
```

### Travel() Implementation:
```cpp
void DeusExMachina::Travel() const
{
    for (size_t i = 0; i < mVehiclesCount; i++)
    {
        mVehicles[i]->TravelByMachina();  // No context passed
    }
}
```

---

## Game Layer Implementations (v1)

All 7 vehicle types implement `TravelByMachina()` with hardcoded logic:

| Vehicle    | Move Cycles | Idle Cycles | Pattern |
|------------|-------------|-------------|---------|
| Airplane   | 1           | 1           | move -> idle -> reset |
| Boat       | 2           | 1           | move -> move -> idle -> reset |
| Sedan      | Variable    | Variable    | Based on trailer state |
| Motorcycle | 1           | 1           | Simple cycle |
| UBoat      | 2           | 2           | Extended idle |
| Boatplane  | Hybrid      | Hybrid      | Combined logic |

---

## Problems with V1 Design

1. **No External Control**: Cannot specify how long to travel
2. **Hardcoded Behavior**: Each vehicle has fixed move/idle patterns
3. **No Environmental Factors**: Weather, emergency conditions not considered
4. **Limited Testability**: Cannot simulate different scenarios without modifying code

---

## Planned Breaking Change: TravelContext

The next version (v2) will introduce `TravelContext` struct to address these issues.

See: `v1_to_v2.md` for migration details.
