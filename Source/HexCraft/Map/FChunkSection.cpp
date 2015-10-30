// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FChunkSection.h"

FChunkSection::FChunkSection()
{
	SetIsCleared(1);
	for (int32 X = 0; X < 16; X++)
		for (int32 Y = 0; Y < 16; Y++)
			for (int32 Z = 0; Z < 16; Z++)
				Block[X][Y][Z] = 0;

	//InitializeSection();
}

FChunkSection::~FChunkSection()
{
	ClearSection();
}

const uint16 FChunkSection::GetBlockIDAt(uint8 X, uint8 Y, uint8 Z)
{

	//if (GetIsCleared() == 1)
	//	return 0;

	if (X < 16 && Y < 16 && Z < 16)
		return Block[X][Y][Z];
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FChunkSection::GetBlockIdAt() : Out of bounds !"));
		return 0;
	}
		
	//	return Blocks[X][Y][Z];
	//else
	//	return Blocks[0][0][0];
	
}

void FChunkSection::SetBlockIDAt(uint8 X, uint8 Y, uint8 Z, uint16 ID)
{
	if (X < 16 && Y < 16 && Z < 16)
		Block[X][Y][Z] = ID;
	else
		UE_LOG(LogTemp, Warning, TEXT("FChunkSection::SetBlockIdAt() : Out of bounds !"));
		//Blocks[X][Y][Z] = ID;
}

void FChunkSection::InitializeSection()
{
	// If there is already an array of block IDs skip the following step
	if (GetIsCleared() == 0)
		return;

	// Dynamically allocate a 3dim array to store all the block IDs of this section
	// THIS NEEDS TO BE MANUALLY DELETED WITHIN THE DESTRUCTOR !!!
	Blocks = new uint16**[16];

	for (int8 X = 0; X < 16; X++)
	{
		Blocks[X] = new uint16*[16];
		for (int8 Y = 0; Y < 16; Y++)
		{
			Blocks[X][Y] = new uint16[16];
			for (int8 Z = 0; Z < 16; Z++)
				Blocks[X][Y][Z] = 0;
		}
	}

	// Update the corresponding flag
	SetIsCleared(0);
}

void FChunkSection::ClearSection()
{
	// Do nothing if Blocks is already null
	if (GetIsCleared() == 1)
		return;

	for (uint8 X = 0; X < 16; X++)
	{
		for (uint8 Y = 0; Y < 16; Y++)
			delete[] Blocks[X][Y];

		delete[] Blocks[X];
	}

	delete[] Blocks;

	SetIsCleared(1);
}


const uint8 FChunkSection::GetIsAir()
{
	return Flags & static_cast<uint8>(ESectionFlags::IsAir) ? 1 : 0;
}

const uint8 FChunkSection::GetIsNotSurface()
{
	return Flags & static_cast<uint8>(ESectionFlags::IsNotSurface) ? 1 : 0;
}

const uint8 FChunkSection::GetIsCleared()
{
	return Flags & static_cast<uint8>(ESectionFlags::IsCleared) ? 1 : 0;
}

void FChunkSection::SetIsAir(uint8 IsAir)
{
	if (IsAir == 0 && GetIsAir() == 1)
	{
		Flags &= ~uint8(ESectionFlags::IsAir);
	}
	else if (IsAir > 0 && GetIsAir() == 0)
	{
		Flags |= uint8(ESectionFlags::IsAir);
	}
}

void FChunkSection::SetIsNotSurface(uint8 IsNotSurface)
{
	if (IsNotSurface == 0 && GetIsNotSurface() == 1)
	{
		Flags &= ~uint8(ESectionFlags::IsNotSurface);
	}
	else if (IsNotSurface > 0 && GetIsNotSurface() == 0)
	{
		Flags |= uint8(ESectionFlags::IsNotSurface);
	}
}

void FChunkSection::SetIsCleared(uint8 IsCleared)
{
	if (IsCleared == 0 && GetIsCleared() == 1)
	{
		Flags &= ~uint8(ESectionFlags::IsCleared);
	}
	else if (IsCleared > 0 && GetIsCleared() == 0)
	{
		Flags |= uint8(ESectionFlags::IsCleared);
	}
}
