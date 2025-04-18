#pragma once
#include "Define.h"

class CImage
{
public:
	CImage();
	~CImage();

public:
	void Set_Info(float _fX, float _fY, float _fCX, float _fCY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
		m_tFrame.iStart = 0;
	}
	void Set_FrameKey(const TCHAR* _pFrameKey)
	{
		m_pFrameKey = _pFrameKey;
	}
	void Set_FrameStart(int _iStart) { m_tFrame.iStart = _iStart; } 
	void Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	INFO* Get_Info() { return &m_tInfo; }
	void Set_bCoin() { m_bCoin = true; }
	bool Get_bCoin() { return m_bCoin; }

public:
	void		Initialize();
	void		Late_Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

private:
	void Update_Rect();
	

private:
	INFO			m_tInfo;
	RECT			m_tRect;
	FRAME			m_tFrame;
	const TCHAR*	m_pFrameKey;
	bool	m_bCoin;

	int m_iCX;
	int m_iCY;

};

