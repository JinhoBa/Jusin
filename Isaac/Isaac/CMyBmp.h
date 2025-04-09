#pragma once
class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC Get_DC() { return m_MemDC; }
	void Load_Bmp(const TCHAR* pFilePath);
	void Release();

private:
	HDC m_MemDC;

	HBITMAP m_curBitMap;
	HBITMAP m_oldBitMap;
};

