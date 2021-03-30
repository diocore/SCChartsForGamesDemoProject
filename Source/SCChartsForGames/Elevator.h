// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElevatorFSM.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"



UCLASS()
class SCCHARTSFORGAMES_API AElevator : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();
	UFUNCTION(BlueprintCallable)
	void PressBtn(int Floor);
	UFUNCTION(BlueprintCallable)
	void UpdateDoorStatus(bool isOpen);
	UFUNCTION(BlueprintCallable)
	void UpdateFloorStatus(int Floor);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void OpenOutsideDoors(int Floor);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
    void CloseOutsideDoors(int Floor);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void OpenElevatorRoomDoors();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void CloseElevatorRoomDoors();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void MoveElevator(bool Up, int NumOfFloors);
	UFUNCTION(BlueprintCallable)
	void CallElevator(int Floor);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadOnly)
	int DebugStateID = 0; // to display the SCCharts
	TQueue<int> Queue; // to que button input
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ElevatorFSM Elevator = ElevatorFSM();
	bool bDoorOpen;
	UPROPERTY(BlueprintReadWrite)
	bool bMoving;
	UPROPERTY(BlueprintReadWrite)
	int CurrentFloor;
};
