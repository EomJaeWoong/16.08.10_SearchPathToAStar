#ifndef __ASTAR__H__
#define __ASTAR__H__

#define MAPSIZE_Y 60
#define MAPSIZE_X 100
#define TILE_SIZE 15

#define BLANK 0
#define START 1
#define END 2
#define OBSTICLE 3
#define CREATE 4
#define DONE 5

struct NODE
{
	int iX;
	int iY;

	float fG;
	float fH;
	float fF;

	NODE *pParent;
};

struct lessF
{
	bool operator () (NODE *left, NODE *right) const
	{
		return left->fF < right->fF;
	}
};

/*---------------------------------------------------------------------------------*/
// MAP 초기화
/*---------------------------------------------------------------------------------*/
void		Init();
void		InitMap();

/*---------------------------------------------------------------------------------*/
// A* 길찾기
/*---------------------------------------------------------------------------------*/
void		SearchToAstar(HWND hWnd);

/*---------------------------------------------------------------------------------*/
// Node 관련
/*---------------------------------------------------------------------------------*/
NODE* 		CreateNode(int iX, int iY, int fG, NODE *pParent);

/*---------------------------------------------------------------------------------*/
// Draw 관련
/*---------------------------------------------------------------------------------*/
void		DrawMap(HDC hdc);
void		CreateStart(int iX, int iY);
void		CreateEnd(int iX, int iY);
void		CreateObsticle(int iX, int iY);
void		SetisObsc(BOOL bObsc);

using namespace std;

#endif