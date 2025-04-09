#pragma once
class CObj;
class CEffectMgr
{
private:
	CEffectMgr();
	~CEffectMgr();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

public:
	void	Add_Effect(TCHAR* _pFilePath, float _fX, float _fY, float _fCX, float _fCY);

public:
	static CEffectMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CEffectMgr;
		}

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	static CEffectMgr* m_pInstance;

	list<CObj*> m_EffectList;
};

