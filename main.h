#pragma once

#ifndef MAIN_H_
#define MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#include <afxwin.h>

#include "resource.h"
#include "wiz_macro.h"
#include "tcp_connection.h"
#include "input_simulator.h"


class CDiabloCalcFancy : public CWinApp {
public:
	BOOL InitInstance();
};

class CDiabloCalcFancyDlg : public CDialog {
public:
	enum { IDD = IDD_DIALOG1 };
	CButton m_ctlACTIVE;
	CButton m_ctlMACROACTIVE;

	CButton	m_ctlIPCHECK;
	CButton m_ctlWCCHECK;
	CButton m_ctlFALTERCHECK;
	CButton m_ctlBERSERKERCHECK;
	CButton m_ctlSPRINTCHECK;
	CButton m_ctlEPIPHANYCHECK;
	CButton m_ctlMANTRAHEALINGCHECK;
	CButton m_ctlSWEEPINGWINDCHECK;
	CButton m_ctlBOHCHECK;
	CButton m_ctlMANTRACONVICTIONCHECK;
	CButton m_ctlLANDOFTHEDEADCHECK;
	CButton m_ctlBONEARMORCHECK;
	CButton m_ctlPOTIONCHECK;
	CButton m_ctlMACROCHECK;
	CButton m_ctlBLACKHOLECHECK;
	CButton m_ctlSTORMARMORCHECK;
	CButton m_ctlMAGICWEAPONCHECK;

	CEdit m_ctlIPHOTKEY;
	CEdit m_ctlWCHOTKEY;
	CEdit m_ctlFALTERHOTKEY;
	CEdit m_ctlBERSERKERHOTKEY;
	CEdit m_ctlSPRINTHOTKEY;
	CEdit m_ctlEPIPHANYHOTKEY;
	CEdit m_ctlMANTRAHEALINGHOTKEY;
	CEdit m_ctlSWEEPINGWINDHOTKEY;
	CEdit m_ctlBOHHOTKEY;
	CEdit m_ctlMANTRACONVICTIONHOTKEY;
	CEdit m_ctlLANDOFTHEDEADHOTKEY;
	CEdit m_ctlBONEARMORHOTKEY;
	CEdit m_ctlPOTIONHOTKEY;
	CEdit m_ctlWAVEOFFORCEHOTKEY;
	CEdit m_ctlELECTROCUTEHOTKEY;
	CEdit m_ctlMETEORHOTKEY;
	CEdit m_ctlDISINTEGRATEHOTKEY;
	CEdit m_ctlBLACKHOLEHOTKEY;
	CEdit m_ctlSTORMARMORHOTKEY;
	CEdit m_ctlMAGICWEAPONHOTKEY;

	CEdit m_ctlUPPERBOUND;
	CEdit m_ctlLOWERBOUND;
	CEdit m_ctlTIME;
	CEdit m_ctlCOE;


	CDiabloCalcFancyDlg();
	static DWORD WINAPI StaticStartTcpConnection(void* Param)
	{
		CDiabloCalcFancyDlg* This = (CDiabloCalcFancyDlg*)Param;
		return This->StartTcpConnectionThread();
	}
	static DWORD WINAPI StaticPrint(void* Param)
	{
		CDiabloCalcFancyDlg* This = (CDiabloCalcFancyDlg*)Param;
		return This->PrintThread();
	}
	static DWORD WINAPI StaticDoLogic(void* Param)
	{
		CDiabloCalcFancyDlg* This = (CDiabloCalcFancyDlg*)Param;
		return This->DoLogicThread();
	}
	static DWORD WINAPI StaticCoeReader(void* Param)
	{
		CDiabloCalcFancyDlg* This = (CDiabloCalcFancyDlg*)Param;
		return This->CoeReaderThread();
	}
	static DWORD WINAPI StaticWizMacro(void* Param)
	{
		CDiabloCalcFancyDlg* This = (CDiabloCalcFancyDlg*)Param;
		return This->WizMacroThread();
	}
	DWORD StartTcpConnectionThread();
	DWORD PrintThread();
	DWORD DoLogicThread();
	DWORD CoeReaderThread();
	DWORD WizMacroThread();
	~CDiabloCalcFancyDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	TCPConnection tcp_connection;
	InputSimulator input_simulator;
	WizMacro wiz_macro;

	HANDLE hThread[6];
	DWORD dwThreadID[6];

	bool Active;

	bool IpCheck;
	bool WcCheck;
	bool FalterCheck;
	bool BerserkerCheck;
	bool SprintCheck;
	bool EpiphanyCheck;
	bool MantraHealingCheck;
	bool SweepingWindCheck;
	bool BohCheck;
	bool MantraConvictionCheck;
	bool LotdCheck;
	bool BoneArmorCheck;
	bool PotionCheck;
	bool MacroCheck;
	bool BlackholeCheck;
	bool StormArmorCheck;
	bool MagicWeaponCheck;
	

	wchar_t IpHotkey;
	wchar_t WcHotkey;
	wchar_t FalterHotkey;
	wchar_t BerserkerHotkey;
	wchar_t SprintHotkey;
	wchar_t EpiphanyHotkey;
	wchar_t MantraHealingHotkey;
	wchar_t SweepingWindHotkey;
	wchar_t BohHotkey;
	wchar_t MantraConvictionHotkey;
	wchar_t LotdHotkey;
	wchar_t BoneArmorHotkey;
	wchar_t PotionHotkey;
	wchar_t WaveOfForceHotkey;
	wchar_t ElectrocuteHotkey;
	wchar_t MeteorHotkey;
	wchar_t DisintegrateHotkey;
	wchar_t BlackholeHotkey;
	wchar_t StormArmorHotkey;
	wchar_t MagicWeaponHotkey;

	void Update();
};


#endif  // MAIN_H_