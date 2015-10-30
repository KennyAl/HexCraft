// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FChunk.h"

FChunk::FChunk()
{
	for (int32 NumSections = 0; NumSections < 8; NumSections++)
		Sections.Add(new FChunkSection);
}

FChunk::~FChunk()
{
}

FChunkSection* FChunk::GetSection(uint32 Index)
{
	if (Sections.IsValidIndex(Index))
		return Sections[Index];
	else
		return nullptr;
}

uint32 FChunk::GetNumSections()
{
	return Sections.Num();
}

uint8 FChunk::GetBlockIDAt(uint8 X, uint8 Y, uint8 Z)
{
	if (Z < 128)
	{
		// Find out which section contains the requested block
		uint32 Section = FMath::FloorToInt(Z / 16.0f);

		return GetSection(Section)->GetBlockIDAt(X, Y, Z % 16);
	}
	else
		return GetSection(0)->GetBlockIDAt(0, 0, 0);
}

void FChunk::SetBlockIDAt(uint8 X, uint8 Y, uint8 Z, uint16 ID)
{
	if (Z < 128)
	{
		// Find out which section contains the requested block
		uint32 Section = FMath::FloorToInt(Z / 16.0f);

		GetSection(Section)->SetBlockIDAt(X, Y, Z % 16, ID);
	}
}
