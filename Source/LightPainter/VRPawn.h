// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "HandController.h"
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

	void Save();
	void Load();

	//Config
	UPROPERTY(EditDefaultsOnly) //Dont want to edit after play start
		TSubclassOf<AHandController> HandControllerClass;

	//Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	//References
	UPROPERTY()
		AHandController* RightController;

};
