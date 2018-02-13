#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Spaghengine
{
public:
	void Start();
	void Initialize();
	void GameLoop();

	Spaghengine(sf::RenderWindow& window);

	sf::RenderWindow& _mainWindow;

private:
	static bool IsExiting();
	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static GameState _gameState;
};