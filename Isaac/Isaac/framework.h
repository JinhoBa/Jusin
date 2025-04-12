#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//STL 헤더
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>

//c++ 해더
#include <iostream>
#include <string>
#include <functional>
#include <random>

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>
#include <iostream>

//Debug 해더
#include <cassert>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

using namespace std;