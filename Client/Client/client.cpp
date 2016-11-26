#pragma region Includes
#include <stdio.h>
#include <iostream>
#include <windows.h>
#pragma endregion
#define MAP_PREFIX          L"Local\\"
#define MAP_NAME            L"RecoResultMap"
#define FULL_MAP_NAME       MAP_NAME

// File offset where the view is to begin.
#define VIEW_OFFSET         0

// The number of bytes of a file mapping to map to the view. All bytes of the 
// view must be within the maximum size of the file mapping object. If 
// VIEW_SIZE is 0, the mapping extends from the offset (VIEW_OFFSET) to the 
// end of the file mapping.
#define VIEW_SIZE           270*240*4+1

using namespace std;
int wmain(int argc, wchar_t* argv[])
{
	HANDLE hMapFile = NULL;
	PVOID pView = NULL;

	// Try to open the named file mapping identified by the map name.
	hMapFile = OpenFileMapping(
		FILE_MAP_READ,          // Read access
		FALSE,                  // Do not inherit the name
		FULL_MAP_NAME           // File mapping name 
		);
	if (hMapFile == NULL)
	{
		wprintf(L"OpenFileMapping failed w/err 0x%08lx\n", GetLastError());
		goto Cleanup;
	}
	wprintf(L"The file mapping (%s) is opened\n", FULL_MAP_NAME);

	// Map a view of the file mapping into the address space of the current 
	// process.
	pView = MapViewOfFile(
		hMapFile,               // Handle of the map object
		FILE_MAP_READ,          // Read access
		0,                      // High-order DWORD of the file offset 
		VIEW_OFFSET,            // Low-order DWORD of the file offset
		VIEW_SIZE               // The number of bytes to map to view
		);
	if (pView == NULL)
	{
		wprintf(L"MapViewOfFile failed w/err 0x%08lx\n", GetLastError());
		goto Cleanup;
	}
	wprintf(L"The file view is mapped\n");
	while (true)
	{
		// Read and display the content in view.
		//wprintf(L"Read from the file mapping:\n\"%s\"\n", (PWSTR)pView);
		//int i = (PWSTR)pView;
		byte t = *((byte*)pView + VIEW_SIZE-1);
		// int i = (*(byte*)pView + VIEW_SIZE - 1) - '0';;
		cout << "flag:" << t<< endl;
		Sleep(30);
	}
	
	// Wait to clean up resources and stop the process.
	wprintf(L"Press ENTER to clean up resources and quit");
	getchar();

Cleanup:

	if (hMapFile)
	{
		if (pView)
		{
			// Unmap the file view.
			UnmapViewOfFile(pView);
			pView = NULL;
		}
		// Close the file mapping object.
		CloseHandle(hMapFile);
		hMapFile = NULL;
	}

	return 0;
}
