// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	AActor* owner = GetOwner();
	originalPos = owner->GetActorLocation();
	FBox box = owner->GetComponentsBoundingBox();
	float doorHeight = box.GetSize().Z;
	endPos = FVector{ originalPos.X, originalPos.Y, originalPos.Z - doorHeight };
	FString endPosString = endPos.ToCompactString();
	duration = FVector::Distance(originalPos, endPos) / 4;
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (startMovement) {
		FVector interpPos = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), endPos, DeltaTime, duration);
		GetOwner()->SetActorLocation(interpPos);
	}
}

void UMover::EnableMover(bool enable)
{
	startMovement = enable;
}

