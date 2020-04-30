// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PaintingPicker.h"
#include "ActionBar.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UActionBar : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize() override; //widget version of begin play
	void SetParentPicker(APaintingPicker* NewParentPicker){ParentPicker = NewParentPicker;}

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* Add;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* Delete;

private:
	UFUNCTION()
	void AddButtonClicked();
	UFUNCTION()
	void DeleteButtonClicked();

	//private pointer to point up to the painting picker (the parent)
	UPROPERTY()
		APaintingPicker* ParentPicker;
};
