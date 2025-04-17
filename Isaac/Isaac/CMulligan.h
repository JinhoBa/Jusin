#pragma once
#include "CMonster.h"

class CMulligan : public CMonster
{
	enum MULLIGANSTATE {LEFT, RIGHT, ST_END};
public:
	CMulligan();
	~CMulligan();

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
	void Move();

private:
	MULLIGANSTATE m_eCurState;
	MULLIGANSTATE m_ePreState;


};

