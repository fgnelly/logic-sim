#include <string>
#include "ProgramManager.h"

int main()
{
	ProgramManager* program = ProgramManager::Instance();

	program->Run();

	ProgramManager::Release();
	program = NULL;

	return 0;
}