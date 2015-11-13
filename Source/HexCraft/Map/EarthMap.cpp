// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "EarthMap.h"
#include "FMeshFactory.h"
#include "FSettings.h"


// Sets default values
AEarthMap::AEarthMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set up the procedural mesh component
	for (int32 Y = 0; Y < ViewDistance; Y++)
		for (int32 X = 0; X < ViewDistance; X++)
		{
			FString StringHelper = FString::FromInt(Y * ViewDistance + X);
			FName Name(*StringHelper);
			Meshes.Add(ObjectInitializer.CreateDefaultSubobject<UProceduralMeshComponent>(this, Name));
			Meshes[Y * ViewDistance + X]->SetWorldLocation(FVector(X * 16 * 50, Y * 16 * 50, 0));
		}

	FSettings::DefaultSettings();
}

// Called when the game starts or when spawned
void AEarthMap::BeginPlay()
{
	Super::BeginPlay();
	LoadChunk();
}

// Called every frame
void AEarthMap::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AEarthMap::LoadChunk()
{
	for (int32 X = 0; X < ViewDistance; X++)
		for (int32 Y = 0; Y < ViewDistance; Y++)
		{
			FChunk& Ref = MapGen.Generate(X, Y);

			TSharedPtr < sMeshData > MeshData;

			MeshData = FMeshFactory::BuildMeshFromChunkB(Ref);

			TArray<FColor> VertexColors;

			TArray<FProcMeshTangent> Tangents;

			Meshes[Y * ViewDistance + X]->CreateMeshSection
				(0, MeshData->Vertices, MeshData->Triangles, MeshData->Normals, MeshData->UVs, VertexColors, Tangents, true);
		}
}

void AEarthMap::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Meshes.Empty();

	// Empty the player register
	PlayerRegister.Empty();
}

int32 AEarthMap::RegisterActivePlayer(ACharacter& NewPlayer)
{
	FPlayerEntry* Entry = new FPlayerEntry;
	Entry->CharRef = &NewPlayer;
	return PlayerRegister.Add(Entry);
}

FPlayerEntry& AEarthMap::GetPlayerByID(int32 ID)
{
		check(PlayerRegister.IsValidIndex(ID))
		return *PlayerRegister[ID];
}
