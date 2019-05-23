#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H
#include "InputManager.h"
#include "Texture.h"

class CollisionManager {

public:

	enum COLLISION_SIDE {left = 0, right = 1, top = 2, bottom = 3, nocol = 4};

private:

	static CollisionManager* sInstance;

	InputManager* mInputMgr;

public:

	static CollisionManager* Instance();
	static void Release();

	bool checkMouseCollision(Texture* tex);
	COLLISION_SIDE getMouseCollisionSideLR(Texture* tex); //used to check gates heading east and west
	COLLISION_SIDE getMouseCollisionSideTB(Texture* tex); //used to check gates heading north and south

private:

	CollisionManager();
	~CollisionManager();

};

#endif