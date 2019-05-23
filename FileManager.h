#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H
#include <vector>
#include <fstream>
#include <sstream>

class FileManager {

private:


public:

	std::vector<std::string> GetFileContent(std::string filename);

	void WriteToFile(std::vector<std::string> content, std::string filename);

	FileManager();
	~FileManager();

};

#endif