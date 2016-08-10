#include "stdafx.h"
#include "Astar.h"

BYTE MAP[MAPSIZE_Y][MAPSIZE_X];

void DrawMap(HDC hdc)
{
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
}