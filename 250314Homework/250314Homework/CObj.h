#pragma once

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
public:
	void SetHDC(HDC _hDC) { m_hDC = _hDC; };
protected:
	HDC m_hDC;
	RECT m_rc;
};

