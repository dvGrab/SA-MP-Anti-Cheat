#include "Detection.h"

#define CLEO_PATTERN "\x68\x00\x00\x00\x00\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x33\xC0\xA3\x00\x00\x00\x00\xA3\x00\x00\x00\x00\x83\xC4\x0C\xC7\x45\x00\x00\x00\x00\x00"
#define CLEO_MASK "x????x????x????xxx????x????xxxxx?????"

void CDetection::Routine(void)
{
	if (MemoryEditor())
		Socket.Send("WINDOWDT Memory Editor");

	ASICheck();
}

bool CDetection::MemoryEditor(void)
{
	HWND Window;

	Window = FindWindow("Window", 0);
	Window = FindWindowEx(Window, NULL, "Window", NULL);
	Window = FindWindowEx(Window, NULL, "Button", "Memory Scan Options");

	if (Window)
		return true;
	else
		return false;
}

bool CDetection::ASICheck(void)
{
	modules_struct Module;
	MD5 Checksum;
	Module.Handle = GetCurrentProcess();

	int Count = 0;
	char Temp[256];

	if (EnumProcessModules(Module.Handle, Module.Files, sizeof(Module.Files), &Module.Size))
	{
		for (int i = 0; i < Module.Size / sizeof(HMODULE); i++)
		{
			if (GetModuleFileNameEx(Module.Handle, Module.Files[i], Module.PathName, sizeof(Module.PathName)))
			{
				if (GetModuleBaseName(Module.Handle, Module.Files[i], Module.Name, sizeof(Module.Name)))
				{
					if (!strstr(Module.Name, ".asi"))
						continue;
				
					if(strcmp(ASI_FILES[i], Module.Name))
					{
						sprintf_s(ASI_FILES[i], Module.Name);
					
						std::ifstream TargetFile;
						TargetFile.open(Module.PathName, std::ios::binary);
						TargetFile.seekg(0, std::ios_base::end);
						float Size = TargetFile.tellg() / 1000;
						TargetFile.close(); 

						for (int j = 0; j < strlen(Module.Name); j++)
						{
							if (Module.Name[j] == ' ')
								Module.Name[j] = '_';
						}

						char Temp[256];
						sprintf_s(Temp, "ASIFILE %s %s %0.f", Checksum.digestFile(Module.PathName), Module.Name, Size);
						Socket.Send(Temp);
					}
				}
			}
		}
	}

	return false;
}