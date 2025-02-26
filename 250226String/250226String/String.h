#pragma once
#include <iostream>
class String
{
public:
	String();
	String(const char _szString[]);
	~String();
public:
	const char* value() { return m_szString; }
	void operator= (const char _szString[]);
	String operator+ (String& _String);
	bool operator== (String& _String);
private:
	char m_szString[64];
};

