// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FSettings.h"
#include "FChunkSection.h"

/**
* A piece of the world that consists of 16*16*256 blocks or 16 sections
*/
class HEXCRAFT_API FChunk
{
public:

	/** Constructor */
	FChunk();

	/** Destructor */
	~FChunk();

	/** Returns a pointer to the section at the given index */
	FChunkSection* GetSection(uint32 Index);

	/** Returns the number of sections this chunk has */
	uint32 GetNumSections();

	/** Returns a block by its coordinates in the chunk */
	inline uint8 GetBlockIDAt(uint8 X, uint8 Y, uint8 Z);

	/** Sets the ID of the block at the given coordinates */
	inline void SetBlockIDAt(uint8 X, uint8 Y, uint8 Z, uint16 ID);

private:

	/** Array of all sections that are belonging to this chunk (0 is bottom, n is top)*/
	TArray<FChunkSection*> Sections;


};
