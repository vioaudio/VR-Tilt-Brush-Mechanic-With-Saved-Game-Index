// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LightPainterSaveGame.generated.h"

/**
 * 
 */

//Also need the list of locations that made up the strokes, so will need a Struct to represent a more complex data type
//it will give "structure" to the data we are trying to serialize

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()

		UPROPERTY()
		TSubclassOf<class AStroke> Class; //The class of the stroke, Part of the state that makes up what a stroke actually is

	UPROPERTY()
		TArray<FVector> ControlPoints; //Will host the locations of all the strokes
};

UCLASS()

class LIGHTPAINTER_API ULightPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

		//Setup Custom API to avoid a lot of casting
public:
	//Creates new save games to populate, static because this is not a method on the instance, because a Save Game has not yet been created,
	//rather we need to get a hold of UPainterSaveGame
	static ULightPainterSaveGame* Create();

	static ULightPainterSaveGame* Load(FString SlotName);//Static because we want to get a UPainterSaveGame Out of it, which means we don't have one yet

	bool Save(); //not static because used on the instance itself when it asks "have we successfully saved" when calling the SaveGameToSlot function

	void SetState(FString NewState) { State = NewState; }
	FString GetState() const { return State; }

	void SerializeFromWorld(UWorld* World); //takes the current state of the world and put it into the Save Game Class
	void DeserializeFromWorld(UWorld* World); //take world from save game and put it into the world

	FString GetSlotName() const { return SlotName; } //Getter for the GUID

private:
	void ClearWorld(UWorld* World);

	//State
	UPROPERTY()
		FString State; //Property that will be populated

	UPROPERTY()
		FString SlotName;

	UPROPERTY()
		//Property to Store the strokes, need the type of stroke, which means you need access to the Blueprint or subclass
		TArray<FStrokeState> Strokes; //Will be used to capture the state of the world and put it back into the world
};

