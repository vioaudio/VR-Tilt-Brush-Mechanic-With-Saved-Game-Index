// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Engine/World.h"
#include "PaintBrushHandController.h"
#include "Components/InputComponent.h"
#include "LightPainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PaintingGameMode.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "PaintingPicker.h"
#include "EngineUtils.h"


AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (RightHandControllerClass)
	{
		RightController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
		RightController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale); //SnapToTargetIncludeScale Eliminates Previous Transform Held
		RightController->SetHand(EControllerHand::Right);
		RightController->SetOwner(this);
	}

	if (LeftHandControllerClass)
	{
		LeftController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		LeftController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale); //SnapToTargetIncludeScale Eliminates Previous Transform Held
		LeftController->SetHand(EControllerHand::Left);
		LeftController->SetOwner(this);
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Draw"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("Draw"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAxis(TEXT("PaginateRight"), this, &AVRPawn::PaginateRight);
	//PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AVRPawn::Save);
}

void AVRPawn::PaginateRight(float AxisValue)
{
	int32 PaginationOffset = 0;
	PaginationOffset += AxisValue > PaginationThumbstickThreshold ? 1 : 0; //ternary operator 
	PaginationOffset += AxisValue < -PaginationThumbstickThreshold ? -1 : 0; 

	if (PaginationOffset != LastPaginationOffset && PaginationOffset != 0)
	{
		UpdateCurrentPage(PaginationOffset);
	}
	LastPaginationOffset = PaginationOffset;
}

void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	//Catches the potential error that if there was more than one Painting Picker, you'd update current page on all of them
	for (TActorIterator<APaintingPicker> PaintingPickerIterator(GetWorld()); PaintingPickerIterator; ++PaintingPickerIterator)
	{
		PaintingPickerIterator->UpdateCurrentPage(Offset); 
	}
}

void AVRPawn::Save()
{
	/*auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode()); //Returns the current Game Mode instance then cast it to PaintingGameMode
	if (!GameMode) return;
	GameMode->Save();
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu")); //Dont need options, default value is fine
	UStereoLayerFunctionLibrary::HideSplashScreen();*/
}


