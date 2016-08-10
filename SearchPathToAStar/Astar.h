#ifndef __ASTAR__H__
#define __ASTAR__H__

#define MAPSIZE_Y 60
#define MAPSIZE_X 100
#define TILE_SIZE 15

struct NODE
{
	int iX;
	int iY;

	float fG;
	float fH;
	float fF;

	NODE *pParent;
};

void DrawMap(HDC hdc);

#endif