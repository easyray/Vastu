#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "string-lib/stringmanip.h"
#include "resource.h"
#include "controllers/main-controller.h"


LRESULT   CALLBACK   MainWndProc (HWND, UINT, WPARAM, LPARAM) ;
HINSTANCE            hInst;


// Our application entry point.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	hInst = hInstance;
	//HMENU hSysMenu;

	WNDCLASSEX  wc;
	LPCTSTR     MainWndClass = TEXT("Win32 Test application");
	HWND        hWnd;
	MSG         msg;

	
	// Class for our main window.
	wc.cbSize        = sizeof(wc);
	wc.style         = 0;
	wc.lpfnWndProc   = &MainWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	
	wc.hIcon         = (HICON) LoadImage(hInstance, 
		MAKEINTRESOURCE(IDI_APPICON), 
		IMAGE_ICON, 0, 0,
		LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED
	);
	
	wc.hCursor       = (HCURSOR) LoadImage(
		NULL, IDC_ARROW, 
		IMAGE_CURSOR, 0, 0, 
		LR_SHARED
	);
	
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName = MainWndClass;
	wc.hIconSm       = 0;

	// Register our window classes, or error.
	if (! RegisterClassEx(&wc))
	{
	MessageBox(NULL, TEXT("Error starting windows application."), TEXT("Error"), MB_ICONERROR | MB_OK);
	return 0;
	}

	// Create instance of main window.
/****/	
	hWnd = CreateWindowEx(
		0, MainWndClass, TEXT("VASTU"), 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		360, 500,
		NULL, NULL, 
		hInstance, NULL
	);
/******/	
/*****
	hWnd = CreateWindowEx(
		0, MainWndClass, TEXT("VASTU"), 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		360, 660,
		NULL, NULL, 
		hInstance, NULL
	);
/*****/	

	// Error if window creation failed.
	if (! hWnd)
	{
	MessageBox(NULL, TEXT(" There was an error creating main window. Contact the app developer"), TEXT("Error"), MB_ICONERROR | MB_OK);
	return 0;
   }
	
// Show window and force a paint.
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

//activate error reporting mechanism
/****
	_Seun_HWND    = hWnd;
	_Seun_IDC_ERR = IDC_Y; 
	_Seun_IDC_MSG = IDC_X; 
 /*****/
// Main message loop.
  while(GetMessage(&msg, NULL, 0, 0) > 0)
  {
  /*  if (! TranslateAccelerator(msg.hwnd, hAccelerators, &msg))
    {
 */
      TranslateMessage(&msg);
      DispatchMessage(&msg);
 /*   }  */
  }

  return (int) msg.wParam;
}


//window procedure
LRESULT CALLBACK MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	
	HWND hCtrl0_0, hCtrl0_1, hCtrl0_2, hCtrl0_3, hCtrl0_4, hCtrl0_5 ;	
	HWND hCtrl0_6, hCtrl0_7, hCtrl0_8, hCtrl0_9, hCtrl0_10, hCtrl0_11 ;	
	HWND hCtrl0_12, hCtrl0_13, hCtrl0_14, hCtrl0_15, hCtrl0_16, hCtrl0_17 ;	
	HWND hCtrl0_18, hCtrl0_19, hCtrl0_20;	
	
	 switch (message)
     {
     case WM_CREATE:
	 
#include "vastu-interface.t"

     return 0 ;

	 case   WM_DESTROY:
		PostQuitMessage (0) ;
	return 0;
	
	case   WM_COMMAND: 
		switch((int) LOWORD(wParam) ){
			case IDM_EXIT:
				handleExit( hWnd, (int) LOWORD(wParam), (HWND) lParam, (UINT)HIWORD(wParam) );
			return 0;

			case IDC_BTN:
					doVastu( hWnd, (int) LOWORD(wParam), (HWND) lParam, (UINT)HIWORD(wParam) ); 
			return 0;		
			
		}
	return 0;
	case   WM_LBUTTONDOWN: 
	case   WM_RBUTTONUP: 
	case   WM_MOUSEWHEEL: 
	case   WM_INITDIALOG:  
	case   WM_KEYDOWN: 
	case   WM_KEYUP: 
	case   WM_PAINT: 
	case   WM_QUIT: 
	case   WM_MOUSEMOVE:			
		return DefWindowProc (hWnd, message, wParam, lParam) ;
	 }	  
	
	
	return DefWindowProc (hWnd, message, wParam, lParam) ;
}

