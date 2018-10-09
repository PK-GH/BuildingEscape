// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor2.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor2::UOpenDoor2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor2::BeginPlay()
{
	Super::BeginPlay();

	OpeningActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}


// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float delay = 0.73f;
	float CurrentTime;

	if(PressurePlate->IsOverlappingActor(OpeningActor))
	{
		OpenDoor2();
		SetTripTime();
	}

	CurrentTime = GetWorld()->GetTimeSeconds();

	if(CurrentTime > (GetTripTime() + delay))
	{
		CloseDoor2();
	}
}
void UOpenDoor2::OpenDoor2()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
}
void UOpenDoor2::CloseDoor2()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, CloseAngle, 0.0f);
	Owner->SetActorRotation(NewRotation);
}
void UOpenDoor2::SetTripTime()
{
	TripTime = GetWorld()->GetTimeSeconds();
}
float UOpenDoor2::GetTripTime()
{
	return TripTime;
}