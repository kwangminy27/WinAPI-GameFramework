#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#pragma comment(lib, "msimg32.lib")

#include <cassert>
#include <crtdbg.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#define NOMINMAX
#include <Windows.h>

#include "type.h"

struct PIXEL8
{
	unsigned char r;
};

struct PIXEL24
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct PIXEL32
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

using PIXEL8_COLLECTION = std::vector<std::vector<PIXEL8>>;
using PIXEL24_COLLECTION = std::vector<std::vector<PIXEL24>>;
using PIXEL32_COLLECTION = std::vector<std::vector<PIXEL32>>;

struct PIXEL8_INFO
{
	XY world{};
	PIXEL8 comparision_pixel8{};
	PIXEL8_COLLECTION pixel8_collection{};
};

struct PIXEL24_INFO
{
	XY world{};
	PIXEL24 comparision_pixel24{};
	PIXEL24_COLLECTION pixel24_collection{};
};

struct PIXEL32_INFO
{
	XY world{};
	PIXEL32 comparision_pixel32{};
	PIXEL32_COLLECTION pixel32_collection{};
};