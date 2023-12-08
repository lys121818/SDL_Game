#include "SaveData.h"
#include <direct.h>
#include <fstream>
#include <iostream>

/*------------------
	CONSTRUCTOR
------------------*/
SaveData::SaveData() :
	m_isLoaded(false)
{
}

/*------------------
	DESTRUCTOR
------------------*/
SaveData::~SaveData()
{
}

/*------------------------------------------
|	Attempts to save the data to disk.		|
|	Returns true if successful.				|
-------------------------------------------*/
bool SaveData::Save(const char* folderName, const char* fileName)
{
	// Make sure directory exists.
	_mkdir(s_kDirectory);

	// Combine directory and filenames.
	std::string path = s_kDirectory + std::string(folderName) + std::string(fileName);

	// Open the file
	std::ofstream file;
	file.open(path, std::ios::out| std::ios::binary);	

	if (!file.is_open())
	{
		std::cout << "[SaveData] Failed to open: " << path << std::endl;
		return false;
	}

	// Write the data
	file.write((char*) & m_data, sizeof(m_data));

	// Close the file
	file.close();

	// success
	return true;	
}

/*------------------------------------------
|	Attempts to load the data to disk.		|
|	Returns true if successful.				|
-------------------------------------------*/
bool SaveData::Load(const char* folderName, const char* fileName)
{
	// Set isloaded to defualt (false)
	m_isLoaded = false;

	// Combine directory and filenames.
	std::string filePath = s_kDirectory + std::string(folderName) + std::string(fileName);

	// default save file (new game)
	if (fileName == _SAVE_FOLDER_MAIN)
		return m_isLoaded;

	// Open the file
	std::ifstream file;
	file.open(filePath, std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "[SaveData] Failed to open: " << filePath << std::endl;
		return m_isLoaded;
	}
	
	// Read from the file.
	file.read((char*)&m_data, sizeof(m_data));

	// Close the file.
	file.close();

	// Update m_isLoaded.
	m_isLoaded = true;

	return m_isLoaded;
}
