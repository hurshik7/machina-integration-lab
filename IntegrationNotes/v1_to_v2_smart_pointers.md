# V1 to V2: Smart Pointer Migration

## Overview
This document details the migration from raw pointers to smart pointers across the Engine and Game layers. This breaking change improves memory safety, clarifies ownership semantics, and eliminates manual memory management.

---

## Summary of Changes

| Component | Before (v1) | After (v2) |
|-----------|-------------|------------|
| DeusExMachina::mInstance | `DeusExMachina*` | `std::unique_ptr<DeusExMachina, InstanceDeleter>` |
| DeusExMachina::mVehicles | `Vehicle**` | `std::vector<std::unique_ptr<Vehicle>>` |
| Vehicle::mPassengersArray | `const Person**` | `std::vector<std::unique_ptr<const Person>>` |
| Sedan::mTrailer | `const Trailer*` | `std::unique_ptr<Trailer>` |

---

## Breaking Changes

### 1. DeusExMachina Singleton

#### Before (v1):
```cpp
class DeusExMachina
{
public:
    static DeusExMachina* GetInstance();
    // No cleanup method - memory leak!

private:
    static DeusExMachina* mInstance;
};
```

#### After (v2):
```cpp
class DeusExMachina
{
public:
    static DeusExMachina* GetInstance();
    static void ResetInstance();  // NEW: explicit cleanup

private:
    struct InstanceDeleter
    {
        void operator()(DeusExMachina* ptr) const { delete ptr; }
    };
    friend struct InstanceDeleter;

    static std::unique_ptr<DeusExMachina, InstanceDeleter> mInstance;
};
```

#### Why Custom Deleter?
- Destructor remains `private` to prevent external deletion
- `InstanceDeleter` is a `friend` struct that can access the private destructor
- This maintains encapsulation while enabling `unique_ptr` cleanup

#### Migration Steps:
1. No changes required for calling code - `GetInstance()` still returns raw pointer
2. Add `ResetInstance()` calls for explicit cleanup (useful in tests)

---

### 2. DeusExMachina Vehicle Storage

#### Before (v1):
```cpp
class DeusExMachina
{
public:
    bool AddVehicle(Vehicle* vehicle);  // Takes raw pointer

private:
    Vehicle** mVehicles;
};
```

#### After (v2):
```cpp
class DeusExMachina
{
public:
    bool AddVehicle(std::unique_ptr<Vehicle> vehicle);  // Takes ownership

private:
    std::vector<std::unique_ptr<Vehicle>> mVehicles;
};
```

#### Migration Steps:

**Before (v1):**
```cpp
Airplane* airplane = new Airplane(5);
deusExMachina->AddVehicle(airplane);
```

**After (v2):**
```cpp
std::unique_ptr<Airplane> airplane = std::make_unique<Airplane>(5);
deusExMachina->AddVehicle(std::move(airplane));
```

---

### 3. Vehicle Passenger Management

#### Before (v1):
```cpp
class Vehicle
{
public:
    bool AddPassenger(const Person* person);      // Takes ownership
    bool RemovePassenger(unsigned int i);          // Deletes passenger
    const Person* GetPassenger(unsigned int i) const;
    void TransferAllPassengers();                  // Nulls without delete

private:
    unsigned int mPassengersCount;
    const Person** mPassengersArray;  // Manual array management
};
```

#### After (v2):
```cpp
class Vehicle
{
public:
    bool AddPassenger(std::unique_ptr<const Person> person);  // Explicit ownership
    bool RemovePassenger(unsigned int i);                      // Auto-deletes
    std::unique_ptr<const Person> ReleasePassenger(unsigned int i);  // NEW
    const Person* GetPassenger(unsigned int i) const;          // Observation only
    std::vector<std::unique_ptr<const Person>> ReleaseAllPassengers();  // NEW

private:
    std::vector<std::unique_ptr<const Person>> mPassengers;  // Auto-managed
};
```

#### Key Semantic Changes:
| Method | v1 Behavior | v2 Behavior |
|--------|-------------|-------------|
| `AddPassenger()` | Implicit ownership transfer | Explicit `std::move()` required |
| `RemovePassenger()` | Manual `delete` | Automatic cleanup |
| `GetPassenger()` | Returns owned pointer | Returns observation pointer |
| `TransferAllPassengers()` | Nulls array | **Removed** - use `ReleaseAllPassengers()` |
| `ReleasePassenger()` | N/A | **New** - returns ownership |
| `ReleaseAllPassengers()` | N/A | **New** - returns all with ownership |

#### Migration Steps:

**Before (v1):**
```cpp
Person* p = new Person("Bob", 85);
airplane.AddPassenger(p);
```

