// WebComServer.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f WebComServerps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <Windows.H>
#include <WindowsX.H>
#include <initguid.h>
#include "WebComServer.h"
#include "MServerComponent.h"
#include "RegisterSave.h"

#include "WebComServer_i.c"
#define UM_DISPRESICONNOTIFY     (WM_USER + 100)
#define adgHANDLE_DLGMSG(hwnd, message, fn)                          \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,               \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))

BOOL DispRes_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam);
VOID ShowMenuItem_WM_DRAWITEM(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
VOID ShowMenuItem_WM_MEASUREITEM(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;



CMServerComponent *_MServerComponent;
LRESULT  DispRes_OnActivate (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify );


void DispRes_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

void DispRes_OnDestroy (HWND hwnd);

void DispRes_OnIconNotify (HWND hwnd, UINT uID, UINT uMsg);
BOOL WINAPI DispRes_WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


const DWORD dwTimeOut = 5000; // time for EXE to be idle before shutting down
const DWORD dwPause = 1000; // time to wait for threads to finish up

static TCHAR g_szAppName[] = __TEXT("DesktopServer");
HWND hWndMonitor = NULL;



// Variables shared across all instances of our application which ensure
// that only one instance of this application  will run at a given time.
#pragma data_seg("Shared")
static LONG g_lInstanceCount = -1;
#pragma data_seg()

#pragma data_seg(".drectve")
static char szShared[] = "-section:Shared,rws";
#pragma data_seg()


// Passed to CreateThread to monitor the shutdown event
static DWORD WINAPI MonitorProc(void* pv)
{
    CExeModule* p = (CExeModule*)pv;
    p->MonitorShutdown();
    return 0;
}




   typedef struct _ITEMMENU
    { 
        WORD Whfont;  // HFONT 
        char psz_ItemText[255]; 
	    WORD WhBitmap;
    } ITEMMENU;             // structure for item font and string  



	static ITEMMENU ItemAbout;
	static ITEMMENU ItemExit;
	static ITEMMENU ItemInternet;
	static ITEMMENU ItemProperties;



void CreateMenuListRBotton(HMENU hmenuMain,HMENU hmenuContext){

	ItemAbout.WhBitmap = IDB_ABOUT;
	strcpy(ItemAbout.psz_ItemText," About");




	ItemExit.WhBitmap = IDB_CLOSE;
	strcpy(ItemExit.psz_ItemText," Close");



	ItemInternet.WhBitmap = IDB_INTERNET;
	strcpy(ItemInternet.psz_ItemText," Online User's Guide  ");


	ItemProperties.WhBitmap = IDB_PROPERTIES;
	strcpy(ItemProperties.psz_ItemText," Properties");
	

    ModifyMenu(hmenuContext, ID_ABOUT, MF_BYCOMMAND | 
                MF_OWNERDRAW, ID_ABOUT, (LPTSTR) &ItemAbout); 


    ModifyMenu(hmenuContext, ID_IDRRBUTTON_ONLINEHELP, MF_BYCOMMAND | 
                MF_OWNERDRAW, ID_IDRRBUTTON_ONLINEHELP, (LPTSTR) &ItemInternet); 


    ModifyMenu(hmenuContext, ID_EXIT, MF_BYCOMMAND | 
                MF_OWNERDRAW, ID_EXIT, (LPTSTR) &ItemExit); 


    ModifyMenu(hmenuContext, ID_IDRRBUTTON_PROPERTIES, MF_BYCOMMAND | 
                MF_OWNERDRAW, ID_IDRRBUTTON_PROPERTIES, (LPTSTR) &ItemProperties); 






	







}


LONG CExeModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0)
    {
        bActivity = true;
        SetEvent(hEventShutdown); // tell monitor that we transitioned to zero
    }
    return l;
}






HFONT GetAFontA(int fnFont) 
{ 
    static LOGFONT lf;  // structure for font information  
 
 
    GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), 
        &lf); 
 
 
    if (fnFont == 1) lf.lfWeight = FW_BOLD; 
    
 
    return CreateFont(lf.lfHeight, lf.lfWidth, 
        lf.lfEscapement, lf.lfOrientation, lf.lfWeight, 
        lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, 
        lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, 
        lf.lfPitchAndFamily, lf.lfFaceName); 

}



extern long SleepTime;

VOID ThreadFunc(LPVOID);

