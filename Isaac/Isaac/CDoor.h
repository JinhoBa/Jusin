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
	void Set_Door(int _iFrameMotion, const TCHAR* _pFileKey, CSceneMgr::SCENEID _eID) 
	{
		Set_FramMotion(_iFrameMotion);
		Set_FrameKey(_pFileKey);
		Set_SceneID(_eID);
	}

	void Set_SceneID(CSceneMgr::SCENEID _eSceneID) { m_eSceneID = _eSceneID; }
	void Set_Open() { m_bOpen = true; }
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

