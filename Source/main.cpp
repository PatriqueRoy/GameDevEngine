#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include "Initiate.h"
#include <SFML/Graphics.hpp>
#include "Spaghengine.h"

using namespace std;


int main() {
	Spaghengine::Start();
	Spaghengine::Initialize();

	return 0;
}