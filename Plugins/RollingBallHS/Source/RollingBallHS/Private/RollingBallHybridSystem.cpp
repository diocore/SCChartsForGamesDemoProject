// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBallHybridSystem.h"

RollingBallHybridSystem::RollingBallHybridSystem() {
}

RollingBallHybridSystem::~RollingBallHybridSystem() {
}

float RollingBallHybridSystem::Tick(const float Velocity, const float DeltaTime) {
    TickData.deltaT = DeltaTime;
    TickData.currentV = Velocity;
    RB_Tick(&TickData);
    return TickData.accel;
}

void RollingBallHybridSystem::Reset() {
    RB_Reset(&TickData);
}

void RollingBallHybridSystem::Setup(const float TargetSpeed, const float Kp, const float Ki, const float Kd) {
    TickData.Kp = Kp;
    TickData.Ki = Ki;
    TickData.Kd = Kd;
    TickData.targetV = TargetSpeed;
}
