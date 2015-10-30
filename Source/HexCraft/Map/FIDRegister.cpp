// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FIDRegister.h"

FIDRegister::FIDRegister()
{
}

FIDRegister::~FIDRegister()
{
	//ClearBlockIDRegister();
}
//
//void FIDRegister::SetBlockIDRegister(TArray<FBlockBase*>* NewBlockIDRegister)
//{
//	// If there is an old register, clear it
//	if (BlockIDRegister != nullptr)
//		ClearBlockIDRegister();
//
//	// Set the pointer to the new register
//	BlockIDRegister = NewBlockIDRegister;
//}
//
//const FBlockBase* FIDRegister::GetBlockByID(uint16 ID)
//{
//	if (BlockIDRegister != nullptr)
//	{
//		if (BlockIDRegister->IsValidIndex(ID))
//			return (*BlockIDRegister)[ID];
//	}
//		return nullptr;
//}
//
//bool FIDRegister::BlockIDRegisterExists()
//{
//	return BlockIDRegister == nullptr ? false : true;
//}
//
//void FIDRegister::ClearBlockIDRegister()
//{
//	// Clear all existing registers
//	if (BlockIDRegister != nullptr)
//	{
//		for (int32 CurrentIndex = 0; CurrentIndex < BlockIDRegister->Num(); CurrentIndex++)
//			if ((*BlockIDRegister)[CurrentIndex] == nullptr)
//				delete (*BlockIDRegister)[CurrentIndex];
//
//		BlockIDRegister->Empty();
//		delete BlockIDRegister;
//	}
//}
