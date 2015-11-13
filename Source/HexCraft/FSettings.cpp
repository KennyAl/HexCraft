// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FSettings.h"

void FSettings::DefaultSettings()
{
	// Chunk settings
	ChunkSizeX = 16;
	ChunkSizeY = 16;
	ChunkSizeZ = 256;
	NumChunkSections = 8;
	ChunkSectionHeight = 16;
	BlockSize = 50.0f;
}
