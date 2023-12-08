#pragma once
#include "Defines.h"
#include "SaveFileDirectory.h"
#include "Vector2.h"
#include <string>
#include <vector>

class SaveData
{
public:
	struct Data 
	{
		double m_playTime = 0.0;
		size_t m_saves = 0;
		size_t m_stage = 0;
		char m_pPlayerName[80] = "";
		char m_pSpriteName[80] = "";
		Vector2<int> m_position = { 0,0 };
		int m_health = 0;

	};

private:
	// save data folder relative location.
	static constexpr char s_kDirectory[] = _SAVE_FOLDER_MAIN;

	// Save Data file name including extension.
	//const char* m_pFileName;

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
	bool Save(const char* folderName, const char* fileName);

	// Attempts to load the data to disk.
	// Returns true if successful.
	bool Load(const char* folderName = nullptr, const char* fileName = nullptr);

	// Get whether the save data has been loaded this session.
	bool GetIsLoaded() { return m_isLoaded; }

	// Get a reference to the actual save data.
	Data& GetData() { return m_data; }
};

