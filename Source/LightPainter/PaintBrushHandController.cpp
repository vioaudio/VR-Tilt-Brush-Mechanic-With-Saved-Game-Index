// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintBrushHandController.h"
#include "Engine/World.h"

// Sets default values
APaintBrushHandController::APaintBrushHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();
}

void APaintBrushHandController::Draw()
{
	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
	CurrentStroke->SetActorLocation(GetActorLocation());
}

void APaintBrushHandController::DrawStop()
{
	CurrentStroke = nullptr;
}

// Called every frame
void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStroke)
	{
		CurrentStroke->Update(GetActorLocation());
	}
}

