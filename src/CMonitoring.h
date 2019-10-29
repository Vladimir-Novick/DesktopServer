// CMonitoring.h : Declaration of the CCMonitoring

#ifndef __CMONITORING_H_
#define __CMONITORING_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "RegisterSave.h"
	extern long SleepTime;

/////////////////////////////////////////////////////////////////////////////
// CCMonitoring
class CCMonitoring : 
	public CAxDialogImpl<CCMonitoring>
{
public:
	CCMonitoring()
	{
	}

	~CCMonitoring()
	{
	}

	enum { IDD = IDD_CMONITORING };

BEGIN_MSG_MAP(CCMonitoring)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_COMBO_WAIT, CBN_SELCHANGE, OnSelchangeCombo_wait)
	COMMAND_HANDLER(IDC_COMBO_WAIT, EN_CHANGE, OnChangeCombo_wait)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}



	LRESULT OnSelchangeCombo_wait(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.

		return 0;
	}
	LRESULT OnChangeCombo_wait(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long lW;
		char Buf[255];
		HWND hwndL = GetDlgItem(IDC_COMBO_WAIT);
		::GetWindowText(hwndL,Buf,254);
		lW = atol(Buf);
		if (lW <= 0 ){
			lW= 1;
		}
		SleepTime = lW*60000;
			CRegisterSave regS;
	         regS.UserKeyStore("TimeOut",&SleepTime,0,CRegisterSave::WRITE);
		return 0;
	}
};

#endif //__CMONITORING_H_
