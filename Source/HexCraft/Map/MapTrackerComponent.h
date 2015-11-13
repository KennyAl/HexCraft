// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EarthMap.h"
#include "Components/ActorComponent.h"
#include "MapTrackerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXCRAFT_API UMapTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMapTrackerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:

	/** The instance of the current world map */
	AEarthMap* EarthMapRef;

	/** The id of the owning player */
	int32 ID;
};
