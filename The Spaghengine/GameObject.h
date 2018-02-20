#include <vector>
#include <SFML\Graphics\Transform.hpp>
#include <SFML\Graphics\Transformable.hpp>

class
	GameObject
{
	public:
		GameObject() {parent = nullptr;}
		~GameObject(void);

		void SetTransform(float &x) { transform = x; }
		float GetTransform() { return transform; }
		float GetWorldTransform() { return worldTransform; }
			
		void SetParent(GameObject& p) {parent = &p;}
		void AddChild(GameObject* s);
		virtual void Update(float msec);

	protected:	
		GameObject* parent;
		float worldTransform;
		float transform;
		std::vector<GameObject*> children;
};