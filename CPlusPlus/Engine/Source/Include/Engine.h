#pragma once

/**
* Used By The Other C++ Project
* 
* Note:
* Build this project as a dynamic link library
*/



/**
* [Include]
* 
* Path(Visual Studio Macro): $(SolutionDir)CPlusPlus/Engine/Source/Include
*/


/**
* [Link]
* 
* Path(Visual Studio Macro): $(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)
*/
#pragma comment(lib, "Engine")


/**
* For Visual Studio
* 
* Output Directory:			$(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)
* Intermediate Directory:	$(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)/$(ProjectName)
*/


/**
* Import engine
* 
* Note:
* As a flag to define ENGINE_API(default is DLL_EXPORT) as DLL_IMPORT
*/
#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API_IMPORTS
#endif


#include "../Runtime/Core.h"

#include "../Runtime/Asset/Bitmap.h"

#include "../Runtime/Platform/HAL/Keyboard.h"
#include "../Runtime/Platform/HAL/Mouse.h"

#include "../Runtime/Platform/SAL/Console.h"
#include "../Runtime/Platform/SAL/Directory.h"
#include "../Runtime/Platform/SAL/EventSystem.h"
#include "../Runtime/Platform/SAL/File.h"
#include "../Runtime/Platform/SAL/Path.h"

#if defined(PLATFORM_WINDOWS)
#include "../Runtime/Platform/Windows/FileDialog.h"
#include "../Runtime/Platform/Windows/GraphicDeviceInterface.h"
#include "../Runtime/Platform/Windows/Window.h"
#endif