DWORD threadID;

HANDLE threadDD;


   VOID ThreadFunc(LPVOID)

	   
   {  while(TRUE){
      _MServerComponent->LoadImageList();
			Sleep(SleepTime);
	   }
   }

//Monitors the shutdown event
void CExeModule::MonitorShutdown()
{
    while (1)
    {
        WaitForSingleObject(hEventShutdown, INFINITE);
        DWORD dwWait=0;
        do
        {
            bActivity = false;
            dwWait = WaitForSingleObject(hEventShutdown, dwTimeOut);
        } while (dwWait == WAIT_OBJECT_0);
        // timed out
        if (!bActivity && m_nLockCnt == 0) // if no activity let's really bail
        {
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
            CoSuspendClassObjects();
            if (!bActivity && m_nLockCnt == 0)
#endif
                break;
        }
    }
    CloseHandle(hEventShutdown);
    PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
}

bool CExeModule::StartMonitor()
{
    hEventShutdown = CreateEvent(NULL, false, false, NULL);
    if (hEventShutdown == NULL)
        return false;
    DWORD dwThreadID;
    HANDLE h = CreateThread(NULL, 0, MonitorProc, this, 0, &dwThreadID);
    return (h != NULL);
}

CExeModule _Module;
long SleepTime= 20000;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}




/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
    int nRet = 0;
    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
   // Only allow one instance of our application to execute
   if (InterlockedIncrement(&g_lInstanceCount) > 0) {

      InterlockedDecrement(&g_lInstanceCount);
      MessageBox(NULL, __TEXT("Desktop server is already running"), 
         g_szAppName, MB_ICONINFORMATION | MB_OK);

   } else {


#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
    HRESULT hRes = CoInitialize(NULL);
#endif
    _ASSERTE(SUCCEEDED(hRes));
    _Module.Init(ObjectMap, hInstance, &LIBID_WEBCOMSERVERLib);
    _Module.dwThreadID = GetCurrentThreadId();
    TCHAR szTokens[] = _T("-/");

    BOOL bRun = TRUE;
    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
    while (lpszToken != NULL)
    {
        if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_WebComServer, FALSE);
            nRet = _Module.UnregisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
        {
            _Module.UpdateRegistryFromResource(IDR_WebComServer, TRUE);
            nRet = _Module.RegisterServer(TRUE);
            bRun = FALSE;
            break;
        }
        lpszToken = FindOneOf(lpszToken, szTokens);
    }

    if (bRun)
    {
        _Module.StartMonitor();
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
        _ASSERTE(SUCCEEDED(hRes));
        hRes = CoResumeClassObjects();
#else
        hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE);
#endif
        _ASSERTE(SUCCEEDED(hRes));

        MSG msg;
	    _MServerComponent = new CMServerComponent;



//        while (GetMessage(&msg, 0, 0, 0))
//

      // Create our modeless dialog About dialog box.
      HWND hwnd = CreateDialog(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDD_ABOUT), 
         NULL, DispRes_WndProc);

   threadDD = NULL;


   
       threadDD = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) ThreadFunc,
                    0, 0, &threadID);

 
      // Keep our process running

	LPSTR lpCmdLine = GetCommandLine();


	int k;
	char strPath[255];
	strcpy(strPath,lpCmdLine);
	for (k = strlen(strPath)-1;k>0;k--){
		if (strPath[k] == '\\'){break;}
	}
	strPath[k] = 0;
	if (strlen(strPath) > 0 ){
	strcpy(_MServerComponent->strPath,&strPath[1]);
	} else {
	strcpy(_MServerComponent->strPath,"");
	}


      CRegisterSave regS;
	  regS.AutoRun(TRUE);
      SleepTime = 0;
	  regS.UserKeyStore("TimeOut",&SleepTime,0,CRegisterSave::READ);
	  if ( SleepTime <= 0 ){
        SleepTime = 20000;
	  }
      while (GetMessage(&msg, hwnd, 0, 0)) {
         if (!IsDialogMessage(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
      }
	  if (threadDD != NULL ){
          TerminateThread(
            threadDD,    // handle to the thread
           0 );
		  threadDD = NULL;
	  }
		
	  regS.AutoRun(FALSE);
 	  delete _MServerComponent;

      DestroyWindow(hwnd);

//



            DispatchMessage(&msg);

        _Module.RevokeClassObjects();
        Sleep(dwPause); //wait for any threads to finish
    }

    _Module.Term();
    CoUninitialize();
	}
    return nRet;
}

