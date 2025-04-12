#pragma once

#include "Define.h"

class CSoundMgr
{
public:
	static CSoundMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundMgr;

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

private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void Release();

public:
	void PlaySound(const TCHAR* pSoundKey, int iID, float fVolume);
	void PlayBGM(const TCHAR* pSoundKey, float fVolume);
	void PlayLoop(const TCHAR* pSoundKey, int iID, float fVolume);
	void StopSound(int iID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);
	int	 Get_AvailableChennel();
	void Return_Chennel(int _iChennel);
private:
	void LoadSoundFile();

private:
	static CSoundMgr* m_pInstance;

	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[SOUND_END];
	deque<int> m_availableChennels;
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem;
};



