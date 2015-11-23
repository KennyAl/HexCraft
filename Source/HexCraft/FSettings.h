// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/** Global pointer to a settings object for testing purposes */
extern const FSettings* GSettings = new FSettings();

/**
 * Class holding all settings that were read from the .set file at startup
 */
class HEXCRAFT_API FSettings
{
public:
	/* Constructor **/
	FSettings();
	
	/** Constructs a settings object from the HexSettings.ini file (\Saved\Config\Windows)
	* When the file does not exist, the fallback routine DefaultSettings() will be called
	*/
	void LoadSettings();

	// Chunk settings
	int32 ChunkSizeX;
	int32 ChunkSizeY;
	int32 ChunkSizeZ;
	int32 NumChunkSections;
	float BlockSize;

	/** Sets all settings to their hardcoded default values */
	void DefaultSettings();

	//
	// Getters & Setters
	//

	// Chunk settings (these are read only, since modifying them after a world has already been setup would break the whole game)

	/** Returns the chunk size in x direction (in blocks) */
	inline int32 GetChunkSizeX() { return ChunkSizeX; }

	/** Returns the chunk size in y direction (in blocks) */
	inline int32 GetChunkSizeY() { return ChunkSizeY; }

	/** Returns the chunk size in z direction (in blocks) */
	inline int32 GetChunkSizeZ() { return ChunkSizeZ; }

	/** Returns the number of sections per chunk */
	inline int32 GetNumChunkSections() { return NumChunkSections; }

	/** Returns the chunk size in x direction (in blocks) */
	inline float GetBlockSize() { return BlockSize; }

private:

	/** Whether the settings were loaded correctly */
	bool Loaded;

};
