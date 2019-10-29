// CMonitoring.cpp : Implementation of CCMonitoring
#include "stdafx.h"
#include "CMonitoring.h"
#include "MServerComponent.h"
#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////
// CCMonitoring
extern CMServerComponent *_MServerComponent;

LRESULT CCMonitoring::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	    char Buf[254];
		int sx = GetSystemMetrics(SM_CXSCREEN);
		int sy = GetSystemMetrics(SM_CYSCREEN);
		RECT Rect;
	    GetWindowRect( &Rect );
		sx = (sx - Rect.right) / 2;
		sy = (sy - Rect.bottom) / 2;
		SetWindowPos(NULL,sx,sy,Rect.right+sx-Rect.left,Rect.bottom+sy-Rect.bottom,SWP_NOSIZE);
		HICON hIcon = LoadIcon(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDI_ICONSERVER_TOOLS_WINDOW));
		SetIcon(hIcon,TRUE);
		SetWindowText("Desktop Server");
		HWND hwndWal= GetDlgItem(IDC_EDIT_WALLPAPER_DIR);
		::SetWindowText(hwndWal,_MServerComponent->strPath);
		hwndWal= GetDlgItem(IDC_COMBO_WAIT);
		sprintf(Buf,"%d",SleepTime/60000);
		::SetWindowText(hwndWal,Buf);


		return 1;  // Let the system set the focus
	}







