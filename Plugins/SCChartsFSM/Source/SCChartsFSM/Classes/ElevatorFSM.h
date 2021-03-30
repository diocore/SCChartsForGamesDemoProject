#pragma once

#include "CoreMinimal.h"

extern "C" {
	#include "../kieler-gen/Elevator.h"
}

class SCCHARTSFSM_API ElevatorFSM {
public:
	ElevatorFSM();
	~ElevatorFSM();
	void Tick();
	void Reset();
	void InputTargetFloor(int TargetFloor);
	void InputDoorOpen(bool isOpen);
	E_TickData tickData = E_TickData();
	int LastStateID;
};


