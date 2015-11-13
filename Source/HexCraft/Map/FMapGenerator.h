// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FChunk.h"
#include "FPerlinNoiseGenerator2D.h"

/**
 * 
 */
class HEXCRAFT_API FMapGenerator
{
public:
	FMapGenerator();
	~FMapGenerator();
	
	// Returns a reference to a newly generated chunk
	FChunk& Generate(int32 X, int32 Y);

private:
	HexNoise::FPerlinNoiseGenerator2D Noise;
};
