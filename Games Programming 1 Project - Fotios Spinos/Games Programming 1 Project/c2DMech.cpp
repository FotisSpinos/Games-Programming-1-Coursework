#include "c2DMech.h"



c2DMech::c2DMech()
{
}

void c2DMech::setBulletCollisionMesh()
{
	int pixelStartW = 7;
	//12
	bulletCollisionMesh[0].w = 2;
	bulletCollisionMesh[0].h = 1;

	//11
	bulletCollisionMesh[0].w = 3;
	bulletCollisionMesh[0].h = 1;

	//10
}

SDL_Rect c2DMech::getBulletCollisionMech(int arrayIndex)
{
	return SDL_Rect();
}

