#pragma once

#define WINCX 800
#define WINCY 600

#define	PI		3.141592f
#define PURE		= 0

#define	NOEVENT		0
#define DEAD		1

#define VK_MAX		0xff

#define TILEX		16
#define TILEY		12

#define TILECX		50
#define TILECY		50


extern HWND    g_hWnd;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_END };
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_ITEM, OBJ_EFFECT, OBJ_DOOR, OBJ_TILE, OBJ_END };
enum UIID { UI_BAR, UI_BUTTON,UI_MOUSE, UI_END };


template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

struct DeleteMap
{
	template<typename T>
	void operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;

typedef struct tagStat
{
	float	fHp;
	float	fAttack;
	float	fIntersection;
}STAT;

typedef struct tagItemInfo
{
	int		iCoin;
	int		iBomb;
	int		iKey;
	
}ITEMINFO;

typedef enum typeEDITOR
{
	LINE_EDITOR,
	RECT_EDITOR,
	END_EDITOR
}TYPE_EDITOR;

typedef struct HitInfo
{
	float fX, fY;
	DIRECTION eDirection;

	HitInfo(float _fX, float _fY, DIRECTION _Dir)
		:fX(_fX), fY(_fY), eDirection(_Dir) {
	}

}HITPOINT;

typedef struct tagFrame
{
	int iStart;
	int iEnd;
	int iMotion;
	ULONGLONG dwFrameSpeed;
	ULONGLONG dwTime;
}FRAME;