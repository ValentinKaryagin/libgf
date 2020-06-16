#pragma once

#include <WS2tcpip.h>
#include <Windows.h>

#include <tchar.h>

#ifdef __cplusplus
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "..\\third_party\\bullet3-2.88\\src\\btBulletDynamicsCommon.h"
#endif

#ifndef LIBGF
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#endif

#ifndef LIBGF
#ifdef _DEBUG
#pragma comment(lib, "..\\third_party\\bullet3-2.88\\build\\lib\\Debug\\BulletDynamics_Debug.lib")
#pragma comment(lib, "..\\third_party\\bullet3-2.88\\build\\lib\\Debug\\BulletCollision_Debug.lib")
#pragma comment(lib, "..\\third_party\\bullet3-2.88\\build\\lib\\Debug\\LinearMath_Debug.lib")
#else
#pragma comment(lib, "..\\third_party\\bullet3-2.88\\build\\lib\\Release\\BulletDynamics.lib")
#pragma comment(lib, "..\\third_party\\bullet3-2.88\\build\\lib\\Release\\BulletCollision.lib")
#pragma comment(lib, "..\\third_party\\bullet3-2.88\\build\\lib\\Release\\LinearMath.lib")
#endif
#endif

#define D3D_SAFE_RELEASE(ptr) if (ptr) { ptr->Release(); ptr = NULL; }
