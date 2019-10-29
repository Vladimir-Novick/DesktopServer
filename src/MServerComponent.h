// MServerComponent.h: interface for the CMServerComponent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSERVERCOMPONENT_H__333EBEC2_F76A_4AF6_96DC_1FA996FF2211__INCLUDED_)
#define AFX_MSERVERCOMPONENT_H__333EBEC2_F76A_4AF6_96DC_1FA996FF2211__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMServerComponent  
{
private:
	void *mon;
public:
	char strPath[255];
	int NewIndexImage;
	void LoadImageList();
	void SetWallpaper(char *FileName);
	VOID PublicationDoc();
	VOID ClearLog();
	VOID ShowLogText(char *strText);
	VOID ShowMonitoring();
	CMServerComponent();
	virtual ~CMServerComponent();
private:
	BYTE * ByteWhereStr(BYTE *BufReportDat,UINT lenBuf,char *NameDoc);
};

#endif // !defined(AFX_MSERVERCOMPONENT_H__333EBEC2_F76A_4AF6_96DC_1FA996FF2211__INCLUDED_)
