#pragma once
#include "..\third Party\xor.h"
#include "..\Init/DLL Init.h"
#include <lmcons.h>
#include <future>
#define DLL_EXPORT extern "C" __declspec(dllexport)
std::future<DWORD WINAPI> FutureInit;
char username[UNLEN + 1];
DWORD username_len = sizeof(username);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved){

	DisableThreadLibraryCalls(hinstDLL);

	if (fdwReason == DLL_PROCESS_ATTACH)
	{

		FutureInit = std::async(std::launch::async, DLL_Init::Init_Point, hinstDLL);


	}
	return TRUE;
}