// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * Static class holding all settings that were read from the .set file at startup
 */
class HEXCRAFT_API FSettings
{
public:

	// Chunk settings
	static int32 ChunkSizeX;
	static int32 ChunkSizeY;
	static int32 ChunkSizeZ;
	static int32 NumChunkSections;
	static int32 ChunkSectionHeight;
	static float BlockSize;


	static void DefaultSettings();

};
