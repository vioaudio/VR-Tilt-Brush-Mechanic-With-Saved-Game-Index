// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"
#include "Engine/World.h"

// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
		SetRootComponent(MotionController);
		MotionController->SetTrackingSource(EControllerHand::Right);
		MotionController->SetShowDeviceModel(true); //Automatically knows which Model Device your using and which hand
}

void AHandController::BeginPlay()
{
	Super::BeginPlay();
}

void AHandController::Draw()
{
	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
	CurrentStroke->SetActorLocation(GetActorLocation());
}

void AHandController::DrawStop()
{
	CurrentStroke = nullptr;
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStroke)
	{
		CurrentStroke->Update(GetActorLocation());
	}
}

