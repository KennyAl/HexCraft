// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FBlockBase.h"

/**
 * Class granting access to different registers.
 * Each register maps an ID of a block or item to an instance of a class which describes the behavior of the
 * object
 * This way a chunk only needs to save IDs for every coordinate, but not an instance of the objects class
 * 
 * This class will not create a register by itself upon initialization, but needs to get input 
 * from a different source !
 */
class HEXCRAFT_API FIDRegister
{
public:

	/** Constructor */
	FIDRegister();

	/** Destructor */
	~FIDRegister();

//	/** Sets the internal pointer to a new BLockIDRegister */
//	static void SetBlockIDRegister(TArray<FBlockBase*>* NewBlockIDRegister);
//
//	/** Returns the register entry for a given ID (null if not existent)
//	* @param ID		The ID to look for
//	* @returns		Const pointer to the entry
//	*/
//	static const FBlockBase* GetBlockByID(uint16 ID);
//
//	/** Checks if the block register exists
//	* @returns	True if existent
//	*/
//	static bool BlockIDRegisterExists();
//
//private:
//
//	/** Clears BlockIDRegister */
//	static void ClearBlockIDRegister();
//
//	/** Pointer to the block ID register */
//	static TArray<FBlockBase*>* BlockIDRegister;
};
