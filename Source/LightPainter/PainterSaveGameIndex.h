// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LightPainterSaveGame.h"
#include "PainterSaveGameIndex.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGameIndex : public USaveGame
{
	GENERATED_BODY()

public:
    //Update Index everytime you create new slot
    static UPainterSaveGameIndex* Load(); //also creates first save game if all else fails
    bool Save(); //boolean because it can fail 
    void AddSlotName(ULightPainterSaveGame* NewSaveGame); // add new painting to index
    TArray<FString> GetSlotNames() const {return SlotNames;}

private:
    static const FString SLOT_NAME;

    UPROPERTY() //A way to Serialize  what you need into the save game
        TArray<FString> SlotNames;

};
