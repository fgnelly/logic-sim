#include "Entity.h"

Entity::Entity(sf::Vector2f pos)
{
	mPos = pos;
	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
	mScale = VEC2_ONE;
}

Entity::~Entity()
{
	mParent = NULL;
}

void Entity::Pos(sf::Vector2f pos)
{
	mPos = pos;
}

sf::Vector2f Entity::Pos(SPACE space)
{
	if (space == local || mParent == NULL)
	{
		return mPos;
	}

	sf::Vector2f parentScale = mParent->Scale(world);
	sf::Vector2f rotPos = RotateVector(sf::Vector2f(mPos.x * parentScale.x, mPos.y * parentScale.y), mParent->Rotation(local));
	return mParent->Pos(world); //got rid of +rotPos
}

void Entity::Rotation(float r) {
	mRotation = r;

	if (mRotation > 360.0f)
		mRotation -= 360.0f;

	if (mRotation < 0.0f)
		mRotation += 360.0f;
}

float Entity::Rotation(SPACE space) {
	if (space == local || mParent == NULL)
		return mRotation;

	return mParent->Rotation(world) + mRotation;
}

void Entity::Scale(sf::Vector2f scale)
{
	mScale = scale;
}

sf::Vector2f Entity::Scale(SPACE space)
{
	if (space == local || mParent == NULL)
	{
		return mScale;
	}

	sf::Vector2f scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void Entity::Active(bool active) {
	mActive = active;
}

bool Entity::Active() {
	return mActive;
}

void Entity::Parent(Entity* parent)
{
	if (parent == NULL)
	{
		mPos = Pos(world);
		mScale = Scale(world);
		mRotation = Rotation(world);
	}
	else
	{
		if (mParent != NULL)
			Parent(NULL);

		sf::Vector2f parentScale = parent->Scale(world);

		mPos = RotateVector(Pos(world) - parent->Pos(world), -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		mRotation = mRotation - parent->Rotation(world);

		mScale = sf::Vector2f(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

Entity* Entity::Parent()
{
	return mParent;
}

void Entity::Translate(sf::Vector2f vec)
{
	mPos += vec;
}

void Entity::Rotate(float amount)
{
	mRotation += amount;
}

void Entity::Update()
{

}

void Entity::Render()
{

}

//void Entity::RenderTransparent(int t)
//{

//}