#pragma once
#include "Define.h"

class CBtn
{
public:
	CBtn();
	~CBtn();
public:
	void		Initialize();
	void		Late_Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	void Update_Rect();


private:
	INFO			m_tInfo;
	RECT			m_tRect;
};

