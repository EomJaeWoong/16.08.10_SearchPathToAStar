#include "stdafx.h"
#include "Astar.h"

BYTE MAP[MAPSIZE_Y][MAPSIZE_X];
int iStartX, iStartY, iEndX, iEndY;
BOOL isObsc, bObsticle;
list<NODE *> ltOpenlist, ltCloselist;

void Init()
{
	for (int iCntY = 0; iCntY < MAPSIZE_Y; iCntY++)
	{
		for (int iCntX = 0; iCntX < MAPSIZE_X; iCntX++)
			MAP[iCntY][iCntX] = BLANK;
	}

	iStartX = -1;
	iStartY = -1;
	iEndX = -1;
	iEndY = -1;

	isObsc = TRUE;
	bObsticle = TRUE;
}

/*---------------------------------------------------------------------------------*/
// Map 초기화
/*---------------------------------------------------------------------------------*/
void InitMap()
{
	for (int iCntY = 0; iCntY < MAPSIZE_Y; iCntY++)
	{
		for (int iCntX = 0; iCntX < MAPSIZE_X; iCntX++)
			if (MAP[iCntY][iCntX] != OBSTICLE)
			MAP[iCntY][iCntX] = BLANK;
	}

	MAP[iStartY][iStartX] = START;
	MAP[iEndY][iEndX] = END;
}

/*---------------------------------------------------------------------------------*/
// A* 길찾기
/*---------------------------------------------------------------------------------*/
void SearchToAstar(HWND hWnd)
{
	NODE* stSearchNode;
	list<NODE *>::iterator iter;

	if ((iStartX == -1 && iStartY == -1) || (iEndX == -1 && iEndY == -1))
		return;

	ltOpenlist.push_back(CreateNode(iStartX, iStartY, 0, NULL));

	while (1)
	{
		ltOpenlist.sort(lessF());
		stSearchNode = ltOpenlist.front();
		ltOpenlist.pop_front();

		if (stSearchNode->iX == iEndX && stSearchNode->iY == iEndY)
		{
			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
				delete *iter;

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
				delete *iter;

			ltOpenlist.clear();
			ltCloselist.clear();

			return;
			//부모와의 경로 그리고 끝
		}

		ltCloselist.push_back(stSearchNode);
		MAP[stSearchNode->iY][stSearchNode->iX] = DONE;

		//UU
		if (MAP[(stSearchNode->iY) - 1][stSearchNode->iX] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX && (*iter)->iY == stSearchNode->iY - 1)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX && (*iter)->iY == stSearchNode->iY - 1)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX, stSearchNode->iY - 1, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY - 1][stSearchNode->iX] = CREATE;
			}
		}

		//RU
		if (MAP[(stSearchNode->iY) - 1][(stSearchNode->iX) + 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX + 1 && (*iter)->iY == stSearchNode->iY - 1)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX + 1 && (*iter)->iY == stSearchNode->iY - 1)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX + 1, (stSearchNode->iY) - 1, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY - 1][stSearchNode->iX + 1] = CREATE;
			}
		}

		//RR
		if (MAP[stSearchNode->iY][(stSearchNode->iX) + 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX + 1 && (*iter)->iY == stSearchNode->iY)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX + 1 && (*iter)->iY == stSearchNode->iY)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX + 1, stSearchNode->iY, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY][stSearchNode->iX + 1] = CREATE;
			}
		}

		//RD
		if (MAP[stSearchNode->iY + 1][stSearchNode->iX + 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX + 1 && (*iter)->iY == stSearchNode->iY + 1)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX + 1 && (*iter)->iY == stSearchNode->iY + 1)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX + 1, stSearchNode->iY + 1, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY + 1][stSearchNode->iX + 1] = CREATE;
			}
		}

		//DD
		if (MAP[(stSearchNode->iY) + 1][stSearchNode->iX] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX && (*iter)->iY == stSearchNode->iY + 1)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX && (*iter)->iY == stSearchNode->iY + 1)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX, (stSearchNode->iY) + 1, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY + 1][stSearchNode->iX] = CREATE;
			}
		}

		//LD
		if (MAP[(stSearchNode->iY) + 1][stSearchNode->iX - 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX - 1 && (*iter)->iY == stSearchNode->iY + 1)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX - 1 && (*iter)->iY == stSearchNode->iY + 1)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX - 1, (stSearchNode->iY) + 1, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY + 1][stSearchNode->iX - 1] = CREATE;
			}
		}

		//LL
		if (MAP[stSearchNode->iY][stSearchNode->iX - 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX - 1 && (*iter)->iY == stSearchNode->iY)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX - 1 && (*iter)->iY == stSearchNode->iY)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX - 1, stSearchNode->iY, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY][stSearchNode->iX - 1] = CREATE;
			}
		}

		//LU
		if (MAP[(stSearchNode->iY) - 1][stSearchNode->iX - 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX - 1 && (*iter)->iY == stSearchNode->iY - 1)
				{
					isExist = TRUE;
					break;
				}
			}

			for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
			{
				if ((*iter)->iX == stSearchNode->iX - 1 && (*iter)->iY == stSearchNode->iY - 1)
				{
					isExist = TRUE;
					break;
				}
			}

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX - 1, (stSearchNode->iY) - 1, stSearchNode->fG + 1, stSearchNode));
				MAP[stSearchNode->iY - 1][stSearchNode->iX - 1] = CREATE;
			}
		}

		MAP[iStartY][iStartX] = START;
		MAP[iEndY][iEndX] = END;

		SendMessage(hWnd, WM_TIMER, 1, 0);
	}
}

