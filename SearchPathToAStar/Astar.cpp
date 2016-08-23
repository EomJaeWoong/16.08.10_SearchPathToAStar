#include "stdafx.h"
#include "Astar.h"

BYTE MAP[MAPSIZE_Y][MAPSIZE_X];
int iStartX, iStartY, iEndX, iEndY;
BOOL isObsc, bObsticle;
list<NODE *> ltOpenlist, ltCloselist;
NODE *EndNode;

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

	EndNode = NULL;

	isObsc = TRUE;
	bObsticle = TRUE;
}

/*---------------------------------------------------------------------------------*/
// Map �ʱ�ȭ
/*---------------------------------------------------------------------------------*/
void InitMap()
{
	for (int iCntY = 0; iCntY < MAPSIZE_Y; iCntY++)
	{
		for (int iCntX = 0; iCntX < MAPSIZE_X; iCntX++)
			if (MAP[iCntY][iCntX] != OBSTICLE)
			MAP[iCntY][iCntX] = BLANK;
	}

	EndNode = NULL;

	MAP[iStartY][iStartX] = START;
	MAP[iEndY][iEndX] = END;
}

/*---------------------------------------------------------------------------------*/
// A* ��ã��
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
			EndNode = stSearchNode;
			break;
			//�θ���� ��� �׸��� ��
		}

		for ()
		ltCloselist.push_back(stSearchNode);
		MAP[stSearchNode->iY][stSearchNode->iX] = DONE;

		//UU
		if (MAP[(stSearchNode->iY) - 1][stSearchNode->iX] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			if (MAP[stSearchNode->iY - 1][stSearchNode->iX] == CREATE ||
				MAP[stSearchNode->iY - 1][stSearchNode->iX] == DONE)
					isExist = TRUE;

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

			if (MAP[stSearchNode->iY - 1][stSearchNode->iX + 1] == CREATE ||
				MAP[stSearchNode->iY - 1][stSearchNode->iX + 1] == DONE)
					isExist = TRUE;

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX + 1, (stSearchNode->iY) - 1, stSearchNode->fG + 1.5f, stSearchNode));
				MAP[stSearchNode->iY - 1][stSearchNode->iX + 1] = CREATE;
			}
		}

		//RR
		if (MAP[stSearchNode->iY][(stSearchNode->iX) + 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			if (MAP[stSearchNode->iY][stSearchNode->iX + 1] == CREATE ||
				MAP[stSearchNode->iY][stSearchNode->iX + 1] == DONE)
					isExist = TRUE;

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

			if (MAP[stSearchNode->iY + 1][stSearchNode->iX + 1] == CREATE ||
				MAP[stSearchNode->iY + 1][stSearchNode->iX + 1] == DONE)
					isExist = TRUE;

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX + 1, stSearchNode->iY + 1, stSearchNode->fG + 1.5f, stSearchNode));
				MAP[stSearchNode->iY + 1][stSearchNode->iX + 1] = CREATE;
			}
		}

		//DD
		if (MAP[(stSearchNode->iY) + 1][stSearchNode->iX] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			if (MAP[stSearchNode->iY + 1][stSearchNode->iX] == CREATE ||
				MAP[stSearchNode->iY + 1][stSearchNode->iX] == DONE)
				isExist = TRUE;

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

			if (MAP[stSearchNode->iY + 1][stSearchNode->iX - 1] == CREATE ||
				MAP[stSearchNode->iY + 1][stSearchNode->iX - 1] == DONE)
				isExist = TRUE;

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX - 1, (stSearchNode->iY) + 1, stSearchNode->fG + 1.5f, stSearchNode));
				MAP[stSearchNode->iY + 1][stSearchNode->iX - 1] = CREATE;
			}
		}

		//LL
		if (MAP[stSearchNode->iY][stSearchNode->iX - 1] != OBSTICLE)
		{
			BOOL isExist = FALSE;

			if (MAP[stSearchNode->iY][stSearchNode->iX - 1] == CREATE ||
				MAP[stSearchNode->iY][stSearchNode->iX - 1] == DONE)
				isExist = TRUE;


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

			if (MAP[stSearchNode->iY - 1][stSearchNode->iX - 1] == CREATE ||
				MAP[stSearchNode->iY - 1][stSearchNode->iX - 1] == DONE)
				isExist = TRUE;

			if (!isExist)
			{
				ltOpenlist.push_back(CreateNode(stSearchNode->iX - 1, (stSearchNode->iY) - 1, stSearchNode->fG + 1.5f, stSearchNode));
				MAP[stSearchNode->iY - 1][stSearchNode->iX - 1] = CREATE;
			}
		}

		MAP[iStartY][iStartX] = START;
		MAP[iEndY][iEndX] = END;

		InvalidateRect(hWnd, NULL, false);
		SendMessage(hWnd, WM_PAINT, 0, 0);
	}
}

/*---------------------------------------------------------------------------------*/
// Node ����
/*---------------------------------------------------------------------------------*/
NODE* CreateNode(int iX, int iY, float fG, NODE *pParent)
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

void ReleaseList()
{
	list<NODE *>::iterator iter;

	for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
		delete *iter;

	for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
		delete *iter;

	ltOpenlist.clear();
	ltCloselist.clear();

	EndNode = NULL;
}

/*---------------------------------------------------------------------------------*/
// Draw
/*---------------------------------------------------------------------------------*/
void DrawMap(HDC hdc)
{
	TCHAR text[20];
	list<NODE *>::iterator iter;

	/*---------------------------------------------------------------------------------*/
	// Map �׸���
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

	/*---------------------------------------------------------------------------------*/
	/*test*/
	for (iter = ltOpenlist.begin(); iter != ltOpenlist.end(); ++iter)
	{
		swprintf_s(text, TEXT("%.2f"), (*iter)->fG);
		TextOut(hdc, (*iter)->iX * TILE_SIZE, (*iter)->iY * TILE_SIZE, text, wcslen(text));
	}
	
	for (iter = ltCloselist.begin(); iter != ltCloselist.end(); ++iter)
	{
		swprintf_s(text, TEXT("%.2f"), (*iter)->fG);
		TextOut(hdc, (*iter)->iX * TILE_SIZE, (*iter)->iY * TILE_SIZE, text, wcslen(text));
	}
	/*---------------------------------------------------------------------------------*/

	for (int iCntY = 0; iCntY < MAPSIZE_Y; iCntY++)
	{
		for (int iCntX = 0; iCntX < MAPSIZE_X; iCntX++)
		{
			/*---------------------------------------------------------------------------------*/
			// ������ �׸���
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
			// ������ �׸���
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
			// ��ֹ� �׸���
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

			/*
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
			*/
		}
	}
	SelectObject(hdc, hPenOld);

	DeleteObject(hPen);
	DeleteObject(hPenOld);
	DeleteObject(hNullPen);
}

void DrawPath(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	if (EndNode != NULL){
		while (EndNode->pParent != NULL)
		{
			MoveToEx(hdc, (EndNode->iX * TILE_SIZE) + (TILE_SIZE / 2),
				(EndNode->iY * TILE_SIZE) + (TILE_SIZE / 2), NULL);
			LineTo(hdc, (EndNode->pParent->iX * TILE_SIZE) + (TILE_SIZE / 2),
				(EndNode->pParent->iY * TILE_SIZE) + (TILE_SIZE / 2));
			EndNode = EndNode->pParent;
		}
	}
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/*---------------------------------------------------------------------------------*/
// ������ Setting
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
// ������ Setting
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
// ��ֹ� Setting
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