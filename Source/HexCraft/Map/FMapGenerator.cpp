// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FMapGenerator.h"

FMapGenerator::FMapGenerator()
{
	FPerlinNoiseSettings Settings;
	Settings.bSmooth = false;
	Settings.Oktaves = 1;
	Settings.InterpMethod = EInterpMethod::Cosine;
	Settings.InitialAmplitude = 30;
	Settings.InitialFrequency = 0.05;
	Noise.NoiseSettings = Settings;
}

FMapGenerator::~FMapGenerator()
{
}

FChunk& FMapGenerator::Generate(int32 _X, int32 _Y)
{
	// Create a new chunk
	FChunk* ChunkPtr = new FChunk();
	check(ChunkPtr != nullptr);
	FChunk& Chunk = *ChunkPtr;

	for (int32 X = 0; X < 16; X++)
		for (int32 Y = 0; Y < 16; Y++)
			for (int32 Z = 0; Z < FMath::Abs(FMath::RoundToInt(Noise.GetNoise(_X * 16 + X, _Y * 16 + Y))); Z++)
				Chunk.SetBlockIDAt(X, Y, Z, 1);
	
	return Chunk;
}