#include <vector>
#include <SFML\Graphics\Transform.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include "BaseComponent.h"
#include "TransformComponent.h"
#include <SFML/Graphics.hpp>

class
	GameObject
{
	public:
		GameObject(int ID) : uniqueID(ID), parent(NULL) {	}

		int GetObjectID() const { return uniqueID; }
			
		void SetParent(GameObject& p) {parent = &p;}
		bool checkForParent() 
		{
			if (parent) {
				return true;
			}
			else {
				return false;
			}
		}

		GameObject* getParent() {
			return parent;
		}

		void AddChild(GameObject* s);

		void Update(float msec, sf::RenderWindow *window);
		void Awake();
		void Start();

		void AddComponent(BaseComponent* component);
		TransformComponent Local_transform;

		void createSprite(std::string fileName);
		void drawSprite(sf::RenderWindow *window);

		sf::Sprite* getSprite() {
			return &objectSprite;
		}

		bool isDrawn = true;

	protected:	
		GameObject * parent;
		int uniqueID;
		std::vector<GameObject*> children;
		std::vector<BaseComponent*> components;
		sf::Transform World_Transform;
		sf::Texture objectTex;
		sf::Sprite objectSprite;
};