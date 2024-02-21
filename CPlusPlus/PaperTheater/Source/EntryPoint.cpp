#include "Application.h"



Int32 EntryPoint()
{
	Runtime runtime;
	runtime.wantToQuit = false;

	OnApplicationInitialize( &runtime );

	while ( !runtime.wantToQuit )
	{
		OnUpdate();
		OnRender();

		Delay(100);
	}

	return 0;
}


int main(int count, char** parameters)
{
	return EntryPoint();
}