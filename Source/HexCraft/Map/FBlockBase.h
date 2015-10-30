// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct RelBlockCoords
{
	uint8 X;
	uint8 Y;
	uint8 Z;
};

enum class EBlockFlags : uint8
{
	IsDestructible	= 0x01,
	IsStatic		= 0x02,
};


/**
 * Base class for all blocks
 */
class HEXCRAFT_API FBlockBase
{
public:

	/** Constructor */
	FBlockBase(uint8 X, uint8 Y, uint8 Z);

	/** Destructor */
	~FBlockBase();

	/** Use this to define behavior that runs when one of the neighbor blocks change 
	* Every child class of BlockBase needs to override this function
	* This will call BlockUpdate() on all surrounding blocks if they are not static
	*/
	virtual void BlockUpdate() = 0;

	/** Returns a reference to the block coordinates relative to the chunk this block is in */
	inline const RelBlockCoords& GetCoords(){ return Coords; }

	//
	// Flags
	// 

	/** Returns the value of the IsDestructable flag */
	inline const uint8 GetIsDestructible();

	/** Returns the value of the IsStatic flag */
	inline const uint8 GetIsStatic();

	/** Sets the value of the IsDestructable flag */
	inline void SetIsDestructible(uint8 IsDestructible);

	/** Sets the value of the IsStatic flag */
	inline void SetIsStatic(uint8 IsStatic);


private:
	
	/** Coordinates relative to the chunk this block is in (from x/y/z min) */
	RelBlockCoords Coords;

	/** Byte-size value to hold the states of the flags above */
	uint8 Flags;
};


// Flags
// IsDestructible
// IsStatic
