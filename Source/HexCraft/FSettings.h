// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * Class holding all settings that were read from the .set file at startup
 */
class HEXCRAFT_API FSettings
{
public:
	/* Constructor **/
	FSettings();
	
	/** Constructs a settings object from a .set file at the given path.
	* When the path is not valid or empty, the fallback routine DefaultSettings will be called
	*/
	void LoadSettings();

	// Chunk settings
	int32 ChunkSizeX;
	int32 ChunkSizeY;
	int32 ChunkSizeZ;
	int32 NumChunkSections;
	int32 ChunkSectionHeight;
	float BlockSize;

	/** Sets all settings to their hardcoded default values */
	void DefaultSettings();

private:

	/** Whether the settings were loaded correctly */
	bool Loaded;

};