/*---------------------------------------------------------------------------------*/
// Node 생성
/*---------------------------------------------------------------------------------*/
NODE* CreateNode(int iX, int iY, int fG, NODE *pParent)
{
	NODE* stNode = new NODE;
	stNode->iX = iX;
	stNode->iY = iY;
	stNode->pParent = pParent;

	stNode->fG = fG;
	stNode->fH = abs(stNode->iX - iEndX) + abs(stNode->iY - iEndY);
	stNode->fF = stNode->fG + stNode->fH;

	return stNode;
}


/*---------------------------------------------------------------------------------*/
// Draw
/*---------------------------------------------------------------------------------*/
void DrawMap(HDC hdc)
{
	/*---------------------------------------------------------------------------------*/
	// Map 그리기
	/*---------------------------------------------------------------------------------*/
	HPEN hPen, hPenOld, hNullPen;
	hNullPen = (HPEN)GetStockObject(NULL_PEN);
	hPen = CreatePen(PS_SOLID, 0, RGB(150, 150, 150));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	for (int iCntX = 0; iCntX <= MAPSIZE_X; iCntX++)
	{
		MoveToEx(hdc, iCntX * TILE_SIZE, 0, NULL);
		LineTo(hdc, iCntX * TILE_SIZE, MAPSIZE_Y * TILE_SIZE);
	}

	for (int iCntY = 0; iCntY <= MAPSIZE_Y; iCntY++)
	{
		MoveToEx(hdc, 0, iCntY * TILE_SIZE, NULL);
		LineTo(hdc, MAPSIZE_X * TILE_SIZE, iCntY * TILE_SIZE);
	}

	SelectObject(hdc, hPenOld);
	hPenOld = (HPEN)SelectObject(hdc, hNullPen);

	for (int iCntY = 0; iCntY < MAPSIZE_Y; iCntY++)
	{
		for (int iCntX = 0; iCntX < MAPSIZE_X; iCntX++)
		{
			/*---------------------------------------------------------------------------------*/
			// 시작점 그리기
			/*---------------------------------------------------------------------------------*/
			if (MAP[iCntY][iCntX] == START)
			{
				HBRUSH hBrush, hBrushOld;
				hBrush = CreateSolidBrush(RGB(0, 255, 0));
				hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
				

				Rectangle(hdc, iCntX * TILE_SIZE + 1, iCntY * TILE_SIZE + 1,
					(iCntX + 1) * TILE_SIZE + 1, (iCntY + 1) * TILE_SIZE) + 2;

				SelectObject(hdc, hBrushOld);
				DeleteObject(hBrush);
			}

			/*---------------------------------------------------------------------------------*/
			// 도착점 그리기
			/*---------------------------------------------------------------------------------*/
			else if (MAP[iCntY][iCntX] == END)
			{
				HBRUSH hBrush, hBrushOld;
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

				Rectangle(hdc, iCntX * TILE_SIZE + 1, iCntY * TILE_SIZE + 1,
					(iCntX + 1) * TILE_SIZE + 1, (iCntY + 1) * TILE_SIZE) + 2;

				SelectObject(hdc, hBrushOld);
				DeleteObject(hBrush);
				DeleteObject(hBrushOld);
			}

			/*---------------------------------------------------------------------------------*/
			// 장애물 그리기
			/*---------------------------------------------------------------------------------*/
			else if (MAP[iCntY][iCntX] == OBSTICLE)
			{
				HBRUSH hBrush, hBrushOld;
				hBrush = CreateSolidBrush(RGB(150, 150, 150));
				hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

				Rectangle(hdc, iCntX * TILE_SIZE + 1, iCntY * TILE_SIZE + 1,
					(iCntX + 1) * TILE_SIZE + 1, (iCntY + 1) * TILE_SIZE) + 2;

				SelectObject(hdc, hBrushOld);
				DeleteObject(hBrush);
				DeleteObject(hBrushOld);
			}

			else if (MAP[iCntY][iCntX] == CREATE)
			{
				HBRUSH hBrush, hBrushOld;
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
				hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

				Rectangle(hdc, iCntX * TILE_SIZE + 1, iCntY * TILE_SIZE + 1,
					(iCntX + 1) * TILE_SIZE + 1, (iCntY + 1) * TILE_SIZE) + 2;

				SelectObject(hdc, hBrushOld);
				DeleteObject(hBrush);
				DeleteObject(hBrushOld);
			}

			else if (MAP[iCntY][iCntX] == DONE )
			{
				HBRUSH hBrush, hBrushOld;
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

				Rectangle(hdc, iCntX * TILE_SIZE + 1, iCntY * TILE_SIZE + 1,
					(iCntX + 1) * TILE_SIZE + 1, (iCntY + 1) * TILE_SIZE) + 2;

				SelectObject(hdc, hBrushOld);
				DeleteObject(hBrush);
				DeleteObject(hBrushOld);
			}
		}
	}
	SelectObject(hdc, hPenOld);

	DeleteObject(hPen);
	DeleteObject(hPenOld);
	DeleteObject(hNullPen);
}

