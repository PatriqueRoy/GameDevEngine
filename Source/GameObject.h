#include <vector>
#include <SFML\Graphics\Transform.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include "BaseComponent.h"
#include "TransformComponent.h"

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

		void Update(float msec);
		void Awake();
		void Start();

		void AddComponent(BaseComponent* component);
		TransformComponent Local_transform;

	protected:	
		GameObject * parent;
		int uniqueID;
		std::vector<GameObject*> children;
		std::vector<BaseComponent*> components;
		sf::Transform World_Transform;
};