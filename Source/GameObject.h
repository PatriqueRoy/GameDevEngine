#include <vector>
#include <SFML\Graphics\Transform.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include "BaseComponent.h"
#include "TransformComponent.h"
#include <SFML/Graphics.hpp>

struct Transform {
public:
	sf::Vector2f t_position;
	float t_rotation;
	sf::Vector2f t_scale;
	sf::Vector2f velocity;
};

class
	GameObject
{
	public:
		GameObject(int ID) : uniqueID(ID), parent(NULL) {}

		int GetObjectID() const { return uniqueID; }
			
		std::string texFilePath;

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

		void updateSpriteTransform(sf::RenderWindow *window);

		void AddComponent(BaseComponent* component);

		void createSprite(std::string fileName);
		void drawSprite(sf::RenderWindow *window);

		sf::Sprite* getSprite() {
			return &objectSprite;
		}

		bool isDrawn = true;

		Transform* getTransform() {
			return &Local_Transform;
		}

		Transform TransformAdd(Transform a, Transform b) {
			Transform temp;
			float tempX = a.t_position.x + b.t_position.x;
			float tempY = a.t_position.y + b.t_position.y;
			temp.t_position = sf::Vector2f(tempX, tempY);

			temp.t_rotation = a.t_rotation + b.t_rotation;

			float tempXScale = a.t_scale.x + b.t_scale.x;
			float tempYScale = a.t_scale.y + b.t_scale.y;
			temp.t_scale = sf::Vector2f(tempXScale, tempYScale);

			return temp;
		}

		void setName(std::string name) {
			objectName = name;
		}

		std::string getName() {
			return objectName;
		}

	protected:	
		GameObject * parent;
		int uniqueID;
		std::vector<GameObject*> children;
		std::vector<BaseComponent*> components;
		Transform World_Transform;
		Transform Local_Transform;
		sf::Texture objectTex;
		sf::Sprite objectSprite;
		std::string objectName;
};