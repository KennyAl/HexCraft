// Fill out your copyright notice in the Description page of Project Settings.

#include "HexCraft.h"
#include "FMeshFactory.h"

FMeshFactory::FMeshFactory()
{
}

FMeshFactory::~FMeshFactory()
{
}


const TSharedPtr<sMeshData> FMeshFactory::BuildMeshFromChunkA(FChunk& Chunk)
{
	// Create a new mesh dataset
	TSharedPtr<sMeshData> MeshData(new sMeshData);
	int32 callCount = 0;
	for (uint32 Section = 0; Section < 1/*Chunk.GetNumSections()*/; Section++)
	{
		// Used for caching the section we need to look in in order to check blocks for visibility
		FChunkSection* TargetSection = Chunk.GetSection(Section);

		// Loop through every block in this section and create a mesh on all sides that are visible
		for (int32 Z = 0; Z < 16; Z++)
			for (int32 Y = 0; Y < 16; Y++)
				for (int32 X = 0; X < 16; X++)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Call Nr %d"), callCount);
					//callCount ++;
					// Goto the next block, when the current one is not visible
					if (TargetSection->GetBlockIDAt(X, Y, Z) == 0)
					{
						//callCount++;//2047
						break;
					}

					// The block we currently looking at
					sBlock Block;

					// Check the sides for visibility

					// Top
					if (Z == 15 && Section < Chunk.GetNumSections() - 1)
						Block.Top = Chunk.GetSection(Section + 1)->GetBlockIDAt(X, Y, 0) == 0 ? true : false;
					else if (Z == 15 && Section == Chunk.GetNumSections() - 1)
						Block.Top = true;
					else
						Block.Top = TargetSection->GetBlockIDAt(X, Y, Z + 1) == 0 ? true : false;

					// Bottom
					if (Z == 0 && Section != 0)
						Block.Bottom = Chunk.GetSection(Section - 1)->GetBlockIDAt(X, Y, 15) == 0 ? true : false;
					else if (Z == 0 && Section == 0)
						Block.Bottom = false;
					else
						Block.Bottom = TargetSection->GetBlockIDAt(X, Y, Z - 1) == 0 ? true : false;

					// Front
					if (X == 15)
						Block.Front = true;
					else
						Block.Front = TargetSection->GetBlockIDAt(X + 1, Y, Z) == 0 ? true : false;

					// Back
					if (X == 0)
						Block.Back = true;
					else
						Block.Back = TargetSection->GetBlockIDAt(X - 1, Y, Z) == 0 ? true : false;

					// Right side
					if (Y == 15)
						Block.RightSide = true;
					else
						Block.RightSide = TargetSection->GetBlockIDAt(X, Y + 1, Z) == 0 ? true : false;

					// Left side
					if (Y == 0)
						Block.LeftSide = true;
					else
						Block.LeftSide = TargetSection->GetBlockIDAt(X, Y - 1, Z) == 0 ? true : false;

					// The first vertex we added for this side
					uint32 FirstVert = 0;

					/*Block.Top		= true;
					Block.Bottom	= true;
					Block.Front		= true;
					Block.Back		= true;
					Block.LeftSide	= true;
					Block.RightSide = true;*/

					// If all sides are not visible (the block is surrounded by other blocks) don't draw anything
					if (!Block.Top && !Block.Bottom && !Block.Front && !Block.Back && !Block.RightSide && !Block.LeftSide)
						break;

					// Calculate the world positions for all verts
					Block.Vert[0] = FVector(X * 25.0f, Y * 25.0f, Z * 25.0f + (Section * 25.0f * 16));
					Block.Vert[1] = FVector(X * 25.0f, (Y + 1) * 25.0f, Z * 25.0f + (Section * 25.0f * 16));
					Block.Vert[2] = FVector((X + 1) * 25.0f, (Y + 1) * 25.0f, Z * 25.0f + (Section * 25.0f * 16));
					Block.Vert[3] = FVector((X + 1) * 25.0f, Y * 25.0f, Z * 25.0f + (Section * 25.0f * 16));

					Block.Vert[4] = FVector(X * 25.0f, Y * 25.0f, (Z + 1) * 25.0f + (Section * 25.0f * 16));
					Block.Vert[5] = FVector(X * 25.0f, (Y + 1) *25.0f, (Z + 1) * 25.0f + (Section * 25.0f * 16));
					Block.Vert[6] = FVector((X + 1) * 25.0f, (Y + 1) * 25.0f, (Z + 1) * 25.0f + (Section * 25.0f * 16));
					Block.Vert[7] = FVector((X + 1) * 25.0f, Y * 25.0f, (Z + 1) * 25.0f + (Section * 25.0f * 16));

					if (Block.Top)
					{
						FirstVert = MeshData->Vertices.Add(Block.Vert[4]);
						MeshData->Vertices.Add(Block.Vert[5]);
						MeshData->Vertices.Add(Block.Vert[6]);
						MeshData->Vertices.Add(Block.Vert[7]);

						// First Triangle
						MeshData->Triangles.Add(FirstVert + 0);
						MeshData->Triangles.Add(FirstVert + 1);
						MeshData->Triangles.Add(FirstVert + 2);

						// Second Triangle
						MeshData->Triangles.Add(FirstVert + 0);
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 3);

						for (int32 Normal = 0; Normal < 4; Normal++)
							MeshData->Normals.Add(FVector::UpVector);

						for (int32 UV = 0; UV < 4; UV++)
							MeshData->UVs.Add(FVector2D(0, 0));
					}

					if (Block.Bottom)
					{
						FirstVert = MeshData->Vertices.Add(Block.Vert[0]);
						MeshData->Vertices.Add(Block.Vert[1]);
						MeshData->Vertices.Add(Block.Vert[2]);
						MeshData->Vertices.Add(Block.Vert[3]);

						// First Triangle
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 1);
						MeshData->Triangles.Add(FirstVert + 0);

						// Second Triangle
						MeshData->Triangles.Add(FirstVert + 3);
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 0);

						for (int32 Normal = 0; Normal < 4; Normal++)
							MeshData->Normals.Add(FVector::UpVector * -1.0f);

						for (int32 UV = 0; UV < 4; UV++)
							MeshData->UVs.Add(FVector2D(0, 0));
					}

					if (Block.Front)
					{
						FirstVert = MeshData->Vertices.Add(Block.Vert[2]);
						MeshData->Vertices.Add(Block.Vert[3]);
						MeshData->Vertices.Add(Block.Vert[6]);
						MeshData->Vertices.Add(Block.Vert[7]);

						// First Triangle
						MeshData->Triangles.Add(FirstVert + 3);
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 1);

						// Second Triangle
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 0);
						MeshData->Triangles.Add(FirstVert + 1);

						for (int32 Normal = 0; Normal < 4; Normal++)
							MeshData->Normals.Add(FVector::ForwardVector);

						for (int32 UV = 0; UV < 4; UV++)
							MeshData->UVs.Add(FVector2D(0, 0));
					}

					if (Block.Back)
					{
						FirstVert = MeshData->Vertices.Add(Block.Vert[0]);
						MeshData->Vertices.Add(Block.Vert[1]);
						MeshData->Vertices.Add(Block.Vert[4]);
						MeshData->Vertices.Add(Block.Vert[5]);

						// First Triangle
						MeshData->Triangles.Add(FirstVert + 3);
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 1);

						// Second Triangle
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 0);
						MeshData->Triangles.Add(FirstVert + 1);

						for (int32 Normal = 0; Normal < 4; Normal++)
							MeshData->Normals.Add(FVector::ForwardVector * -1.0f);

						for (int32 UV = 0; UV < 4; UV++)
							MeshData->UVs.Add(FVector2D(0, 0));
					}

					if (Block.RightSide)
					{
						FirstVert = MeshData->Vertices.Add(Block.Vert[1]);
						MeshData->Vertices.Add(Block.Vert[2]);
						MeshData->Vertices.Add(Block.Vert[5]);
						MeshData->Vertices.Add(Block.Vert[6]);

						// First Triangle
						MeshData->Triangles.Add(FirstVert + 3);
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 1);

						// Second Triangle
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 0);
						MeshData->Triangles.Add(FirstVert + 1);

						for (int32 Normal = 0; Normal < 4; Normal++)
							MeshData->Normals.Add(FVector::RightVector);

						for (int32 UV = 0; UV < 4; UV++)
							MeshData->UVs.Add(FVector2D(0, 0));
					}

					if (Block.LeftSide)
					{
						FirstVert = MeshData->Vertices.Add(Block.Vert[0]);
						MeshData->Vertices.Add(Block.Vert[3]);
						MeshData->Vertices.Add(Block.Vert[4]);
						MeshData->Vertices.Add(Block.Vert[7]);

						// First Triangle
						MeshData->Triangles.Add(FirstVert + 1);
						MeshData->Triangles.Add(FirstVert + 2);
						MeshData->Triangles.Add(FirstVert + 3);

						// Second Triangle
						MeshData->Triangles.Add(FirstVert + 1);
						MeshData->Triangles.Add(FirstVert + 0);
						MeshData->Triangles.Add(FirstVert + 2);

						for (int32 Normal = 0; Normal < 4; Normal++)
							MeshData->Normals.Add(FVector::RightVector * -1.0f);

						for (int32 UV = 0; UV < 4; UV++)
							MeshData->UVs.Add(FVector2D(0, 0));
					}

				}
	}
	return MeshData;
}


