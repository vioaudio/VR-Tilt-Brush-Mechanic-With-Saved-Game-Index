// Fill out your copyright notice in the Description page of Project Settings.


#include "LightPainterSaveGame.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Stroke.h"

void ULightPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeIterator(World); StrokeIterator; ++StrokeIterator)
	{
		StrokeIterator->Destroy();
	}
}

ULightPainterSaveGame* ULightPainterSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass()); //Static class function retruns "this" class types

	return Cast<ULightPainterSaveGame>(NewSaveGame); //Cast to change it to proper return type
}

void ULightPainterSaveGame::DeserializeFromWorld(UWorld* World)
{
	//clear the world
	ClearWorld(World);

	//For all strokes, spawn a stroke of that type
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState); //Creates the struct
	}	
}

ULightPainterSaveGame* ULightPainterSaveGame::Load()
{
	USaveGame* LoadSaveGame = UGameplayStatics::LoadGameFromSlot(TEXT("Test"), 0);
	return  Cast<ULightPainterSaveGame>(LoadSaveGame);
}

bool ULightPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Test"), 0); //Creates Save Slot
}

void ULightPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	//clear the array
	Strokes.Empty();
	//iterate over all stroke and serialize them
	for (TActorIterator<AStroke> StrokeIterator(World); StrokeIterator; ++StrokeIterator) //TActorIterator Bass class is a template class used to filter actors by certain characteristics
	{
		Strokes.Add(StrokeIterator->SerializeToStruct()); //Returns the state of the stroke
	}
	//Store the class type in the array
}
