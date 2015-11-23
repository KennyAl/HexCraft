// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FSettings.h"
#include "Engine.h"

FSettings::FSettings()
{
	Loaded = false;
}

void FSettings::LoadSettings()
{
	/*check(GConfig);

	GConfig->LoadFile(TEXT("Test"));
	GConfig->GetInt(TEXT("Sec"), TEXT("ChunkSizeX"), ChunkSizeX, FString("Test"));*/
	DefaultSettings();
}

void FSettings::DefaultSettings()
{
	// Chunk settings
	ChunkSizeX = 16;
	ChunkSizeY = 16;
	ChunkSizeZ = 256;
	NumChunkSections = 8;
	BlockSize = 50.0f;
}