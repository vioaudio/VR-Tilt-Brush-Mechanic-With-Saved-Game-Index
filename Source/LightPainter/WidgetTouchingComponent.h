// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "WidgetTouchingComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) //need to do custom annotation to get a custom widget to show up in the editor
class LIGHTPAINTER_API UWidgetTouchingComponent : public UWidgetInteractionComponent
{
	GENERATED_BODY()

public:
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//state
	bool bIsClicked = false;
};