const TSharedPtr<sMeshData> FMeshFactory::BuildMeshFromChunkB(FChunk& Chunk)
{
	// Create a new mesh dataset
	TSharedPtr<sMeshData> MeshData(new sMeshData);
	
	// Loop through every block in this section and create a mesh on all sides that are visible
	for (int32 Z = 0; Z < 128; Z++)
		for (int32 Y = 0; Y < 16; Y++)
			for (int32 X = 0; X < 16; X++)
			{
				// Goto the next block, when the current one is not visible
				if (Chunk.GetBlockIDAt(X, Y, Z) == 0)
					continue;

				// The block we currently looking at
				sBlock Block;

				// Check the sides for visibility

				// Top
				if (Z == 127)
					Block.Top = true;
				else
					Block.Top = Chunk.GetBlockIDAt(X, Y, Z + 1) == 0 ? true : false;

				// Bottom
				if (Z == 0)
					Block.Bottom = false;
				else
					Block.Bottom = Chunk.GetBlockIDAt(X, Y, Z - 1) == 0 ? true : false;

				// Front
				if (X == 15)
					Block.Front = true;
				else
					Block.Front = Chunk.GetBlockIDAt(X + 1, Y, Z) == 0 ? true : false;

				// Back
				if (X == 0)
					Block.Back = true;
				else
					Block.Back = Chunk.GetBlockIDAt(X - 1, Y, Z) == 0 ? true : false;

				// Right side
				if (Y == 15)
					Block.RightSide = true;
				else
					Block.RightSide = Chunk.GetBlockIDAt(X, Y + 1, Z) == 0 ? true : false;

				// Left side
				if (Y == 0)
					Block.LeftSide = true;
				else
					Block.LeftSide = Chunk.GetBlockIDAt(X, Y - 1, Z) == 0 ? true : false;

				/*Block.Top		= true;
				Block.Bottom	= true;
				Block.Front		= true;
				Block.Back		= true;
				Block.LeftSide	= true;
				Block.RightSide = true;*/
				
				// If all sides are not visible (the block is surrounded by other blocks) don't draw anything
				//if (!Block.Top && !Block.Bottom && !Block.Front && !Block.Back && !Block.RightSide && !Block.LeftSide)
					//break;
				//if ((Block.Top + Block.Bottom + Block.Front + Block.Back + Block.RightSide + Block.LeftSide) == 0)
					//break;

				// The desired dimensions of the blocks
				float BlockDim = 50.0f;

				// Calculate the world positions for all verts
				Block.Vert[0] = FVector(X * BlockDim, Y * BlockDim, Z * BlockDim);
				Block.Vert[1] = FVector(X * BlockDim, (Y + 1) * BlockDim, Z * BlockDim);
				Block.Vert[2] = FVector((X + 1) * BlockDim, (Y + 1) * BlockDim, Z * BlockDim);
				Block.Vert[3] = FVector((X + 1) * BlockDim, Y * BlockDim, Z * BlockDim);

				Block.Vert[4] = FVector(X * BlockDim, Y * BlockDim, (Z + 1) * BlockDim);
				Block.Vert[5] = FVector(X * BlockDim, (Y + 1) *BlockDim, (Z + 1) * BlockDim);
				Block.Vert[6] = FVector((X + 1) * BlockDim, (Y + 1) * BlockDim, (Z + 1) * BlockDim);
				Block.Vert[7] = FVector((X + 1) * BlockDim, Y * BlockDim, (Z + 1) * BlockDim);

				// The first vertex we added for this side
				uint32 FirstVert = 0;

				if (Block.Top)
				{
					FirstVert = MeshData->Vertices.Add(Block.Vert[4]);
					MeshData->Vertices.Add(Block.Vert[5]);
					MeshData->Vertices.Add(Block.Vert[6]);
					MeshData->Vertices.Add(Block.Vert[7]);

					// First Triangle
					MeshData->Triangles.Add(FirstVert + 0);
					MeshData->Triangles.Add(FirstVert + 1);
					MeshData->Triangles.Add(FirstVert + 2);

					// Second Triangle
					MeshData->Triangles.Add(FirstVert + 0);
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 3);

					for (int32 Normal = 0; Normal < 4; Normal++)
						MeshData->Normals.Add(FVector::UpVector);

					for (int32 UV = 0; UV < 4; UV++)
						MeshData->UVs.Add(FVector2D(0, 0));
				}

				if (Block.Bottom)
				{
					FirstVert = MeshData->Vertices.Add(Block.Vert[0]);
					MeshData->Vertices.Add(Block.Vert[1]);
					MeshData->Vertices.Add(Block.Vert[2]);
					MeshData->Vertices.Add(Block.Vert[3]);

					// First Triangle
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 1);
					MeshData->Triangles.Add(FirstVert + 0);

					// Second Triangle
					MeshData->Triangles.Add(FirstVert + 3);
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 0);

					for (int32 Normal = 0; Normal < 4; Normal++)
						MeshData->Normals.Add(FVector::UpVector * -1.0f);

					for (int32 UV = 0; UV < 4; UV++)
						MeshData->UVs.Add(FVector2D(0, 0));
				}

				if (Block.Front)
				{
					FirstVert = MeshData->Vertices.Add(Block.Vert[2]);
					MeshData->Vertices.Add(Block.Vert[3]);
					MeshData->Vertices.Add(Block.Vert[6]);
					MeshData->Vertices.Add(Block.Vert[7]);

					// First Triangle
					MeshData->Triangles.Add(FirstVert + 3);
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 1);

					// Second Triangle
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 0);
					MeshData->Triangles.Add(FirstVert + 1);

					for (int32 Normal = 0; Normal < 4; Normal++)
						MeshData->Normals.Add(FVector::ForwardVector);

					for (int32 UV = 0; UV < 4; UV++)
						MeshData->UVs.Add(FVector2D(0, 0));
				}

				if (Block.Back)
				{
					FirstVert = MeshData->Vertices.Add(Block.Vert[0]);
					MeshData->Vertices.Add(Block.Vert[1]);
					MeshData->Vertices.Add(Block.Vert[4]);
					MeshData->Vertices.Add(Block.Vert[5]);

					// First Triangle
					MeshData->Triangles.Add(FirstVert + 3);
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 1);

					// Second Triangle
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 0);
					MeshData->Triangles.Add(FirstVert + 1);

					for (int32 Normal = 0; Normal < 4; Normal++)
						MeshData->Normals.Add(FVector::ForwardVector * -1.0f);

					for (int32 UV = 0; UV < 4; UV++)
						MeshData->UVs.Add(FVector2D(0, 0));
				}

				if (Block.RightSide)
				{
					FirstVert = MeshData->Vertices.Add(Block.Vert[1]);
					MeshData->Vertices.Add(Block.Vert[2]);
					MeshData->Vertices.Add(Block.Vert[5]);
					MeshData->Vertices.Add(Block.Vert[6]);

					// First Triangle
					MeshData->Triangles.Add(FirstVert + 3);
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 1);

					// Second Triangle
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 0);
					MeshData->Triangles.Add(FirstVert + 1);

					for (int32 Normal = 0; Normal < 4; Normal++)
						MeshData->Normals.Add(FVector::RightVector);

					for (int32 UV = 0; UV < 4; UV++)
						MeshData->UVs.Add(FVector2D(0, 0));
				}

				if (Block.LeftSide)
				{
					FirstVert = MeshData->Vertices.Add(Block.Vert[0]);
					MeshData->Vertices.Add(Block.Vert[3]);
					MeshData->Vertices.Add(Block.Vert[4]);
					MeshData->Vertices.Add(Block.Vert[7]);

					// First Triangle
					MeshData->Triangles.Add(FirstVert + 1);
					MeshData->Triangles.Add(FirstVert + 2);
					MeshData->Triangles.Add(FirstVert + 3);

					// Second Triangle
					MeshData->Triangles.Add(FirstVert + 1);
					MeshData->Triangles.Add(FirstVert + 0);
					MeshData->Triangles.Add(FirstVert + 2);

					for (int32 Normal = 0; Normal < 4; Normal++)
						MeshData->Normals.Add(FVector::RightVector * -1.0f);

					for (int32 UV = 0; UV < 4; UV++)
						MeshData->UVs.Add(FVector2D(0, 0));
				}

			}
	
	return MeshData;
}