#ifndef _MOVABLEGUICOMPONENT_H
#define _MOVABLEGUICOMPONENT_H
#include "Texture.h"

class MovableGUIComponent : public Entity {

private:

	bool mPickedUp;
	Texture mTexture = Texture();

public:

	MovableGUIComponent(Texture* mTex);
	~MovableGUIComponent();
	
	void PickUp();
	void Drop();
	
	bool PickedUp();

	void Render();
	void Update();

};

#endif