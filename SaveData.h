#pragma once
#include "Defines.h"
#include "Vector2.h"
#include <vector>

class SaveData
{
public:
	struct Data
	{
		Vector2<int> m_playerPosition;
		std::vector<Vector2<int>> m_enemyPositions;
		std::vector<const char*> m_enemySprite;
	};

private:
	// save data folder relative location.
	static constexpr char s_kDirectory[] = SAVE_FOLDER;

	// Save Data file name including extension.
	static constexpr char s_kFileName[] = SAVE_FILE;

	// buildFolder\saves\savedata.save

	// whether this save data has been loaded this session.
	bool m_isLoaded;

	// The actual save data that will read/written.
	Data m_data;

public:
	SaveData();
	~SaveData();

	// Attempts to save the data to disk.
	// Returns true if successful.
	bool Save();

	// Attempts to load the data to disk.
	// Returns true if successful.
	bool Load();

	// Get whether the save data has been loaded this session.
	bool GetIsLoaded() { return m_isLoaded; }

	// Get a reference to the actual save data.
	Data& GetData() { return m_data; }
};

