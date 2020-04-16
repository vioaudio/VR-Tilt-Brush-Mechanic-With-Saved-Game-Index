// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Stroke.h"

/*void UPainterSaveGame::Clearworld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeIterator(World); StrokeIterator; ++StrokeIterator)
	{
		StrokeIterator->Destroy();
	}
}

UPainterSaveGame* UPainterSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass()); //Static class function retruns "this" class types

	return Cast<UPainterSaveGame>(NewSaveGame); //Cast to change it to proper return type
}

void UPainterSaveGame::DeserializeFromWorld(UWorld* World)
{
	//clear the world

	//For all strokes, spawn a stroke of that type
}


UPainterSaveGame* UPainterSaveGame::Load()
{
	USaveGame* LoadSaveGame = UGameplayStatics::LoadGameFromSlot(TEXT("Test"), 0);
	return  Cast<UPainterSaveGame>(LoadSaveGame);
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Test"), 0); //Creates Save Slot
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	//clear the array
	Strokes.Empty();
	//iterate over all stroke and serialize them
	for (TActorIterator<AStroke> StrokeIterator(World); StrokeIterator; ++StrokeIterator) //TActorIterator Bass class is a template class used to filter actors by certain characteristics
	{
		Strokes.Add(StrokeIterator->GetClass()); //get class of stroke and passes it into array so you get the correct blueprint class
	}
	//Store the class type in the array
}*/



