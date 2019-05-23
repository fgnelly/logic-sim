#include "CollisionManager.h"

CollisionManager* CollisionManager::sInstance = NULL;

CollisionManager* CollisionManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new CollisionManager();

	return sInstance;
}

void CollisionManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

CollisionManager::CollisionManager()
{
	mInputMgr = InputManager::Instance();
}

CollisionManager::~CollisionManager()
{
	mInputMgr = NULL;
}

bool CollisionManager::checkMouseCollision(Texture* tex)
{
	sf::Vector2i MouseVec = mInputMgr->MousePos();
	sf::Vector2f PosVec = tex->Pos();
	sf::Vector2i DimVec = tex->GetDimentions();

	int texTop = PosVec.y + DimVec.y / 2;
	int texLeft = PosVec.x - DimVec.x / 2;
	int texRight = PosVec.x + DimVec.x / 2;
	int texBottom = PosVec.y - DimVec.y / 2;

	if (MouseVec.x >= texLeft && MouseVec.x <= texRight && MouseVec.y <= texTop && MouseVec.y >= texBottom)
		return true;
	else
		return false;
}

CollisionManager::COLLISION_SIDE CollisionManager::getMouseCollisionSideLR(Texture* tex)
{
	sf::Vector2i MouseVec = mInputMgr->MousePos();
	sf::Vector2f PosVec = tex->Pos();
	sf::Vector2i DimVec = tex->GetDimentions();

	int texTop = PosVec.y + DimVec.y / 2;
	int texLeft = PosVec.x - DimVec.x / 2;
	int texRight = PosVec.x + DimVec.x / 2;
	int texBottom = PosVec.y - DimVec.y / 2;
	int texMiddleX = PosVec.x;
	int texMiddleY = PosVec.y;

	if (MouseVec.x < texMiddleX && MouseVec.x >= texLeft && MouseVec.y > texBottom && MouseVec.y < texTop)
	{
		return CollisionManager::left;
	}
	else if (MouseVec.x > texMiddleX && MouseVec.x <= texRight && MouseVec.y > texBottom && MouseVec.y < texTop)
	{
		return CollisionManager::right;
	}
	else
	{
		return CollisionManager::nocol;
	}
}

CollisionManager::COLLISION_SIDE CollisionManager::getMouseCollisionSideTB(Texture* tex)
{
	sf::Vector2i MouseVec = mInputMgr->MousePos();
	sf::Vector2f PosVec = tex->Pos();
	sf::Vector2i DimVec = tex->GetDimentions();

	int texTop = PosVec.y + DimVec.y / 2;
	int texLeft = PosVec.x - DimVec.x / 2;
	int texRight = PosVec.x + DimVec.x / 2;
	int texBottom = PosVec.y - DimVec.y / 2;
	int texMiddleX = PosVec.x;
	int texMiddleY = PosVec.y;

	if (MouseVec.y < texMiddleY && MouseVec.y >= texTop && MouseVec.x > texLeft && MouseVec.x < texRight)
	{
		return CollisionManager::top;
	}
	else if (MouseVec.y > texMiddleY && MouseVec.y <= texBottom && MouseVec.x > texLeft && MouseVec.x < texRight)
	{
		return CollisionManager::bottom;
	}
	else
	{
		return CollisionManager::nocol;
	}
}