#pragma once
#include "Define.h"

class CObj;
class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

public:
	void Picking_Tile(POINT _pt, int _iDraw, int _iOption);
	vector<CObj*> Get_vecTile() { return m_vecTile; }
	void Save_Tile();
	void Load_Tile(const TCHAR * _FilePath);

public:
	static CTileMgr* Get_Instance();
	static void Destory_Instance();

public:
	static CTileMgr* m_pInstance;
	vector<CObj*> m_vecTile;

	bool m_bTileRender;
};

