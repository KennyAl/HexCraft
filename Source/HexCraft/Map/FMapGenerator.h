// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FChunk.h"

/**
 * 
 */
class HEXCRAFT_API FMapGenerator
{
public:
	FMapGenerator();
	~FMapGenerator();

	void Generate(FChunk& Chunk);

private:
	HexNoise::FPerlinNoiseGenerator2D Noise;
};
