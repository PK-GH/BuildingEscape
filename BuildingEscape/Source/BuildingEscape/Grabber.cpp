// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Oh I grab things"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get player view point for this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	FString ViewLoc;
	FString ViewRot;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
	OUT PlayerViewPointLocation,
	OUT PlayerViewPointRotation
	);
	
	ViewLoc = PlayerViewPointLocation.ToString();
	ViewRot = PlayerViewPointRotation.ToString();

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
	
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *ViewLoc, *ViewRot);
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Do a line-trace (ray-cast) to reach distance

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	// Determine what is hit
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("In contact with: %s"), *(ActorHit->GetName()))
	}
	

}

