
#include <stdint.h>
#include <windows.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

struct Bitgoodness
{
	HBITMAP hBitmap;
	BITMAP BMP;
	HINSTANCE Instance;
	LPCTSTR image;
};
struct win32_offscreen_buffer
{
	// NOTE(casey): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
	BITMAPINFO Info;
	void *Memory;
	int Width;
	int Height;
	int Pitch;
	int BytesPerPixel;
};
HINSTANCE gInstance = 0;
bool quit = false;
win32_offscreen_buffer GlobalBackbuffer;
void
Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
{
	// TODO(casey): Bulletproof this.
	// Maybe don't free first, free after, then free first if that fails.

	if (Buffer->Memory)
	{
		VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
	}

	Buffer->Width = Width;
	Buffer->Height = Height;

	int BytesPerPixel = 4;
	Buffer->BytesPerPixel = BytesPerPixel;

	// NOTE(casey): When the biHeight field is negative, this is the clue to
	// Windows to treat this bitmap as top-down, not bottom-up, meaning that
	// the first three bytes of the image are the color for the top left pixel
	// in the bitmap, not the bottom left!
	Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
	Buffer->Info.bmiHeader.biWidth = Buffer->Width;
	Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
	Buffer->Info.bmiHeader.biPlanes = 1;
	Buffer->Info.bmiHeader.biBitCount = 32;
	Buffer->Info.bmiHeader.biCompression = BI_RGB;

	// NOTE(casey): Thank you to Chris Hecker of Spy Party fame
	// for clarifying the deal with StretchDIBits and BitBlt!
	// No more DC for us.
	int BitmapMemorySize = (Buffer->Width*Buffer->Height)*BytesPerPixel;
	Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	Buffer->Pitch = Width * BytesPerPixel;

	// TODO(casey): Probably clear this to black
}

void RenderWeirdGradient(win32_offscreen_buffer *Buffer)
{
	int Width = Buffer->Width;
	int Height = Buffer->Height;

	int Pitch = Width * Buffer->BytesPerPixel;
	uint8 *Row = (uint8 *)Buffer->Memory;
	for (int Y = 0; Y < Buffer->Height; ++Y)
	{
		uint32 *Pixel = (uint32 *)Row;
		for (int X = 0; X < Buffer->Width; ++X)
		{
			uint8 Blue = (X);
			uint8 Green = (Y);

			*Pixel++ = ((Green << 8) | Blue);
		}

		Row += Pitch;
	}

}
void Renderer(HDC DeviceContext, HGDIOBJ hgdi, int x, int y, int width, int height)
{
	HDC hdc = CreateCompatibleDC(DeviceContext);

	SelectObject(hdc, hgdi);
	BitBlt(DeviceContext, x, y, width, height, hdc, 0, 0, SRCCOPY);

	DeleteDC(hdc);
	DeleteObject(hgdi);
}
LRESULT CALLBACK MainWindowCallBack(HWND window, UINT  message, WPARAM  wParam, LPARAM  lParam)
{
	LRESULT result = 0;

	switch (message)
	{
	case WM_SIZE:
	{
		break;
	}
	case WM_DESTROY:
	{
		quit = true;
		break;
	}
	case WM_CLOSE:
	{
		quit = true;
		break;
	}
	case WM_QUIT:
	{
		quit = true;
		break;
	}
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
			quit = true;
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT Paint;
		HDC DeviceContext = BeginPaint(window, &Paint);
		
		Renderer(DeviceContext, &GlobalBackbuffer.Memory, 10, 10, GlobalBackbuffer.Width, GlobalBackbuffer.Height);
		EndPaint(window, &Paint);

		break;
	}
	default:
		result = DefWindowProcA(window, message, wParam, lParam);
	}


	return(result);
}


void CreateBitmap(Bitgoodness * bitg)
{

	bitg->hBitmap = (HBITMAP)LoadImageA(bitg->Instance, bitg->image, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	GetObject(bitg->hBitmap, sizeof(bitg->BMP), &bitg->BMP);

}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE previnstance, PSTR commandline, int showcmd)
{

	WNDCLASS wc = {};
	wc.style = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWindowCallBack;
	wc.hInstance = (HINSTANCE)GetModuleHandle(0);
	wc.hIcon = (HICON)LoadImage(NULL, "favicon.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

	wc.lpszClassName = "Erthel path";

	RegisterClass(&wc);

	HWND windows = CreateWindowExA(0, wc.lpszClassName, wc.lpszClassName,
		WS_TILEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, wc.hInstance, 0);
	Win32ResizeDIBSection(&GlobalBackbuffer, 800, 800);
	if (windows)
	{
		MSG msg;
		while (!quit)
		{
			// Did we recieve a message, or are we idling ?
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Advance Game Frame.
				HDC DeviceContext = GetDC(windows);
				Bitgoodness BackGround;
				BackGround.image = "BackGround.bmp";
				BackGround.Instance = instance;
	
				CreateBitmap(&BackGround);
				
				RenderWeirdGradient(&GlobalBackbuffer) ;
			
				Renderer(DeviceContext, BackGround.hBitmap, 10, 10, BackGround.BMP.bmWidth, BackGround.BMP.bmHeight);
				
				ReleaseDC(windows, DeviceContext);
				DeleteObject(BackGround.hBitmap);
				
				

			}
		}


	}
}
