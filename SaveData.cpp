#include "SaveData.h"
#include <direct.h>
#include <fstream>
#include <iostream>

/*------------------
	CONSTRUCTOR
------------------*/
SaveData::SaveData()
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
bool SaveData::Save()
{
	// Make sure directory exists.
	_mkdir(s_kDirectory);

	// Combine directory and filenames.
	std::string path = s_kDirectory + std::string(s_kFileName);

	// Open the file
	std::ofstream file;
	file.open(path, std::ios::out);	// Todo: change to binary mode.

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
bool SaveData::Load()
{
	// Combine directory and filenames.
	std::string path = s_kDirectory + std::string(s_kFileName);

	// Open the file
	std::ifstream file;
	file.open(path, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "[SaveData] Failed to open: " << path << std::endl;
		return false;
	}
	
	// Read from the file.
	file.read((char*)&m_data, sizeof(m_data));

	// Close the file.
	file.close();

	// Update m_isLoaded.
	m_isLoaded = true;

	return true;
}
