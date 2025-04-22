#pragma once
#include "CMonster.h"

class CCharger : public CMonster
{
	enum CHARGERSTATE{LEFT, TOP, RIGHT, BOTTOM, ATTACK, ST_END};
public:
	CCharger();
	~CCharger();

public:
	void Set_DIR(int _i) 
	{
		switch (_i)
		{
		case 4:
			m_eCurState = LEFT;
			break;
		case 6:
			m_eCurState = RIGHT;
			break;
		case 8:
			m_eCurState = TOP;
			break;
		case 2:
			m_eCurState = BOTTOM;
			break;
		default:
			break;
		}
	}

public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	void Change_Motion();

private:
	CHARGERSTATE m_eCurState;
	CHARGERSTATE m_ePreState;

	CHARGERSTATE m_eStateDIR;

	float m_fOffX;
	float m_fOffY;

};

