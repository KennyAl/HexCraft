// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FBlockBase.h"

FBlockBase::FBlockBase(uint8 X, uint8 Y, uint8 Z)
{
	Coords = { X, Y, Z };
}

FBlockBase::~FBlockBase()
{
}

//void FBlockBase::BlockUpdate()
//{
//	// Call BlockUpdate() on all dynamic neighbors
//	for (int8 X = -1; X < 1; X++)
//	{
//		for (int8 Y = -1; Y < 1; Y++)
//		{
//			for (int8 Z = -1; Z < 1; Z++)
//			{
//				
//			}
//		}
//	}
//
//	UE_LOG(Editor, Warning, TEXT("Base"));
//}

const uint8 FBlockBase::GetIsDestructible()
{
	return Flags & static_cast<uint8>(EBlockFlags::IsDestructible) ? 1 : 0;
}

const uint8 FBlockBase::GetIsStatic()
{
	return Flags & static_cast<uint8>(EBlockFlags::IsStatic) ? 1 : 0;
}

void FBlockBase::SetIsDestructible(uint8 IsDestructible)
{
	if (IsDestructible == 0 && GetIsDestructible() == 1)
	{
		Flags &= ~IsDestructible;
	}
	else if ((IsDestructible > 1 || IsDestructible == 1) && GetIsDestructible() == 0)
	{
		Flags |= IsDestructible;
	}
}

void FBlockBase::SetIsStatic(uint8 IsStatic)
{
	if (IsStatic == 0 && GetIsStatic() == 1)
	{
		Flags &= ~IsStatic;
	}
	else if ((IsStatic > 1 || IsStatic == 1) && GetIsStatic() == 0)
	{
		Flags |= IsStatic;
	}
}