///////////////////////////////////////////////////////////////////////////////


BOOL WINAPI DispRes_WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   switch (uMsg) {
        case WM_DRAWITEM:
		  if (_Module.CheckMenuHwnd == hwnd ){ 
            ShowMenuItem_WM_DRAWITEM(hwnd, uMsg, wParam,lParam); 
		  }
		  return(TRUE);
        break;
      case WM_MEASUREITEM:
		  if (_Module.CheckMenuHwnd == hwnd ){ 
            ShowMenuItem_WM_MEASUREITEM(hwnd, uMsg, wParam,lParam); 
		  }
		  return(TRUE);

      case UM_DISPRESICONNOTIFY:
         // A mouse message occured over our notification icon
         DispRes_OnIconNotify(hwnd, (UINT) wParam, (UINT) lParam);
         return(TRUE);

      adgHANDLE_DLGMSG(hwnd, WM_INITDIALOG, DispRes_OnInitDialog);
      adgHANDLE_DLGMSG(hwnd, WM_DESTROY,    DispRes_OnDestroy);
      adgHANDLE_DLGMSG(hwnd, WM_COMMAND,    DispRes_OnCommand);
      adgHANDLE_DLGMSG(hwnd, WM_ACTIVATE,    DispRes_OnActivate);
   }

   return(FALSE);
}



///////////////////////////////////////////////////////////////////////////////

void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, long xStart,
                           long yStart, COLORREF cTransparentColor)
   {
   BITMAP     bm;
   COLORREF   cColor;
   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
   POINT      ptSize;

   hdcTemp = CreateCompatibleDC(hdc);
   SelectObject(hdcTemp, hBitmap);   // Select the bitmap

   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device

                                     // to logical points

   // Create some DCs to hold temporary data.
   hdcBack   = CreateCompatibleDC(hdc);
   hdcObject = CreateCompatibleDC(hdc);
   hdcMem    = CreateCompatibleDC(hdc);
   hdcSave   = CreateCompatibleDC(hdc);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC
   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   bmBackOld   = (HBITMAP )SelectObject(hdcBack, bmAndBack);
   bmObjectOld = (HBITMAP )SelectObject(hdcObject, bmAndObject);
   bmMemOld    = (HBITMAP )SelectObject(hdcMem, bmAndMem);
   bmSaveOld   = (HBITMAP )SelectObject(hdcSave, bmSave);

   // Set proper mapping mode.
   SetMapMode(hdcTemp, GetMapMode(hdc));

   // Save the bitmap sent here, because it will be overwritten.
   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   cColor = SetBkColor(hdcTemp, cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
          SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   SetBkColor(hdcTemp, cColor);

   // Create the inverse of the object mask.
   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
          NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
          SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

   // Copy the destination to the screen.
   BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
          SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   // Delete the memory bitmaps.
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));

   // Delete the memory DCs.
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);
   DeleteDC(hdcObject);
   DeleteDC(hdcSave);
   DeleteDC(hdcTemp);
   } 

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

VOID ShowMenuItem_WM_DRAWITEM(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
 
    ITEMMENU *pmyitem;      // pointer to item's font and string        
//    static HMENU hmenu;             // handle to main menu            
    static COLORREF crSelText;  // text color of selected item        
    static COLORREF crSelBkgnd; // background color of selected item  
    COLORREF crText;            // text color of unselected item      
    COLORREF crBkgnd;           // background color unselected item   
          
    LPDRAWITEMSTRUCT lpdis;     // pointer to item drawing data        
    HDC hdc;                    // handle to screen DC                
    SIZE size;                  // menu-item text extents             
    WORD wCheckX;               // check-mark width                   
    int nTextX;                 // width of menu item                 
    int nTextY;                 // height of menu item 
    HFONT hfontOld;             // handle to old font                 
    BOOL fSelected = FALSE;     // menu-item selection flag      
    BITMAP  bm;
	HBITMAP hBmp;
	HFONT hFont;
	DWORD ItemHeight;


 

			


		    crSelText = GetSysColor(COLOR_HIGHLIGHTTEXT); 
		    crSelBkgnd = GetSysColor(COLOR_HIGHLIGHT); 


 
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
            pmyitem = (ITEMMENU *) lpdis->itemData; 


			if ((pmyitem->WhBitmap == IDB_ITEMDEFAULT)&&(lpdis->itemState & ODS_SELECTED)){
			   hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_ITEMDEFAULT_N));
			} else {
//			     if ((pmyitem->WhBitmap == IDB_NEXT)&&(lpdis->itemState & ODS_SELECTED)){
//			         hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_NEXT_S));
//				 }else {
			         hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->WhBitmap));
