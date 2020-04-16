// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

		//Setup Custom API to avoid a lot of casting
public:
	//Creates new save games to populate, static because this is not a method on the instance, because a Save Game has not yet been created,
	//rather we need to get a hold of UPainterSaveGame
		static UPainterSaveGame* Create(); 

		static UPainterSaveGame* Load();//Static because we want to get a UPainterSaveGame Out of it, which means we don't have one yet
		
		bool Save(); //not static because used on the instance itself when it asks "have we successfully saved" when calling the SaveGameToSlot function

		void SetState(FString NewState) { State = NewState; }
		FString GetState() const { return State;}

		void SerializeFromWorld(UWorld* World); //takes the current state of the world and put it into the Save Game Class
		void DeserializeFromWorld(UWorld* World); //take world from save game and put it into the world
private:
	void Clearworld(UWorld* World);

	//State
	UPROPERTY()
		FString State; //Property that will be populated
	UPROPERTY()
		//Property to Store the strokes, need the type of stroke, which means you need access to the Blueprint or subclass
		TArray<TSubclassOf<class AStroke>> Strokes; //Will be used to capture the state of the world and put it back into the world
};
