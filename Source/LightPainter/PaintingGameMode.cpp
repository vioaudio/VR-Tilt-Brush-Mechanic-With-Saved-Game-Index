// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"
#include "LightPainterSaveGame.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

//Warning: InitGame is called before the actors PreInitialize Components, so cannot use it to bring in the drawings in this case, use BeginPlay since it's a child of AActor
void APaintingGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage); //Must call to Super whenever you do a virtual function

	//handle options and parse out the ones you want
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");

	UE_LOG(LogTemp, Warning, TEXT("SlotName: %s"), *SlotName);
}
void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();
	Load();
	UStereoLayerFunctionLibrary::HideSplashScreen();
}

void APaintingGameMode::Save()
{
	ULightPainterSaveGame* Painting = ULightPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
	}
}

void APaintingGameMode::Load()
{
	ULightPainterSaveGame* Painting = ULightPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->DeserializeFromWorld(GetWorld());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Slot Not Found: %s"), *SlotName);
	}
}

void APaintingGameMode::SaveAndQuit()
{
	Save();
	//UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu")); //Dont need options, default value is fine
	//UStereoLayerFunctionLibrary::HideSplashScreen();
}

