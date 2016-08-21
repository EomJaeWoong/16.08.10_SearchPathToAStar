#include "stdafx.h"
#include "Astar.h"

BYTE MAP[MAPSIZE_Y][MAPSIZE_X];
int iStartX, iStartY, iEndX, iEndY;
BOOL isObsc, bObsticle;

/*---------------------------------------------------------------------------------*/
// Map �ʱ�ȭ
/*---------------------------------------------------------------------------------*/
void InitMap()
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

void DrawMap(HDC hdc)
{
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
				hPenOld = (HPEN)SelectObject(hdc, hNullPen);

				Rectangle(hdc, iCntX * TILE_SIZE + 1, iCntY * TILE_SIZE + 1,
					(iCntX + 1) * TILE_SIZE + 1, (iCntY + 1) * TILE_SIZE) + 2;

				SelectObject(hdc, hBrushOld);
				SelectObject(hdc, hPenOld);
				DeleteObject(hBrush);
				DeleteObject(hBrushOld);
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
				SelectObject(hdc, hPenOld);
				DeleteObject(hBrush);
				DeleteObject(hBrushOld);
			}

			/*---------------------------------------------------------------------------------*/
			// ��ֹ� �׸���
			/*---------------------------------------------------------------------------------*/
			else if (MAP[iCntY][iCntX] == OBSTICLE)
			{
				HBRUSH hBrush, hBrushOld;
				hBrush = CreateSolidBrush(RGB(200, 200, 200));
				hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

				Rectangle(hdc, iCntX * TILE_SIZE + 1, iCntY * TILE_SIZE + 1,
					(iCntX + 1) * TILE_SIZE + 1, (iCntY + 1) * TILE_SIZE) + 2;

				SelectObject(hdc, hBrushOld);
				SelectObject(hdc, hPenOld);
				DeleteObject(hBrush);
				DeleteObject(hBrushOld);
			}
		}
	}
	DeleteObject(hPen);
	DeleteObject(hPenOld);
	DeleteObject(hNullPen);
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