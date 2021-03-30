// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Wrapper to relay the press of the button up to the FSM
void AElevator::PressBtn(int Floor) {
	Queue.Enqueue(Floor);
}
// Updates the doorOpen value inside the SCCharts model to reflect the same value inside the game
void AElevator::UpdateDoorStatus(bool isOpen) {
	Elevator.InputDoorOpen(isOpen);
}
// Updates the currentFloor value inside the SCCharts model to reflect the same value inside the game
void AElevator::UpdateFloorStatus(int Floor) {
	CurrentFloor = Floor;
	Elevator.tickData.currentFloor = Floor;
}
// Calls the elevator to the given floor
void AElevator::CallElevator(int Floor)  {
	// this Queue holds the requested number of floors in order of the requests given
	if (CurrentFloor != Floor) {
		Queue.Enqueue(Floor);
	}
}

// Called when the game starts or when spawned
void AElevator::BeginPlay() {
	Super::BeginPlay();
	// The SCCharts FSM needs to be ressetted before it can recive the first tick
	Elevator.Reset();
}

void AElevator::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);Elevator.Tick();
	DebugStateID = Elevator.tickData.stateID;
	int NextFloor = -1;
	if (Elevator.LastStateID != Elevator.tickData.stateID) 	{
		switch (Elevator.tickData.stateID) 		{
		case 1: 
			OpenOutsideDoors(Elevator.tickData.currentFloor); OpenElevatorRoomDoors(); 
			break;
		case 3: 
			CloseOutsideDoors(Elevator.tickData.currentFloor); CloseElevatorRoomDoors();
			break;
		default:
			break;
		}
	} else if (Elevator.LastStateID == 2) { 
		if ( Queue.Dequeue(NextFloor)) Elevator.tickData.targetFloor = NextFloor; 
	}
	
	if (Elevator.tickData.moveUp) MoveElevator(true, Elevator.tickData.numFloorsToMove);
	
	if (Elevator.tickData.moveDown)	MoveElevator(false, Elevator.tickData.numFloorsToMove); 
}

// Called every frame
// void AElevator::Tick(float DeltaTime) {
// 	Super::Tick(DeltaTime);
// 	Elevator.Tick();
// 	DebugStateID = Elevator.tickData.stateID;
// 	int NextFloor = -1;
// 	// Check if the state changed. This is necessary to not open the doors repeatedly if they are already open
// 	// could also be handled inside the called function separately, but I decided to handle it this way
// 	if (Elevator.LastStateID != DebugStateID) 	{
// 		switch (DebugStateID) 		{
// 		case 1: // State: OpenDoors
// 			OpenOutsideDoors(Elevator.tickData.currentFloor); // Open the doors at the floor given by the SCCharts value currentFloor
// 			OpenElevatorRoomDoors(); // also opens the Elevator door so people can get in
// 			break;
// 		case 3: // State: Wait
// 			CloseOutsideDoors(Elevator.tickData.currentFloor); // Close the doors at the floor given by the SCCharts value currentFloor
// 			CloseElevatorRoomDoors(); // also closes the Elevator door so it i ready for movement
// 			break;
// 		default:
// 			break;
// 		}
// 	} else if (Elevator.LastStateID == 2) { // this needs to be called every tick. Otherwise we would be stuck in the Waiting state
// 		if ( Queue.Dequeue(NextFloor)) { // the Queue that holds the requested floor destinations
// 			// if Dequeue was successful at dequeuing and writing its value to nextFloor
// 			Elevator.tickData.targetFloor = NextFloor; // the value is written to the SCCharts targetFloor value
// 		}
// 	}
// 	
// 	// handles the output signals of the SCCharts
// 	if (Elevator.tickData.moveUp) {// if moveUp is present
// 		MoveElevator(true, Elevator.tickData.numFloorsToMove); // move the Elevator up by the given numbers of floors
// 	}
// 	if (Elevator.tickData.moveDown) {// if moveDown is present
// 		MoveElevator(false, Elevator.tickData.numFloorsToMove); // move the Elevator down by the given numbers of floors
// 	}
// }







