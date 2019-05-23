#include "FileManager.h"
#include <iostream>
FileManager::FileManager()
{
	std::vector<std::string> lol;
	lol = GetFileContent("save");
	for (int i = 0; i < lol.size(); i++)
	{
		std::cout << lol[i] << std::endl;
	}
	WriteToFile(lol, "siema");
}

FileManager::~FileManager()
{

}

std::vector<std::string> FileManager::GetFileContent(std::string filename)
{
	std::string ffilename = "Saves/";
	ffilename.append(filename);
	std::ifstream ifs;

	std::cout << ffilename;

	ifs = std::ifstream(ffilename, std::ifstream::in);
	std::string line;
	std::vector<std::string> content;

	while (std::getline(ifs, line))
	{
		content.push_back(line);
	}

	ifs.close();

	if (content.size() == 0)
	{
		content.push_back("file-doesnt-exist"); //flag to the save interpreter
	}

	return content;

}

void FileManager::WriteToFile(std::vector<std::string> content, std::string filename)
{
	std::string ffilename = "Saves/";
	ffilename.append(filename);
	std::ofstream ofs;

	ofs = std::ofstream(ffilename, std::ifstream::out);

	if (ofs.is_open())
	{
		for (int i = 0; i < content.size(); i++)
		{
			ofs << content[i] << std::endl;
		}
	}

	ofs.close();

}