#include "GameConstants.h"

class c2DMech
{
public:
	c2DMech();
	SDL_Rect bulletCollisionMesh[];
	void setBulletCollisionMesh();
	
	SDL_Rect getBulletCollisionMech(int arrayIndex);
};

