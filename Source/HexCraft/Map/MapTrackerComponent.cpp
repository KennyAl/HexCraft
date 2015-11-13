// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "MapTrackerComponent.h"


// Sets default values for this component's properties
UMapTrackerComponent::UMapTrackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	EarthMapRef = nullptr;
	
	ID = -1;
}


// Called when the game starts
void UMapTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the instance of the earth map 
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AEarthMap::StaticClass(), OutActors);

	// If the array is empty assert
	check(OutActors.Num() != 0);

	EarthMapRef = static_cast<AEarthMap*>(OutActors[0]);
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	ID = EarthMapRef->RegisterActivePlayer(*Owner);
}


// Called every frame
void UMapTrackerComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Update the location of the owner in the player register of the map
	auto Ref = EarthMapRef->GetPlayerByID(ID);
	Ref.Location = GetOwner()->GetActorLocation();
}

