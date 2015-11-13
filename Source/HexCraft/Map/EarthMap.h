// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FMapGenerator.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "EarthMap.generated.h"

USTRUCT()
struct FPlayerEntry
{
	GENERATED_BODY()

	ACharacter* CharRef;
	FVector Location;
};

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

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/** Creates a new entry in the active players register and returns its id */
	int32 RegisterActivePlayer(ACharacter& NewPlayer);

	/** Returns a reference to the register entry */
	FPlayerEntry& GetPlayerByID(int32 ID);

private:

	/** Test chunk mesh */
	//UProceduralMeshComponent* ProcMeshComp;
	TArray<UProceduralMeshComponent*> Meshes;

	FMapGenerator MapGen;
	
	const int32 ViewDistance = 20;

	/** The player register */
	TArray<FPlayerEntry*> PlayerRegister;
};
