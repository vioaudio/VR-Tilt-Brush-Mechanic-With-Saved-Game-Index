// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "HandControllerBase.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void RightTriggerPressed() { if (RightController) RightController->Draw(); }
	void RightTriggerReleased() { if (RightController) RightController->DrawStop(); }
	void PaginateRight(float AxisValue);
	void UpdateCurrentPage(int32 Offset);
	void Save();

	//Config
	UPROPERTY(EditDefaultsOnly) //Dont want to edit after play start
		TSubclassOf<AHandControllerBase> RightHandControllerClass;
	UPROPERTY(EditDefaultsOnly) //Dont want to edit after play start
		TSubclassOf<AHandControllerBase> LeftHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
		float PaginationThumbstickThreshold = 0.9;

	//Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	//References
	UPROPERTY()
		AHandControllerBase* RightController;

	UPROPERTY()
		AHandControllerBase* LeftController;

	//State
	int32 LastPaginationOffset = 0;
};
