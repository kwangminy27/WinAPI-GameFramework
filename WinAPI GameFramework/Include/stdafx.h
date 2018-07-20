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
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <string>
#include <unordered_map>

#define NOMINMAX
#include <Windows.h>

#include "type.h"