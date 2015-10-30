// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "ChunkTest.h"
#include "FPerlinNoiseGenerator2D.h"


// Sets default values
AChunkTest::AChunkTest(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set up the procedural mesh component
	ProcMeshComp = ObjectInitializer.CreateDefaultSubobject<UProceduralMeshComponent>(this, TEXT("ProceduralMeshComponent"));
	RootScene = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = RootScene;
	ProcMeshComp->SetWorldLocation(FVector(0));

}

// Called when the game starts or when spawned
void AChunkTest::BeginPlay()
{
	Super::BeginPlay();
	FRandomStream Random;
	Random.Initialize(1);
	
	HexNoise::FPerlinNoiseGenerator2D Noise;
	
	Noise.NoiseSettings.InitialAmplitude = 30;
	Noise.NoiseSettings.InterpMethod = EInterpMethod::Cubic;
	Noise.NoiseSettings.bSmooth = false;
	Noise.NoiseSettings.Seed = 1;
	Noise.NoiseSettings.Oktaves = 1;
	Noise.NoiseSettings.InitialFrequency = 0.05;
	FTransform trans(FVector(600, 600, 0));
	
	//Loop through every block in this section and create a mesh on all sides that are visible
	//for (int32 Z = 0; Z < 128; Z++)
	//{
	//	for (int32 Y = 0; Y < 16; Y++)
	//	{
	//		for (int32 X = 0; X < 16; X++)
	//		{
	//			/*if (X < 2 && Y == 0 && Z == 0)
	//			TestChunk.GetSection(Section)->SetBlockIDAt(X, Y, Z, 1);
	//			else
	//			TestChunk.GetSection(Section)->SetBlockIDAt(X, Y, Z, 0);*/
	//			/*if (Random.FRandRange(0, 99) < 10)
	//				TestChunk.SetBlockIDAt(X, Y, Z, 1);
	//				else
	//				TestChunk.SetBlockIDAt(X, Y, Z, 0);*/
	//			/*if ((X + Y) <= Z)
	//			TestChunk.GetSection(Section)->SetBlockIDAt(X, Y, Z, 1);
	//			else
	//			TestChunk.GetSection(Section)->SetBlockIDAt(X, Y, Z, 0);*/
	//			//TestChunk.SetBlockIDAt(X, Y, Z, 1);
	//		}
	//	}
	//}
	for (int32 X = 0; X < 16; X++)
		for (int32 Y = 0; Y < 16; Y++)
			for (int32 Z = 0; Z < FMath::Abs(FMath::RoundToInt(Noise.GetNoise(X, Y))); Z++)
				TestChunk.SetBlockIDAt(X, Y, Z, 1);
	
	//UE_LOG(LogTemp, Warning, TEXT("Id: %d"), static_cast<int32>(TestChunk.GetBlockIDAt(0, 2, 0)));

	TSharedPtr < sMeshData > MeshData;

	MeshData = FMeshFactory::BuildMeshFromChunkB(TestChunk);

	TArray<FColor> VertexColors;

	TArray<FProcMeshTangent> Tangents;
	
	ProcMeshComp->CreateMeshSection
		(0, MeshData->Vertices, MeshData->Triangles, MeshData->Normals, MeshData->UVs, VertexColors, Tangents, true);
}

// Called every frame
void AChunkTest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AChunkTest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//for (uint32 Section = 0; Section < TestChunk.GetNumSections(); Section++)
	//{
		// Loop through every block in this section and create a mesh on all sides that are visible
		for (int32 Z = 0; Z < 16; Z++)
			for (int32 Y = 0; Y < 16; Y++)
				for (int32 X = 0; X < 16; X++)
				{
					//TestChunk.GetSection(Section)->SetBlock(X, Y, Z, 1);
				}
	//}

	//TSharedPtr < sMeshData > MeshData;

	//MeshData = FMeshFactory::BuildMeshFromChunk(TestChunk);

	TArray<FColor> VertexColors;
	/*VertexColors.Add(FColor::Blue);
	VertexColors.Add(FColor::Blue);
	VertexColors.Add(FColor::Blue);
	VertexColors.Add(FColor::Blue);*/

	TArray<FProcMeshTangent> Tangents;
	/*Tangents.Add(FProcMeshTangent(1, 0, 0));
	Tangents.Add(FProcMeshTangent(1, 0, 0));
	Tangents.Add(FProcMeshTangent(1, 0, 0));
	Tangents.Add(FProcMeshTangent(1, 0, 0));*/

	//ProcMeshComp->CreateMeshSection
		//(0, MeshData->Vertices, MeshData->Triangles, MeshData->Normals, MeshData->UVs, VertexColors, Tangents, false);
}

int32 AChunkTest::GetBlock(int32 X, int32 Y, int32 Z)
{
	if (TestChunk.GetNumSections() != 8)
		return 7;

	return TestChunk.GetSection(0)->GetBlockIDAt(X, Y, Z);
}

