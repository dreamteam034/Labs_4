// lab04.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "lab04.h"

#include "Figure.h"
#include "FigureList.h"

#include <fstream>
#include <ctype.h>

#include <stdio.h>
#include <commdlg.h>

#define MAX_LOADSTRING 100

// Workspace size
#define WORKSPACE_WIDTH 1920
#define WORKSPACE_HEIGHT 1080

// Scrolling
#define SCROLL_STEPS 100

// Zooming
#define ZOOM_STEP 0.1
#define ZOOM_MAX 1.2
#define ZOOM_MIN 0.8

// Macros
#define MOUSE_POS int((LOWORD(lParam) / Zoom) + 2 * iHscrollPos), int((HIWORD(lParam) / Zoom) + 2 * iVscrollPos)


using namespace std;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

CHOOSECOLOR cc;
static COLORREF acrCustClr[16];

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB04, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB04));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB04));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB04);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void processInputFile(char *path) {
	const unsigned int bufferLength = 32, typeLength = 16, valueLength = 8, maxLength = 9;
	char buffer[bufferLength], *bufferPtr = buffer, c, type[typeLength], c_value[valueLength];
	int tmp;
	bool onStart = true; //	Ìû òîëüêî íà÷àëè ñ÷èòûâàòü èíôîðìàöèþ î ôèãóðå 
	ifstream in("input.txt");

	while (in.eof()) {
		in >> c;

		
		if (isalpha(c)) {
			if (onStart) {
				*bufferPtr++ = c;
			}
		}
		if (c == '=') {
			*bufferPtr = '\n';
			strcpy_s(type, buffer);
		}
		else if (c == '{') {
			while (in >> c) {
				if (isalpha(c)) {
					*bufferPtr++ = c;
				}
				else if (c == '=') {
					*bufferPtr = '\0';
					bufferPtr = c_value;

					for (int i = 0; i < sizeof(param) / sizeof(char*); i++) {
						if (!strcmp(buffer, param[i])) {
							tmp = i;
						}
					}
				}
				else if (c == ';') {
					*bufferPtr = '\0';
					bufferPtr = buffer;

					inputedParams[tmp] = atoi(c_value); 
					
				}
				else if (c == '}') {
					break;
				}
			}
			bufferPtr = buffer;
		}
	}
}

char *szToolById[] = {
	"line",
	"ellipse",
	"rectangle",
	"rectangle_rounded"
};

int iCurrentTool = -1;
bool bDrawTemp = false;

float Zoom = 1;

CCamera Camera;

CFigureList List;
CPoint StartMousePos = { 0, 0 }, EndMousePos = { 0, 0 };

DWORD rgbBackground = RGB(255, 255, 255);
DWORD rgbBorder = RGB(0, 0, 0);

int iStyleBackground = -1;
int iStyleBorder = 0;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

static int cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth,
iVscrollPos, iVscrollMax, iHscrollPos, iHscrollMax;

void SetZoom(HWND &hWnd, int iValue)
{
	Zoom = iValue;
	if (Zoom > ZOOM_MAX)
		Zoom = ZOOM_MAX;
	else if (Zoom < ZOOM_MIN)
		Zoom = ZOOM_MIN;

	// Scrolls change size
	SetScrollRange(hWnd, SB_VERT, 0, (Zoom - ZOOM_MIN) * 20, TRUE);
	SetScrollRange(hWnd, SB_HORZ, 0, (Zoom - ZOOM_MIN) * 20, TRUE);

	iVscrollPos = 0;
	iHscrollPos = 0;

	InvalidateRect(hWnd, NULL, TRUE);
}

void ChangeZoom(HWND &hWnd, int iValue)
{
	if (iValue != 0)
		Zoom = Zoom + iValue * ZOOM_STEP;
	else
		Zoom = 1;

	SetZoom(hWnd, iValue);
}

