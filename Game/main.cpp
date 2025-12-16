#include <cassert>
#include <iostream>
#include <iomanip>
#include <memory>

#include "../Engine/Vehicles/Vehicle.h"
#include "Vehicles/Airplane.h"
#include "Vehicles/Boat.h"
#include "Vehicles/Boatplane.h"
#include "Vehicles/Motorcycle.h"
#include "Vehicles/Sedan.h"
#include "Vehicles/Trailer.h"
#include "Vehicles/UBoat.h"
#include "../Engine/Core/DeusExMachina.h"
#include "../Engine/Core/TravelContext.h"
#include "Vehicles/Person.h"

using namespace game::vehicles;
using engine::core::DeusExMachina;

int main()
{
	std::unique_ptr<Person> p = std::make_unique<Person>("Bob", 85);

	assert(p->GetName() == std::string("Bob"));
	assert(p->GetWeight() == 85);

	std::unique_ptr<Person> p2 = std::make_unique<Person>("James", 75);
	std::unique_ptr<Person> p3 = std::make_unique<Person>("Tina", 52);

	std::unique_ptr<Person> p4 = std::make_unique<Person>("Peter", 78);
	std::unique_ptr<Person> p5 = std::make_unique<Person>("Jane", 48);
	std::unique_ptr<Person> p6 = std::make_unique<Person>("Steve", 88);

	Airplane a(5);
	a.AddPassenger(std::move(p));
	a.AddPassenger(std::move(p2));
	a.AddPassenger(std::move(p3));

	assert(a.GetMaxPassengersCount() == 5);
	assert(a.GetPassengersCount() == 3);
	assert(a.GetPassenger(1)->GetName() == "James");
	assert(a.GetFlySpeed() == 648);
	assert(a.GetDriveSpeed() == 59);
	assert(a.GetMaxSpeed() == 648);

	Boat b(5);
	b.AddPassenger(std::move(p4));
	b.AddPassenger(std::move(p5));
	b.AddPassenger(std::move(p6));

	Boatplane bp = a + b;

	assert(bp.GetPassengersCount() == 6);
	assert(bp.GetMaxPassengersCount() == 10);

	assert(a.GetPassengersCount() == 0);
	assert(b.GetPassengersCount() == 0);

	DeusExMachina* deusExMachina1 = DeusExMachina::GetInstance();
	DeusExMachina* deusExMachina2 = DeusExMachina::GetInstance();

	bool bSame = deusExMachina1 == deusExMachina2;
	assert(bSame);

	std::unique_ptr<Airplane> airplane = std::make_unique<Airplane>(5);
	std::unique_ptr<Boat> boat = std::make_unique<Boat>(5);
	std::unique_ptr<Boatplane> boatplane = std::make_unique<Boatplane>(5);
	std::unique_ptr<Motorcycle> motorcycle = std::make_unique<Motorcycle>();
	std::unique_ptr<Sedan> sedan = std::make_unique<Sedan>();
	std::unique_ptr<Sedan> sedan2 = std::make_unique<Sedan>();
	std::unique_ptr<UBoat> uboat = std::make_unique<UBoat>();

	bool bAdded = sedan2->AddTrailer(std::make_unique<Trailer>(50));
	assert(bAdded);

	bAdded = sedan2->AddTrailer(std::make_unique<Trailer>(60));
	assert(!bAdded);

	// GetFurthestTravelled 테스트용 raw pointer 저장
	const Boat* boatPtr = boat.get();

	bAdded = deusExMachina1->AddVehicle(std::move(airplane));
	assert(bAdded);

	deusExMachina1->AddVehicle(std::move(boat));
	deusExMachina1->AddVehicle(std::move(boatplane));
	deusExMachina1->AddVehicle(std::move(motorcycle));
	deusExMachina1->AddVehicle(std::move(sedan));
	deusExMachina1->AddVehicle(std::move(sedan2));
	deusExMachina1->AddVehicle(std::move(uboat));
	deusExMachina1->AddVehicle(std::make_unique<Airplane>(5));
	deusExMachina1->AddVehicle(std::make_unique<Airplane>(5));
	deusExMachina1->AddVehicle(std::make_unique<Airplane>(5));

	bAdded = deusExMachina1->AddVehicle(std::make_unique<Airplane>(5));

	assert(!bAdded);

	deusExMachina1->RemoveVehicle(9);
	deusExMachina1->RemoveVehicle(8);
	bool bRemoved = deusExMachina1->RemoveVehicle(7);
	assert(bRemoved);

	bRemoved = deusExMachina1->RemoveVehicle(9);
	assert(!bRemoved);

	engine::core::TravelContext context;
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);
	deusExMachina1->Travel(context);

	assert(deusExMachina1->GetFurthestTravelled() == boatPtr);

	return 0;
}
