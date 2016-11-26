#pragma region Includes
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <windows.h>
using namespace cv;
#pragma endregion
#define MAP_PREFIX          L"Local\\"
#define MAP_NAME            L"RecoResultMap"
#define FULL_MAP_NAME       MAP_PREFIX MAP_NAME

// Max size of the file mapping object.
#define MAP_SIZE            270 * 240 * 4+1

// File offset where the view is to begin.
#define VIEW_OFFSET         0

// The number of bytes of a file mapping to map to the view. All bytes of the 
// view must be within the maximum size of the file mapping object (MAP_SIZE). 
// If VIEW_SIZE is 0, the mapping extends from the offset (VIEW_OFFSET) to  
// the end of the file mapping.
#define VIEW_SIZE           270 * 240 * 4+1

// Unicode string message to be written to the mapped view. Its size in byte 
// must be less than the view size (VIEW_SIZE).
#define MESSAGE             L"1"
#define MESSAGET				L"0"

int wmain(int argc, wchar_t* argv[])
{
	HANDLE hMapFile = NULL;
	PVOID pView = NULL;
	byte *bgrMap = new byte[270 * 240 * 4];
	DWORD cbMessage = 270 * 240 * 4+1;
	// Create the file mapping object.
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // Use paging file - shared memory
		NULL,                   // Default security attributes
		PAGE_READWRITE,         // Allow read and write access
		0,                      // High-order DWORD of file mapping max size
		MAP_SIZE,               // Low-order DWORD of file mapping max size
		FULL_MAP_NAME           // Name of the file mapping object
		);
	if (hMapFile == NULL)
	{
		wprintf(L"CreateFileMapping failed w/err 0x%08lx\n", GetLastError());
		return 0;
		//goto Cleanup;
	}
	wprintf(L"The file mapping (%s) is created\n", FULL_MAP_NAME);

	// Map a view of the file mapping into the address space of the current 
	// process.
	pView = MapViewOfFile(
		hMapFile,               // Handle of the map object
		FILE_MAP_ALL_ACCESS,    // Read and write access
		0,                      // High-order DWORD of the file offset 
		VIEW_OFFSET,            // Low-order DWORD of the file offset 
		VIEW_SIZE               // The number of bytes to map to view
		);
	if (pView == NULL)
	{
		wprintf(L"MapViewOfFile failed w/err 0x%08lx\n", GetLastError());
		return 0;
		//goto Cleanup;
	}
	wprintf(L"The file view is mapped\n");

	// Prepare a message to be written to the view.
	//PWSTR pszMessage = MESSAGE;
	//DWORD cbMessage = (wcslen(pszMessage) + 1) * sizeof(*pszMessage);
	int i = 0;
	VideoCapture video(0);
	video.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	video.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	while (video.isOpened())
	{
		i++;
		Mat bgrImage;

		video >> bgrImage;
		
		resize(bgrImage, bgrImage, Size(270, 240), CV_INTER_LINEAR);
		imshow("c++¶ËÍ¼Ïñ»ñÈ¡", bgrImage);
		int  key = waitKey(1);
		if (key == 27)
		{
			break;
		}

		for (int i = 0; i<240; i++)
		{
			for (int j = 0; j<270; j++)
			{
				//std::cout << "bef:i=" << i << ",j=" << j << std::endl;
				bgrMap[(i * 270 + j) * 4 + 0] = bgrImage.data[(i * 270 + j) * 3 + 0];
				bgrMap[(i * 270 + j) * 4 + 1] = bgrImage.data[(i * 270 + j) * 3 + 1];
				bgrMap[(i * 270 + j) * 4 + 2] = bgrImage.data[(i * 270 + j) * 3 + 2];
				bgrMap[(i * 270 + j) * 4 + 3] = 255;
				
				
			}
		}
		// Write the message to the view.
		bgrMap[270 * 240 * 4] = '1';
		memcpy_s(pView, VIEW_SIZE, bgrMap, cbMessage);
		Sleep(60);
	}



	// Wait to clean up resources and stop the process.
	wprintf(L"Press ENTER to clean up resources and quit");


//Cleanup:

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