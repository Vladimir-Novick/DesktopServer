// MServerComponent.cpp: implementation of the CMServerComponent class.
//
//////////////////////////////////////////////////////////////////////




#include "stdafx.h"


#define DWORD_PTR DWORD
#define ULONG_PTR    DWORD
#include "wininet.h"

#include "shlobj.h"

#include "MServerComponent.h"
#include "CMonitoring.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMServerComponent::CMServerComponent()
{
	mon = NULL;
	NewIndexImage = 0;

}

CMServerComponent::~CMServerComponent()
{
	if (mon != NULL ){
		delete mon;
	}
}

VOID CMServerComponent::ShowMonitoring()
{


	if (mon != NULL) {
		((CCMonitoring *)mon)->ShowWindow(SW_HIDE);
		((CCMonitoring *)mon)->ShowWindow(SW_SHOW);
	} else {
       mon = new CCMonitoring;
       ((CCMonitoring *)mon)->DoModal(::GetDesktopWindow());
	   delete mon;
	   mon = NULL;
	}



}

VOID CMServerComponent::ShowLogText(char *strText)
{
	      if (mon != NULL ){
						((CCMonitoring *)mon)->SendMessage( 
						  ((CCMonitoring *)mon)->GetDlgItem(IDC_LISTDOC),              // handle to destination window 
						  LB_ADDSTRING,             // message to send
						 (WPARAM) 0,          // not used; must be zero
					 	 (LPARAM) strText          // string (LPCTSTR)
						);
		  }

}

VOID CMServerComponent::ClearLog()
{
	/*

    WORD wYear; 
    WORD wMonth; 
    WORD wDayOfWeek; 
    WORD wDay; 
    WORD wHour; 
    WORD wMinute; 
    WORD wSecond; 
    WORD wMilliseconds; 

	*/
	SYSTEMTIME SystemTime;
/*	char strText[100];
	GetLocalTime( &SystemTime);
	sprintf(strText,"Start:  %02d-%02d-%d %02d:%02d:%02d",
		SystemTime.wDay,
		SystemTime.wMonth,
		SystemTime.wYear,
		SystemTime.wHour,
		SystemTime.wMinute,
		SystemTime.wSecond);
	      if (mon != NULL ){
							((CCMonitoring *)mon)->SendMessage( 
						  ((CCMonitoring *)mon)->GetDlgItem(IDC_LISTDOC),             
						  LB_RESETCONTENT,             // Delete all send
						 (WPARAM) 0,          
					 	 (LPARAM) 0          
						);

							ShowLogText(strText);
							ShowLogText(" ");
		  }
*/
}



BYTE * CMServerComponent::ByteWhereStr(BYTE *BufReportDat,UINT lenBuf, char *NameDoc)
{
	UINT iCount = 0;
	UINT lenS = strlen(NameDoc);
	BYTE  *pD = BufReportDat;
	BOOL FlagExit = TRUE;
	char *pS;
	UINT k;
	BYTE *pST= BufReportDat;
	while (TRUE){
		iCount ++;
		if (iCount >= lenBuf ){ break;}
		if (*pD == (BYTE)*NameDoc ){
			pST = pD;
			FlagExit = TRUE;
			pS = NameDoc;
			for (k = 1; k < lenS; k ++){
				pS++;
				pD++;
				if (*pD != (BYTE)*pS ){
				  	FlagExit = FALSE;
					break;
				}
			}

			if (FlagExit == TRUE ){
				return pST;
			}
			
		}
		pD++;

	}

 return BufReportDat;
}




void CMServerComponent::SetWallpaper(char *FileName)
{

//	SPI_SETDESKWALLPAPER
HRESULT hr;
IActiveDesktop *pActiveDesktop;


hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
            IID_IActiveDesktop, (void**)&pActiveDesktop);

CComBSTR fn;//= 
fn = FileName;
WALLPAPEROPT pwpo;
pwpo.dwSize = sizeof WALLPAPEROPT;

//WPSTYLE_CENTER 
//WPSTYLE_TILE 
//WPSTYLE_STRETCH
//WPSTYLE_MAX 

pwpo.dwStyle = WPSTYLE_CENTER ;
//pActiveDesktop->SetWallpaperOptions(&pwpo,0);

pActiveDesktop->SetWallpaper(fn,0);
pActiveDesktop->ApplyChanges(AD_APPLY_ALL  | AD_APPLY_FORCE);
    

// Call the Release method
pActiveDesktop->Release();

//
//  for BMP file
//
//      int ret = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0,FileName, SPIF_UPDATEINIFILE |  SPIF_SENDWININICHANGE);
//
}




void CMServerComponent::LoadImageList()
{

#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
    HRESULT hRes = CoInitialize(NULL);
#endif
        WIN32_FIND_DATA FindFileData;
        HANDLE hFind;
		char fileName[MAX_PATH];
		char strMask[254];
		char NameMenu[MAX_PATH];
		BOOL ret= TRUE;
		int indCurrent = 0;
		BOOL bOK = FALSE;
		char newWallpaper[255];



//		GetCurrentDirectory(254,strMask);
		strcpy(strMask,strPath);
		strcpy(newWallpaper,strPath);
		strcat(strMask,"\\*.jpg");
        hFind = FindFirstFile(strMask, &FindFileData);

        if (hFind != INVALID_HANDLE_VALUE) {
			if (FindFileData.cFileName[0]=='.'){
			   ret = FindNextFile(hFind,&FindFileData);
			}
		}

        if (hFind != INVALID_HANDLE_VALUE) {
			if (FindFileData.cFileName[0]=='.'){
			   ret = FindNextFile(hFind,&FindFileData);
			}
		}


        if (hFind != INVALID_HANDLE_VALUE) {
			while (ret){
				strcpy(fileName,FindFileData.cFileName);
				strcpy(NameMenu,FindFileData.cFileName);
				if (NewIndexImage == indCurrent){
					bOK = TRUE;
					NewIndexImage++;
					break;
				}
			   indCurrent++;
			   ret = FindNextFile(hFind,&FindFileData);
			}
		}
  
        FindClose(hFind);
		if ( bOK == TRUE ) {
			strcat(newWallpaper,"\\");
			strcat(newWallpaper,fileName);
			this->SetWallpaper(newWallpaper);
		} else {
			NewIndexImage = 0;

		}
		CoUninitialize( );
}
