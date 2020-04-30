// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "HandControllerBase.h"
#include "UIPointerHandController.generated.h"

/**
 * 
 */
UCLASS() 
class LIGHTPAINTER_API AUIPointerHandController : public AHandControllerBase
{
	GENERATED_BODY()

public:
		AUIPointerHandController();

		void Draw() override; //override is just a safeguard, because it will fail if you don't override something in the base class
		void DrawStop() override;

private:
	UPROPERTY(VisibleAnywhere)
		UWidgetInteractionComponent* Pointer;
	
};
