// Fill out your copyright notice in the Description page of Project Settings.


#include "LightPainterSaveGame.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Guid.h"
#include "PainterSaveGameIndex.h"
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
	//Static class function retruns "this" class type, Cast is to change it to proper return type  because create save game object will be of type USaveGame
	ULightPainterSaveGame* NewSaveGame = Cast<ULightPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if (!NewSaveGame->Save()) return nullptr; //makes sure it saves so you don't add to index and later forget to save it

	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();// Load the index
	Index->AddSlotName(NewSaveGame);
	Index->Save();
	return NewSaveGame; 
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

ULightPainterSaveGame* ULightPainterSaveGame::Load(FString SlotName) //SlotName doesn't simply work in Load because it is static and doesn't have access to instanced variables yet when called
{
	USaveGame* LoadSaveGame = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	return  Cast<ULightPainterSaveGame>(LoadSaveGame);
}

bool ULightPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0); //Creates Save Slot
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
