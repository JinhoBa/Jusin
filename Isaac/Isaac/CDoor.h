#pragma once
#include "CObj.h"
#include "CSceneMgr.h"

class CDoor : public CObj
{
	enum DOORDIR{UP, LEFT, RIGHT, DOWN};
public:
	CDoor();
	~CDoor();

public:
	void Set_SceneID(CSceneMgr::SCENEID _eSceneID) { m_eSceneID = _eSceneID; }
	bool Get_bOpen() { return m_bOpen; }
public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	bool m_bOpen;
	CSceneMgr::SCENEID m_eSceneID;
};

