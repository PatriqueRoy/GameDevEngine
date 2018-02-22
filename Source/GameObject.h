#include <vector>
#include <SFML\Graphics\Transform.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include "BaseComponent.h"
#include "TransformComponent.h"

class
	GameObject
{
	public:
		GameObject() {
			parent = nullptr;
		}
		~GameObject(void);
			
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
		virtual void Update(float msec);

		void AddComponent(BaseComponent* component);

	protected:	
		GameObject* parent;
		std::vector<GameObject*> children;
		std::vector<BaseComponent*> components;
};