/*---------------------------------------------------------------------------------*/
// 시작점 Setting
/*---------------------------------------------------------------------------------*/
void CreateStart(int iX, int iY)
{
	if (iX < MAPSIZE_X && iY < MAPSIZE_Y)
	{
		if (iStartX != -1 && iStartY != -1)
			MAP[iStartY][iStartX] = BLANK;
			
		iStartX = iX;
		iStartY = iY;

		MAP[iY][iX] = START;
	}
}

/*---------------------------------------------------------------------------------*/
// 도착점 Setting
/*---------------------------------------------------------------------------------*/
void CreateEnd(int iX, int iY)
{
	if (iX < MAPSIZE_X && iY < MAPSIZE_Y)
	{
		if (iEndX != -1 && iEndY != -1)
			MAP[iEndY][iEndX] = BLANK;

		iEndX = iX;
		iEndY = iY;

		MAP[iY][iX] = END;
	}
}

/*---------------------------------------------------------------------------------*/
// 장애물 Setting
/*---------------------------------------------------------------------------------*/
void CreateObsticle(int iX, int iY)
{
	if (iX < MAPSIZE_X && iY < MAPSIZE_Y)
	{
		if (MAP[iY][iX] == OBSTICLE && isObsc)
		{
			bObsticle = TRUE;
			isObsc = FALSE;
		}
		else if (MAP[iY][iX] == BLANK  && isObsc)
		{
			bObsticle = FALSE;
			isObsc = FALSE;
		}

		if(bObsticle)	MAP[iY][iX] = BLANK;
		else			MAP[iY][iX] = OBSTICLE;
	}
}

void SetisObsc(BOOL bObsc)	{ isObsc = bObsc; }