**After (v2):**
```cpp
std::unique_ptr<Person> p = std::make_unique<Person>("Bob", 85);
airplane.AddPassenger(std::move(p));
```

**Passenger Transfer (v1):**
```cpp
for (size_t i = 0; i < plane.GetPassengersCount(); i++)
{
    bp.AddPassenger(plane.GetPassenger(i));  // Pointer copy
}
plane.TransferAllPassengers();  // Clear without delete
```

**Passenger Transfer (v2):**
```cpp
std::vector<std::unique_ptr<const Person>> passengers = plane.ReleaseAllPassengers();
for (std::unique_ptr<const Person>& passenger : passengers)
{
    bp.AddPassenger(std::move(passenger));  // Ownership transfer
}
```

---

### 4. Sedan Trailer Management

#### Before (v1):
```cpp
class Sedan : public Vehicle
{
public:
    bool AddTrailer(const Trailer* trailer);
    bool RemoveTrailer();

private:
    bool mbIsTrailOn;
    const Trailer* mTrailer;
};
```

#### After (v2):
```cpp
class Sedan : public Vehicle
{
public:
    bool AddTrailer(std::unique_ptr<Trailer> trailer);
    bool RemoveTrailer();
    const Trailer* GetTrailer() const;  // NEW: observation access

private:
    std::unique_ptr<Trailer> mTrailer;  // nullptr check replaces mbIsTrailOn
};
```

#### Migration Steps:

**Before (v1):**
```cpp
sedan->AddTrailer(new Trailer(50));
```

**After (v2):**
```cpp
sedan->AddTrailer(std::make_unique<Trailer>(50));
```

---

## Copy Semantics

### Vehicle Copy Constructor/Assignment
Both perform **deep copy** of passengers:

```cpp
Vehicle::Vehicle(const Vehicle& other)
{
    for (const std::unique_ptr<const Person>& passenger : other.mPassengers)
    {
        mPassengers.push_back(std::make_unique<Person>(
            passenger->GetName().c_str(), passenger->GetWeight()));
    }
}
```

### Sedan Copy Constructor/Assignment
Performs **deep copy** of trailer:

```cpp
Sedan::Sedan(const Sedan& other)
    : Vehicle(other)
    , mTrailer(nullptr)
{
    if (other.mTrailer != nullptr)
    {
        mTrailer = std::make_unique<Trailer>(other.mTrailer->GetWeight());
    }
}
```

---

## Impact Analysis

### Engine Layer Changes
| File | Changes |
|------|---------|
| `DeusExMachina.h` | Added `InstanceDeleter`, `ResetInstance()`, changed `mInstance` type |
| `DeusExMachina.cpp` | Updated singleton initialization and cleanup |
| `Vehicle.h` | Changed `mPassengersArray` to vector, updated method signatures |
| `Vehicle.cpp` | Rewrote passenger management, simplified destructor |

### Game Layer Changes
| File | Changes |
|------|---------|
| `Sedan.h` | Removed `mbIsTrailOn`, changed `mTrailer` type |
| `Sedan.cpp` | Updated trailer logic, simplified destructor |
| `Airplane.cpp` | Updated `operator+` to use `ReleaseAllPassengers()` |
| `Boat.cpp` | Updated `operator+` to use `ReleaseAllPassengers()` |
| `main.cpp` | All `new` replaced with `std::make_unique`, added `std::move()` |

---

## Benefits Achieved

1. **Memory Safety**: No manual `delete` calls - eliminates memory leaks and double-free bugs
2. **Clear Ownership**: `unique_ptr` explicitly shows who owns memory
3. **Exception Safety**: RAII ensures cleanup even when exceptions occur
4. **Simplified Destructors**: Many become `= default`
5. **Self-Documenting Code**: API signatures show ownership transfer intent

---

## Lessons Learned

1. **Custom Deleters for Private Destructors**: Use friend struct pattern for singletons
2. **Release vs Remove**: Distinguish between "delete and remove" vs "transfer ownership"
3. **Observation Pointers**: Getters return raw pointers for observation, not ownership
4. **Deep Copy with Smart Pointers**: Requires explicit reconstruction of owned objects
5. **Vector vs Raw Array**: `std::vector<unique_ptr<T>>` eliminates manual size tracking

---

## Interview Discussion Points

- Why `unique_ptr` over `shared_ptr`? (Single ownership is clearer and more efficient)
- Custom deleter pattern for encapsulated singletons
- RAII and exception safety guarantees
- Migration strategy: change API signatures first, then fix compilation errors
- Deep copy semantics with smart pointers
