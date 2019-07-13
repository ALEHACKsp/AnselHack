#include "SigScan.h"
#define AddOffset(name, pattern, type) static DWORD64 Get_## name (){static DWORD64 name = NULL; if (name != NULL) return name; return name=(DWORD64)PatternScanner::FindPattern({pattern, type});} 

class StaticOffsets {
public:
	AddOffset(OFFSET_ANSELSETTINGS, "48 8B 05 [?? ?? ?? ?? 8B 88 88 00 00 00 89 4B 10 F3 0F 11 82 58 01 00 00", PatternType::RelativePointer)
};