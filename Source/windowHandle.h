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

	windowHandle() : window(sf::VideoMode(1024, 768), "Untitled") {}

	sf::RenderWindow* getWindow()
	{
		return &window;
	}

private:

	static windowHandle* s_pInstance;

	sf::RenderWindow window;

};

//
