// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Stroke.generated.h"

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	AStroke();

	UFUNCTION()
	void Update(FVector CursorLocation);

private:

	FTransform GetNextSegmentTransform(FVector CurrentLocation) const; //Const because it doesn't need to change anything it's just a getter
	FTransform GetNextJointTransform(FVector CurrentLocation) const; //Const because it doesn't need to change anything it's just a getter

	FVector GetNextSegmentLocation(FVector CurrentLocation) const;
	FQuat GetNextSegmentRotation(FVector CurrentLocation) const;
	FVector GetNextSegmentScale(FVector CurrentLocation) const;
	

	//Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	//Config
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* StrokeMeshes;
	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* JointMeshes;

	//State
	FVector PreviousCursorLocation;
};
