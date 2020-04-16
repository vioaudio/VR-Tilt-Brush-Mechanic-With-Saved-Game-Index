// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Stroke Meshes"));
	StrokeMeshes->SetupAttachment(Root);

	JointMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Joint Meshes"));
	JointMeshes->SetupAttachment(Root);
}

FTransform AStroke::GetNextSegmentTransform(FVector CurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetScale3D(GetNextSegmentScale(CurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CurrentLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));

	return SegmentTransform;
}

FTransform AStroke::GetNextJointTransform(FVector CurrentLocation) const
{
	FTransform JointTransform;
	JointTransform.SetLocation(GetTransform().InverseTransformPosition(CurrentLocation));
	return JointTransform;
}

FVector AStroke::GetNextSegmentLocation(FVector CurrentLocation) const
{
	return GetTransform().InverseTransformPosition(PreviousCursorLocation);
}

FQuat AStroke::GetNextSegmentRotation(FVector CurrentLocation) const
{
	FVector Segment = CurrentLocation - PreviousCursorLocation;
	FVector SegmentNormal = Segment.GetSafeNormal();
	
	return FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentNormal); 
}

FVector AStroke::GetNextSegmentScale(FVector CurrentLocation) const
{
	FVector Segment = CurrentLocation - PreviousCursorLocation;
	return FVector(Segment.Size(), 1, 1);
}

void AStroke::Update(FVector CursorLocation) //When drawing Cursor Location is the Location of the Controller of that frame
{
	if (PreviousCursorLocation.IsNearlyZero()) //So the first point doesn't start at (0,0,0)
	{
		PreviousCursorLocation = CursorLocation;
		JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
		return;
	}
	StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
	JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
	PreviousCursorLocation = CursorLocation;

	/*USplineMeshComponent* Spline = CreateSplineMesh();
	//Update EndPoints
	FVector StartPos, StartTangent, EndPos, EndTangent;
	StartPos = GetActorTransform().InverseTransformPosition(CursorLocation); //Can use get transform because stroke will be at the root of the actor, then invert it to local space
	EndPos = GetActorTransform().InverseTransformPosition(PreviousCursorLocation);//What was Last Updated

	Spline->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent); //Sets paramaeters of spline

	PreviousCursorLocation = CursorLocation; //Used as end position in Next frame while drawing*/
}

/*USplineMeshComponent* AStroke::CreateSplineMesh()
{
	USplineMeshComponent* NewSpline = NewObject<USplineMeshComponent>(this); //creates new static mesh at runtime
	NewSpline->SetMobility(EComponentMobility::Movable);
	NewSpline->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale); // Can pass on endpoints in local space more easiliy
	NewSpline->SetStaticMesh(SplineMesh); //Sets Mesh during Runtime
	NewSpline->SetMaterial(0, SplineMaterial); //Sets Material during Runtime to material at index (0)
	NewSpline->RegisterComponent();

	return NewSpline;
}*/

