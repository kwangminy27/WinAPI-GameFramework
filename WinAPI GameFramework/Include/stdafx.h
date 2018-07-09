#pragma once

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include <cassert>
#include <crtdbg.h>

#include <array>
#include <chrono>
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
