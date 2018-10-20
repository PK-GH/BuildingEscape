// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float delay = 0.49f;
	float CurrentTime;
	int TriggerMass = 32;
	if (GetTotalMassActorsOnPlate() > TriggerMass)
	{
		OpenDoor();
		SetTripTime();
	}

	CurrentTime = GetWorld()->GetTimeSeconds();

	if(CurrentTime > (GetTripTime() + delay))
	{
		CloseDoor();
	}
}
int UOpenDoor::GetTotalMassActorsOnPlate()
{
	int TotalMass = 0;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate"), *Actor->GetName());
		int Mass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += Mass;
	}

	return TotalMass;
}

void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
}
void UOpenDoor::CloseDoor()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, CloseAngle, 0.0f);
	Owner->SetActorRotation(NewRotation);
}
void UOpenDoor::SetTripTime()
{
	TripTime = GetWorld()->GetTimeSeconds();
}
float UOpenDoor::GetTripTime()
{
	return TripTime;
}