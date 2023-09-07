// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* actor = GetAcceptableActor();
	if(actor != nullptr)
	{
		mover->UnlockMover(true);
		UPrimitiveComponent* primitiveComponent = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (primitiveComponent != nullptr) 
		{
			primitiveComponent->AttachToComponent(GetAttachmentRoot(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
			primitiveComponent->SetSimulatePhysics(false);
		}
	}
	else
	{
		if(mover)
			mover->UnlockMover(false);
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);

	for (AActor* actor : actors)
	{
		if (actor->ActorHasTag(UnlockTag) && actor->ActorHasTag(GrabbedTag) == false)
		{
			return actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::InjectMover(UMover* newMover)
{
	mover = newMover;
}




