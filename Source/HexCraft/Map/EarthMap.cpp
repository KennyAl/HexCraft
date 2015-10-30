// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "EarthMap.h"


// Sets default values
AEarthMap::AEarthMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set up the procedural mesh component
	ProcMeshComp = ObjectInitializer.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("ProceduralMeshComponent"));
}

// Called when the game starts or when spawned
void AEarthMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEarthMap::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEarthMap::LoadChunk()
{

}

