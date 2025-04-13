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

#define DOOR_TOPX		400.f
#define DOOR_TOPY		125.f

#define DOOR_BOTTOMX	400.f
#define DOOR_BOTTOMY	575.f

#define DOOR_LEFTX		25.f
#define DOOR_LEFTY		350.f

#define DOOR_RIGHTX		775.f
#define DOOR_RIGHTY		350.f


extern HWND    g_hWnd;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_END };
enum OBJID { OBJ_PLAYER, OBJ_MONSTER, OBJ_BULLET, OBJ_TILE, OBJ_ITEM, OBJ_DOOR, OBJ_EFFECT, OBJ_END };
enum UIID { UI_BAR, UI_BUTTON,UI_MOUSE, UI_BOSSHP, UI_MINIMAP, UI_END };
enum CHANNELID { SOUND_BGM, SOUND_EFFECT, SOUND_INTRO, SOUND_BOMBEFFECT, SOUND_TEAR, SOUND_TEARDEAD, SOUND_END = 32 };

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
	float	fMaxHp;
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