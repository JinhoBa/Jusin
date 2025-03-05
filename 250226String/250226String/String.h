#pragma once
#include <iostream>
template<class T>
void Safe_Delete_Array(T& p)
{
	if (p)
	{
		delete[]p;
		p = nullptr;
	}
}

class String
{
public:
	String();
	String(const char* _pString);
	String(const String& _pString);
	~String();
public:
	const char* Get_String();
	void Release();
	const char* value() { return m_pString; }
	String& operator= (const char* _pString);
	String& operator= (const String& rhs);
	String operator+(const char* _pString);
	String operator+(String& rString);
	
private:
	char* m_pString;
	int m_iSize;
};

