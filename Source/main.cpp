#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include "Initiate.h"
#include <SFML/Graphics.hpp>
#include "Spaghengine.h"

using namespace std;

windowHandle* windowHandle::s_pInstance = nullptr;

int main() {
	Spaghengine::Initialize();
	Spaghengine::Start();
	
	//return 0;
}