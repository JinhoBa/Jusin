#pragma once
#include "CUI.h"
class CNumber : public CUI
{
public:
	CNumber();
	~CNumber();
public:
	void Set_Frame(int _iStart, int _iMotion)
	{
		m_tFrame.iStart = _iStart;
		m_tFrame.iMotion = _iMotion;
	}

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	FRAME m_tFrame;
};

