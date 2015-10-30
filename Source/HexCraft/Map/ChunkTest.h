// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "FChunk.h"
#include "FMeshFactory.h"
#include "GameFramework/Actor.h"
#include "ChunkTest.generated.h"

UCLASS()
class HEXCRAFT_API AChunkTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkTest(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category = "Debug")
	int32 GetBlock(int32 X, int32 Y, int32 Z);

private:

	/** Test chunk */
	FChunk TestChunk;

	/** Test chunk mesh */
	UProceduralMeshComponent* ProcMeshComp;

	/** Root */
	USceneComponent* RootScene;

};