//				 }
			}
		    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
			
 
            if (lpdis->itemState & ODS_SELECTED) 
            { 
                crText = SetTextColor(lpdis->hDC, crSelText); 
                crBkgnd = SetBkColor(lpdis->hDC, crSelBkgnd); 
                fSelected = TRUE; 
            } 
 
            wCheckX = GetSystemMetrics(SM_CXMENUCHECK); 

            wCheckX = 0; 
            nTextX = wCheckX ;
			nTextX = nTextX + lpdis->rcItem.left+bm.bmWidth; 
            nTextY = lpdis->rcItem.top; 
 
			if ( pmyitem->Whfont == 1 ) {
 			  hFont = GetAFontA(0);
              hfontOld = (HFONT)SelectObject(lpdis->hDC,hFont ); 
			}

			 
            hdc = GetDC(hwnd); 
			
           GetTextExtentPoint32(hdc, pmyitem->psz_ItemText, 
                lstrlen(pmyitem->psz_ItemText), &size); 
			if (size.cy < bm.bmHeight ){
				nTextY = nTextY + (bm.bmHeight-size.cy)/2 ;
			}			
		
			ItemHeight = bm.bmHeight;
			
			ExtTextOut(lpdis->hDC, nTextX, nTextY, ETO_OPAQUE, 
                &lpdis->rcItem, pmyitem->psz_ItemText, 
                lstrlen(pmyitem->psz_ItemText), NULL); 

			if ( pmyitem->Whfont == 1 ) {
            SelectObject(lpdis->hDC, hfontOld); 
            }
 
            if (fSelected) 
            { 
               SetTextColor(lpdis->hDC, crText); 
               SetBkColor(lpdis->hDC, crBkgnd); 
            } 

			POINT pS;
            nTextY = lpdis->rcItem.top; 
			pS.x = wCheckX/2 + lpdis->rcItem.left;
			pS.x = lpdis->rcItem.left;
			pS.y = nTextY;

            DrawTransparentBitmap(lpdis->hDC,hBmp,pS.x,pS.y,RGB(0,128,0));
			DeleteObject(hBmp);



			if ( pmyitem->Whfont == 1 ) {
			if (fSelected){
			    hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_SELECTED));
		        GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
            pS.y = nTextY+(ItemHeight - bm.bmHeight) / 2;
                DrawTransparentBitmap(lpdis->hDC,hBmp,pS.x,pS.y,RGB(0,128,0));
			    DeleteObject(hBmp);
			} else {
			    hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(IDB_SELECTING));
		        GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
                pS.y = nTextY+(ItemHeight - bm.bmHeight) / 2;
              DrawTransparentBitmap(lpdis->hDC,hBmp,pS.x,pS.y,RGB(0,128,0));
			    DeleteObject(hBmp);
			}
			  DeleteObject(hFont);
			}

            ReleaseDC(hwnd, hdc); 
			return;
} 




////--------------

///////////////////////////////////////////////////////////////////////////////

VOID ShowMenuItem_WM_MEASUREITEM(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
 
    ITEMMENU *pmyitem;      // pointer to item's font and string        
//    static HMENU hmenu;             // handle to main menu            

   

    LPMEASUREITEMSTRUCT lpmis;  // pointer to item of data             
      
    HDC hdc;                    // handle to screen DC                
    SIZE size;                  // menu-item text extents             
                
              
 
    HFONT hfontOld;             // handle to old font                 
    BOOL fSelected = FALSE;     // menu-item selection flag      
    BITMAP  bm;
	HBITMAP hBmp;
	HFONT hFont;


 
            hdc = GetDC(hwnd); 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            pmyitem = (ITEMMENU *) lpmis->itemData; 

			hBmp = LoadBitmap(_Module.GetModuleInstance(),MAKEINTRESOURCE(pmyitem->WhBitmap));
		    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bm);
			DeleteObject(hBmp);

			hFont = GetAFontA(0);
            hfontOld = (HFONT)SelectObject(hdc,hFont ); 
 
            GetTextExtentPoint32(hdc, pmyitem->psz_ItemText, 
                lstrlen(pmyitem->psz_ItemText), &size); 
            lpmis->itemWidth = size.cx + bm.bmWidth ;
			if (size.cy < bm.bmHeight ){
				lpmis->itemHeight = bm.bmHeight ;
			}else {
            lpmis->itemHeight = size.cy; 
			}
 
 
            SelectObject(hdc, hfontOld); 
            ReleaseDC(hwnd, hdc); 
			DeleteObject(hFont);
 
} 