OPENFILENAME InitFileDialog(OPENFILENAME &fn, HWND &hWnd, TCHAR pwszFileName[])
{
	fn.lStructSize = sizeof(fn);
	fn.hwndOwner = hWnd;
	fn.lpstrFile = pwszFileName;
	fn.nMaxFile = sizeof(pwszFileName);
	fn.lpstrFilter = _T(".txt");

	return fn;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME fn = { 0 }; 
	TCHAR pwszFileName[128] = _T("file");
	bool bSaveFirstTime = true;

	wchar_t buffer[64];
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_FILE_NEW:
				List.Clean();
				RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
				break; 
			case ID_FILE_OPEN:
				InitFileDialog(fn, hWnd, pwszFileName);

				if (GetOpenFileName(&fn)) {
					List.Clean();
					Camera = List.ReadData(pwszFileName);
					SetZoom(hWnd, Camera.Zoom);
					RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
				}
				break;
			case ID_FILE_SAVE:
				if (bSaveFirstTime) {
					InitFileDialog(fn, hWnd, pwszFileName);

					if (GetOpenFileName(&fn))
						List.PrintList(pwszFileName, Zoom, { 0 , 0 }); //	PUT CAMERA COORDINATES HERE!
				} 
				else
					List.PrintList(pwszFileName, Zoom, { 0 , 0 }); //	PUT CAMERA COORDINATES HERE!

				break;
			case ID_FILE_SAVEAS:
				InitFileDialog(fn, hWnd, pwszFileName);

				//if (GetSaveFileName(&ofn)) {
					//list.printList(fileName);
				//}

				if (GetOpenFileName(&fn))
					List.PrintList(pwszFileName, Zoom, { 0 , 0 }); //	PUT CAMERA COORDINATES HERE!

				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_TOOLS_SELECTION:
				iCurrentTool = -1;
				break;
			case IDM_TOOLS_LINE:
				iCurrentTool = 0;
				break;
			case IDM_TOOLS_ELLIPSE:
				iCurrentTool = 1;
				break;
			case IDM_TOOLS_RECTANGLE:
				iCurrentTool = 2;
				break;
			case IDM_TOOLS_ROUNDED_RECTANGLE:
				iCurrentTool = 3;
				break;
			case IDM_COLORS_BACKGROUND:
				cc.hwndOwner = hWnd;
				cc.rgbResult = rgbBackground;
				if (ChooseColor(&cc))
					rgbBackground = cc.rgbResult;
				break;
			case IDM_COLORS_BORDER:
				cc.hwndOwner = hWnd;
				cc.rgbResult = rgbBorder;
				if (ChooseColor(&cc))
					rgbBorder = cc.rgbResult;
				break;
			case IDM_BORDER_SOLID:
				iStyleBorder = PS_SOLID;
				break;
			case IDM_BORDER_DASHED:
				iStyleBorder = PS_DASH;
				break;
			case IDM_BORDER_DOTTED:
				iStyleBorder = PS_DOT;
				break;
			case IDM_BORDER_DASHDOTTED:
				iStyleBorder = PS_DASHDOT;
				break;
			case IDM_BORDER_DASHDOTDOTTED:
				iStyleBorder = PS_DASHDOTDOT;
				break;
			case IDM_BACKGROUND_DEFAULT:
				iStyleBackground = -1;
				break;
			case IDM_BACKGROUND_HORIZONTAL:
				iStyleBackground = HS_HORIZONTAL;
				break;
			case IDM_BACKGROUND_VERTICAL:
				iStyleBackground = HS_VERTICAL;
				break;
			case IDM_BACKGROUND_FDIAGONAL:
				iStyleBackground = HS_FDIAGONAL;
				break;
			case IDM_BACKGROUND_BDIAGONAL:
				iStyleBackground = HS_BDIAGONAL;
				break;
			case IDM_BACKGROUND_CROSS:
				iStyleBackground = HS_CROSS;
				break;
			case IDM_BACKGROUND_DIAGCROSS:
				iStyleBackground = HS_DIAGCROSS;
				break;
			case IDM_ZOOM_ZOOMIN:
				ChangeZoom(hWnd, 1);
				break;
			case IDM_ZOOM_ZOOMOUT:
				ChangeZoom(hWnd, -1);
				break;
			case IDM_ZOOM_SETDEFAULT:
				ChangeZoom(hWnd, 0);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
		
        break;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			iVscrollPos -= 1;
			break;
		case SB_LINEDOWN:
			iVscrollPos += 1;
			break;
		case SB_THUMBPOSITION:
			iVscrollPos = HIWORD(wParam);
			break;
		default:
			break;
		}

		if (iVscrollPos != GetScrollPos(hWnd, SB_VERT))
		{
			SetScrollPos(hWnd, SB_VERT, iVscrollPos , TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		}

		return 0;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			iHscrollPos -= 1;
			break;
		case SB_LINERIGHT:
			iHscrollPos += 1;
			break;
		case SB_THUMBPOSITION:
			iHscrollPos = HIWORD(wParam);
			break;
		default:
			break;
		}

		if (iHscrollPos != GetScrollPos(hWnd, SB_HORZ))
		{
			SetScrollPos(hWnd, SB_HORZ, iHscrollPos, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			
			HDC hMemDC = CreateCompatibleDC(hdc);
			HBITMAP hScreen = CreateCompatibleBitmap(hdc, WORKSPACE_WIDTH, WORKSPACE_HEIGHT);
			HBITMAP oldBmp = (HBITMAP)SelectObject(hMemDC, hScreen);

			//	SetViewportExtEx(hdc, Scale, Scale, nullptr);
			//	SetViewportExtEx(hMemDC, Scale, Scale, nullptr);

			PatBlt(hMemDC, 0, 0, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, WHITENESS);

			List.DrawList(hMemDC, Zoom);

			if (bDrawTemp)
			{
				CFigure TempFigure(
					StartMousePos,
					EndMousePos,
					szToolById[iCurrentTool], 
					rgbBackground, 
					rgbBorder, 
					iStyleBackground, 
					iStyleBorder
				);

				TempFigure.Draw(hMemDC, Zoom);
			}

			BitBlt(hdc, 0, 0, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, hMemDC, 2 * iHscrollPos * Zoom, 2 * iVscrollPos * Zoom, SRCCOPY);
			SelectObject(hMemDC, oldBmp);
			DeleteObject(hScreen);
			DeleteDC(hMemDC);

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_ERASEBKGND:
		// Fix for drawing
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
		{
			InvalidateRect(hWnd, NULL, TRUE);
			StartMousePos = { MOUSE_POS };
			if (iCurrentTool >= 0)
			{
				// Let's start temp drawing
				bDrawTemp = true;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			bDrawTemp = false;

			if (iCurrentTool >= 0)
			{
				// Let's create our figure

				List.Add({
					StartMousePos,
					EndMousePos,
					szToolById[iCurrentTool],
					rgbBackground,
					rgbBorder,
					iStyleBackground,
					iStyleBorder
				});

				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				// Let's select figure
				unsigned length = List.GetLength() - 1;
				for (unsigned i = length; i > 0; i--)
				{
					
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			EndMousePos = { MOUSE_POS };
			if (bDrawTemp && iCurrentTool >= 0)
			{
				// Let's redraw current figure
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			
		}
		break;
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_OEM_PLUS:
				if (GetAsyncKeyState(VK_CONTROL))
					ChangeZoom(hWnd, 1);
				break;
			case VK_OEM_MINUS:
				if (GetAsyncKeyState(VK_CONTROL))
					ChangeZoom(hWnd, -1);
				break;
			case VK_DELETE:
				
				break;
			}
		}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
