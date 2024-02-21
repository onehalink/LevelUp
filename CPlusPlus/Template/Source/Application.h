#pragma once

#include "Runtime.h"



Void OnApplicationInitialize(Void* userParameter);
Void OnApplicationResize(SizeType width, SizeType height);
Void OnApplicationFocus(Bool isFocused);
Void OnApplicationQuit(Bool wantToQuit);

Void OnUpdate(RealType deltaTime);
Void OnRender(Void* RenderTarget);