///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
LRESULT  DispRes_OnActivate (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify ){
		if (hwndCtl == WA_INACTIVE ){
			::ShowWindow(hwnd, SW_HIDE);
		}
		return 0;
}

void DispRes_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {

   switch (id) {
      case IDOK:
      case IDCANCEL:
         ShowWindow(hwnd, SW_HIDE);
         break;
   }
}


///////////////////////////////////////////////////////////////////////////////
// A mouse message occured over our notification icon.
void DispRes_OnIconNotify (HWND hwnd, UINT uID, UINT uMsg) {

   DWORD dwModeNum = (DWORD) -1; // # of DEVMODEs
   DWORD dwMenuIndex = 0;  // Index into menu where item should be inserted
//   HDC hdc  = GetDC(hwnd);  // Screen DC used to get current resolution info
   HMENU hmenuMain = NULL;
   HMENU hmenuContext = NULL;


   HMENU ghMenu = NULL;


  switch (uMsg) {
	  
 
  
      case WM_RBUTTONUP:
		  {
		   hmenuMain = LoadMenu(_Module.GetModuleInstance(), 
		      MAKEINTRESOURCE(IDR_RBUTTON));
		   hmenuContext = GetSubMenu(hmenuMain, 0);
		   CreateMenuListRBotton(hmenuMain,hmenuContext);

          
		  break;
		  }
      default:
          return;
  }		  


	_Module.CheckMenuHwnd = hwnd;

	SetForegroundWindow(hwnd);	

   // Display the context menu near the mouse cursor
   POINT pt;
   GetCursorPos(&pt);
   UINT uMenuID = TrackPopupMenu(hmenuContext, 
      TPM_BOTTOMALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
      pt.x, pt.y, 0, hwnd, NULL);

   DestroyMenu(hmenuMain);

	PostMessage(hwnd, WM_NULL, 0, 0);	

   switch (uMenuID) {
      case 0:  // The menu was cancelled
         break;
	  case ID_IDRRBUTTON_PROPERTIES:
		  {
			  _MServerComponent->ShowMonitoring();
		  }
		  break;
        case ID_ABOUT:
         RECT rc;
         GetWindowRect(hwnd, &rc);
         SetWindowPos(hwnd, NULL, 
            (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2,
            (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2,
            0, 0, SWP_NOZORDER | SWP_NOSIZE);

         ShowWindow(hwnd, SW_SHOW);
         break;
		case ID_IDRRBUTTON_ONLINEHELP:
		             ShellExecute(NULL, "open", "http://www.deltacom.co.il", NULL, NULL, SW_SHOWNORMAL);

		  break;


      case ID_EXIT:
         PostQuitMessage(1);
         break;

      default:



  



         break;
   }         
//   ReleaseDC(hwnd, hdc);
   
}



void DispRes_OnDestroy (HWND hwnd) {

   // Remove the notification icon from the taskbar
   NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uID = IDI_COMSERVER;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

///////////////////////////////////////////////////////////////////////////////

BOOL DispRes_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam) {

   // Add the notification icon to the taskbar
   NOTIFYICONDATA nid;
   nid.cbSize = sizeof(nid);
   nid.hWnd = hwnd;        
   nid.uID = IDI_COMSERVER;   
   nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   nid.uCallbackMessage = UM_DISPRESICONNOTIFY;
   nid.hIcon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_ICONSERVER));
   lstrcpyn(nid.szTip, g_szAppName, sizeof(nid.szTip) / sizeof(nid.szTip[0]));
   Shell_NotifyIcon(NIM_ADD, &nid);

   // Set an icon with our window
   SendMessage(hwnd, WM_SETICON, (WPARAM) TRUE, (LPARAM) nid.hIcon);


   return(TRUE);
}