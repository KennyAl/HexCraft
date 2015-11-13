// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FBlockBase.h"

enum class ESectionFlags : uint8
{
	IsAir			= 0x01,
	IsNotSurface	= 0x02,
	IsCleared		= 0x04,
};

/**
 * Section that contains 16*16*16 blocks
 * Each chunk consists of 16 sections
 * These sections allow easy mesh building and checks without looking at every single block
 */
class HEXCRAFT_API FChunkSection
{
public:

	/** Constructor */
	FChunkSection();

	/** Destructor */
	~FChunkSection();

	/** Returns the ID of the block at the given relative coordinates 
	* All coordinates have to be 0-15, otherwise the 0 will be returned
	*/
	inline const uint16 GetBlockIDAt(uint8 X, uint8 Y, uint8 Z);

	/** Sets the ID of the block at the given coordinates */
	inline void SetBlockIDAt(uint8 X, uint8 Y, uint8 Z, uint16 ID);

	/** If not already done, all resources will be initialized */
	void InitializeSection();

	/** Deletes all block data */
	void ClearSection();

	//
	// Flags
	// 

	/** Returns the value of the IsDestructable flag */
	inline const uint8 GetIsAir();

	/** Returns the value of the IsStatic flag */
	inline const uint8 GetIsNotSurface();

	/** Returns the value of the IsStatic flag */
	inline const uint8 GetIsCleared();

	/** Sets the value of the IsAir flag */
	inline void SetIsAir(uint8 IsAir);

	/** Sets the value of the IsNotSurface flag */
	inline void SetIsNotSurface(uint8 IsNotSurface);

	/** Sets the value of the IsCleared flag */
	inline void SetIsCleared(uint8 IsCleared);

private:

	/** 3 dimensional array containing all blocks */
	uint16*** Blocks;

	/** Byte-size value to hold the states of the flags above */
	uint8 Flags;

	//TStaticArray<TStaticArray<TStaticArray<uint16, 16>, 16>, 16> Block;
};
