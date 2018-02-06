#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool IsOnlyInstance(LPCTSTR gameTitle) {
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS) {
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd) {
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;
}

bool CheckStorage(const DWORDLONG diskSpaceNeeded) {
	// Check for enough free disk space on the current disk.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const neededClusters = diskSpaceNeeded /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters) {
		// if you get here you don’t have enough disk space!
		//GCC_ERROR("CheckStorage Failure : Not enough physical storage.");
		cout << "CheckMemory Failure : Not enough physical storage." << endl;
		return false;
	}
	return true;
}

bool CheckMemory(const DWORDLONG physicalRAMNeeded, const
	DWORDLONG virtualRAMNeeded) {
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	if (status.ullTotalPhys < physicalRAMNeeded) {
		/* you don’t have enough physical memory. Tell the
		player to go get a real computer and give this one to
		his mother. */
		//GCC_ERROR("CheckMemory Failure : Not enough physical memory."); return false;
		cout << "CheckMemory Failure : Not enough physical memory." << endl;
	}
	// Check for enough free memory.
	if (status.ullAvailVirtual < virtualRAMNeeded) {
		// you don’t have enough virtual memory available.
		// Tell the player to shut down the copy of Visual 
		//Studio running in the background.
		//GCC_ERROR("CheckMemory Failure : Not enough virtual memory.");
		cout << "CheckMemory Failure : Not enough virtual memory." << endl;
		return false;
	}

	cout << "Available Physical Mem: " << status.ullTotalPhys / 1048576 << "MB" << endl;
	cout << "Available Virtual Mem: " << status.ullTotalVirtual / 1048576 << "MB" << endl;

	/*char *buff = GCC_NEW char[virtualRAMNeeded];
	if (buff)
	delete[] buff;
	else {
	// even though there is enough memory, it isn’t
	//available in one block, which can be critical for games
	//that manage their own memory
	//GCC_ERROR("CheckMemory Failure : Not enough contiguous memory.");
	return false;
	}*/
}

DWORD ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, reinterpret_cast<LPCTSTR>("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueEx(hKey, reinterpret_cast<LPCTSTR>("~MHz"), NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}
	return dwMHz;
}

bool Init() {
	cout << "Hello World!" << endl;

	string name = "GameTest";
	LPCTSTR newName = name.c_str();

	bool onlyInstance = IsOnlyInstance(newName);

	if (!onlyInstance) {
		system("PAUSE");
		return 0;
	}
	else {
		cout << "This is the only instance!" << endl;
	}

	const DWORDLONG storageSize = 300;

	bool storageCheck = CheckStorage(storageSize);

	if (!storageCheck) {
		system("PAUSE");
		return 0;
	}
	else {
		cout << "Storage is good!" << endl;
	}

	const DWORDLONG virtualMem = 5000;
	const DWORDLONG RAM = 1000;

	bool memCheck = CheckMemory(RAM, virtualMem);

	if (!memCheck) {
		system("PAUSE");
		return 0;
	}
	else {
		cout << "RAM and virtual memory is good!" << endl;
	}

	cout << "CPU Speed: " << ReadCPUSpeed() << "~MHz" << endl;
}