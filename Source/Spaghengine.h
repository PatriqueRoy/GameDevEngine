#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "windowHandle.h"

class Spaghengine
{
public:
	static void Start();
	static void Initialize();
	
private:
	static bool IsExiting();
	static void GameLoop();
	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};
	static GameState _gameState;
	static float currentTime;
	static float deltaTime;
};