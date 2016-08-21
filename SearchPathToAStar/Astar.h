#ifndef __ASTAR__H__
#define __ASTAR__H__

#define MAPSIZE_Y 60
#define MAPSIZE_X 100
#define TILE_SIZE 15

#define BLANK 0
#define START 1
#define END 2
#define OBSTICLE 3

struct NODE
{
	int iX;
	int iY;

	float fG;
	float fH;
	float fF;

	NODE *pParent;
};

void		InitMap();
void		DrawMap(HDC hdc);
void		CreateStart(int iX, int iY);
void		CreateEnd(int iX, int iY);
void		CreateObsticle(int iX, int iY);
void		SetisObsc(BOOL bObsc);
#endif