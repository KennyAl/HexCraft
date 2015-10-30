// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FChunk.h"


/** Struct holding all data you need to create a mesh */
struct sMeshData
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
};


/**
 * Factory class for generating meshdate out of the data from a given chunk
 */
class HEXCRAFT_API FMeshFactory
{
public:

	/** Constructor */
	FMeshFactory();

	/** Destructor */
	~FMeshFactory();

	/** Returns a smart pointer to the generated data */
	static const TSharedPtr<sMeshData> BuildMeshFromChunkA(FChunk& Chunk);

	/** Returns a smart pointer to the generated data */
	static const TSharedPtr<sMeshData> BuildMeshFromChunkB(FChunk& Chunk);

private:
	/** The internal representation of a block 
	* 
	* Vert order:
	* [0] x   | y   | z
	* [1] x   | y+1 | z
	* [2] x+1 | y+1 | z
	* [3] x+1 | y   | z
	* [4] x   | y   | z+1
	* [5] x   | y+1 | z+1
	* [6] x+1 | y+1 | z+1
	* [7] x+1 | y   | z+1
	* 
	*/
	struct sBlock
	{
		/** The locations of the vertecies, sorted as described above */
		FVector Vert[8];

		/** The visibility of the 6 sides */
		bool Top;
		bool Bottom;
		bool Front;
		bool Back;
		bool LeftSide;
		bool RightSide;
	};

};
