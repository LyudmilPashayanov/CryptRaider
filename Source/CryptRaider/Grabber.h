// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent,BlueprintType) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GrabItem();
	void ReleaseItem();

private:
	UPROPERTY(EditAnywhere)
	float maxGrabDistance=400;
	
	UPROPERTY(EditAnywhere)
	float shapeRadius = 100;

	UPROPERTY(EditAnywhere)
	FName GrabbedTag;

	UPhysicsHandleComponent* physicsHandle;

	bool GetHitResultInRange(FHitResult& hitResult) const;
	UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const;

};
