// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayTagContainer.h"
#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetPhysicsHandle()->GetGrabbedComponent() != nullptr) 
	{
	
		FVector targetLocation = GetComponentLocation() + (GetForwardVector() * 150);
		GetPhysicsHandle()->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
}

bool UGrabber::GetHitResultInRange(FHitResult& outHitResult) const
{
	FCollisionShape circleShape = FCollisionShape::MakeSphere(shapeRadius);
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * maxGrabDistance;
	return GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, circleShape);
}

void UGrabber::ReleaseItem()
{
	UPrimitiveComponent* grabComponent = GetPhysicsHandle()->GetGrabbedComponent();
	if (grabComponent != nullptr)
	{
		GetPhysicsHandle()->ReleaseComponent();
		grabComponent->GetOwner()->Tags.Remove(GrabbedTag);
	}
}

void UGrabber::GrabItem()
{
	FHitResult hitResult;
	if(GetHitResultInRange(hitResult))	
	{
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 20, 20, FColor::Red, false, 5);	
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->WakeAllRigidBodies();
		hitComponent->SetSimulatePhysics(true);
		AActor* actor = hitComponent->GetOwner(); 
		actor->Tags.Add(GrabbedTag);
		actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		GetPhysicsHandle()->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation());
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	if (physicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("no physics handle"));
		return nullptr;
	}
	return physicsHandle;
}
