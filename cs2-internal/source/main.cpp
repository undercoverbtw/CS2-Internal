#include <thread>
#include <Windows.h>

unsigned long __stdcall init(void* pm)
{
#pragma region debuglogs
#ifdef _DEBUG

    // debug console with logs will come in next update
	// debug logs are very importmant and really useful for debugging crashes and where we crash without having to attach a debugger

#endif // _DEBUG
#pragma endregion debuglogs


#pragma region initialization
	do {

		// if (!hooks::setup())
		//      break;
		// 
		// if (!interfaces::setup())
		//      break;

		// unloading cheat when pressing END key
		// if we have not clicked the thread will sleep until unload button preseed
		
		while (!(GetAsyncKeyState(VK_END))) // figure this out :)
			std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sleep thread

	} while (false);
#pragma endregion initialization
	
	
#pragma region unload
	// this code will be executed when unload button is pressed

	// restore hooks etc..

	// sleep thread so we make sure everything unloads smoothely and not rushing it (causing crash)
	std::this_thread::sleep_for(std::chrono::seconds(2));

#ifdef _DEBUG
	// close debug shit
	// for example if you opened a console it would be

	// close file (log file)
	// close debug console
#endif // debug
	
	// lastly we need to exit our thread that we opened in DLLmain
	FreeLibraryAndExitThread(static_cast<HMODULE>(pm), EXIT_SUCCESS);

#pragma endregion unload
}

BOOL APIENTRY DllMain(const HMODULE module, const DWORD reason, const LPVOID reserved)
{
#pragma region injection
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	    {

		// creating our thread and making init run inside of the thread
		if (const HANDLE thread = CreateThread(nullptr, 0, init, module, 0, nullptr); thread != nullptr)
			CloseHandle(thread); 
		// dont really need to explain but we close the thread after creating it.
		
	    }

	}
#pragma endregion injection

	// if everything went good in dll_process_attach we return true
	return TRUE;
}
