#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

bool IsOnlyInstance(LPCTSTR gameTitle);
bool CheckStorage(const DWORDLONG diskSpaceNeeded);
bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
DWORD ReadCPUSpeed();
bool initEngine();
