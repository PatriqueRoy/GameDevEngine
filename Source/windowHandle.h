#include <SFML/Graphics.hpp>

class windowHandle : public sf::NonCopyable
{
public:

	static windowHandle* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new windowHandle();
		}
		return s_pInstance;
	}

	windowHandle() : window(sf::VideoMode(410, 650), "Untitled") {}//Initilizing the window

	sf::RenderWindow* getWindow()//referencing the window
	{
		return &window;
	}

private:

	static windowHandle* s_pInstance;

	sf::RenderWindow window;
};

//
