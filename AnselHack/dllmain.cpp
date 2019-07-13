#include "StaticOffsets.h"

// check if a pointer is valid
bool IsValidPtr(void* ptr) {
	return !IsBadReadPtr(ptr, sizeof(LPVOID));
}

// The game's AnselSettings class
class AnselSettings {
public:
	char pad_000[0x90];
	float CameraMaxWanderDistance;
};

DWORD WINAPI mainThread(LPVOID lpParam) {
	// Get the address from our sig scanner
	void* ppAnselSettings = (void*)StaticOffsets::Get_OFFSET_ANSELSETTINGS(); 
	// Wait to make sure the pointer is valid
	while (!IsValidPtr(ppAnselSettings)) Sleep(100);
	// Dereference
	AnselSettings* pAnselSettings = *(AnselSettings**)ppAnselSettings;
	// set the MaxWanderDistance to some other number
	pAnselSettings->CameraMaxWanderDistance = 10000000;
	// unload the module
	FreeLibraryAndExitThread((HMODULE)lpParam, 0);
}

// entry point of the mod
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	// if the mod just got attached to the game,
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		// create a thread and start executing our own code
		CreateThread(NULL, NULL, mainThread, hModule, NULL, NULL);
	}
	return TRUE;
}