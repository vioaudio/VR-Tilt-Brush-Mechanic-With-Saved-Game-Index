// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.h"
#include "HandControllerBase.h"
#include "PaintBrushHandController.generated.h"



UCLASS()
class LIGHTPAINTER_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintBrushHandController();

	void Draw() override; //override is just a safeguard, because it will fail if you don't override something in the base class
	void DrawStop() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	

	//State
		AStroke* CurrentStroke;

	//Config
	UPROPERTY(EditDefaultsOnly) //Dont want to edit after play start
		TSubclassOf<AStroke> StrokeClass;

};
