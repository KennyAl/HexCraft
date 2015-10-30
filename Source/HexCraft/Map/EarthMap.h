// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "EarthMap.generated.h"

UCLASS()
class HEXCRAFT_API AEarthMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEarthMap(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Loads a chunk from savegame or generates a new one */
	void LoadChunk();

private:

	/** Test chunk mesh */
	UProceduralMeshComponent* ProcMeshComp;
	
};
