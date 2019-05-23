#ifndef _ENTITY_H
#define _ENTITY_H
#include "MathHelper.h"

class Entity {
public:
	enum SPACE {local = 0, world = 1};

private:

	sf::Vector2f mPos;
	float mRotation;
	sf::Vector2f mScale;

	bool mActive;
	Entity* mParent;

public:

	Entity(sf::Vector2f pos = VEC2_ZERO);
	~Entity();

	void Pos(sf::Vector2f pos);
	sf::Vector2f Pos(SPACE space = world);

	void Rotation(float rotation);
	float Rotation(SPACE space = world);

	void Scale(sf::Vector2f scale);
	sf::Vector2f Scale(SPACE space = world);

	void Active(bool active);
	bool Active();

	void Parent(Entity* parent);
	Entity* Parent();

	void Translate(sf::Vector2f vec);
	void Rotate(float amount);

	virtual void Update();
	virtual void Render();
	//virtual void RenderTransparent(int t);

};

#endif