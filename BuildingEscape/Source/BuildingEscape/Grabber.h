// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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

	FVector GetLineTraceEnd();

	// Ray cast and grab what's in reach
	virtual void Grab();
	virtual void Release();
	//make getters for the Physics handle and inputcomponent
	virtual void FindPhysicsHandle();
	virtual void SetupInputComponent();

	const FHitResult GetFirstPhysicsBodyInReach();
	

private:

	float Reach = 100.0f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
		
	UInputComponent* InputComponent = nullptr;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
};
