#include <afxwin.h>
#include <iostream>


#include "Main.h"

#include "tcp_connection.h"
#include "input_simulator.h"
#include "Debug.h"

CDiabloCalcFancyDlg::CDiabloCalcFancyDlg() :CDialog(CDiabloCalcFancyDlg::IDD) 
{

}

DWORD CDiabloCalcFancyDlg::StartTcpConnectionThread()
{
	DEBUG_MSG("tcp start" << std::endl);
	tcp_connection.Init();
	DEBUG_MSG("tcp init" << std::endl);
	tcp_connection.Listen();
	DEBUG_MSG("tcp listen" << std::endl);
	tcp_connection.Exit();
	DEBUG_MSG("tcp start" << std::endl);
	Sleep(10);
	return 0;
}

DWORD CDiabloCalcFancyDlg::PrintThread()
{
	while (true)
	{
		Sleep(1000);

		if (!tcp_connection.IsReady()) continue;

		for (int i = 0; i < 8; i++)
		{
			DEBUG_MSG(tcp_connection.ElementAt(i, 1) << " ");
		}
		DEBUG_MSG(" ");
		for (int i = 0; i < 8; i++)
		{
			DEBUG_MSG(tcp_connection.ElementAt(i, 2) << " ");
		}
		DEBUG_MSG(" ");
		for (int i = 0; i < 8; i++)
		{
			DEBUG_MSG(tcp_connection.ElementAt(i, 3) << " ");
		}
		DEBUG_MSG(" ");
		for (int i = 0; i < 8; i++)
		{
			DEBUG_MSG(tcp_connection.ElementAt(i, 4) << " ");
		}
		DEBUG_MSG(" ");
		for (int i = 0; i < 8; i++)
		{
			DEBUG_MSG(tcp_connection.ElementAt(i, 5) << " ");
		}
		DEBUG_MSG(" ");
		for (int i = 0; i < 8; i++)
		{
			DEBUG_MSG(tcp_connection.ElementAt(i, 6) << " ");
		}

		DEBUG_MSG(std::endl);
	}
	return 0;
}

DWORD CDiabloCalcFancyDlg::DoLogicThread()
{
	DWORD WarCryDuration = GetTickCount();
	DWORD BoHDuration = GetTickCount();
	DWORD ConvictionDuration = GetTickCount();
	DWORD ActiveDuration = GetTickCount();
	DWORD ResetDuration = GetTickCount();
	DWORD AutoMacroDuration = GetTickCount();
	DWORD EpiphanyDuration = GetTickCount();

	while (true)
	{
		Sleep(10);
		if (GetAsyncKeyState(VK_F10) && (GetTickCount() - 500 >= ActiveDuration))
		{
			ActiveDuration = GetTickCount();
			Active = !Active;

			wiz_macro.AutoMacro = false;
			input_simulator.SendKeyUp(ElectrocuteHotkey);
			m_ctlMACROACTIVE.SetCheck(BST_UNCHECKED);
		}

		if (GetAsyncKeyState(input_simulator.CharToVK('6')) && (GetTickCount() - 500 >= ResetDuration))
		{
			ResetDuration = GetTickCount();
			wiz_macro.LowerBound = 32000;
			wiz_macro.UpperBound = 32000;
		}

		
		if (!tcp_connection.IsReady()) continue;

		if (tcp_connection.IsActive() && Active)
		{
			m_ctlACTIVE.SetCheck(BST_CHECKED);
		}
		else
		{
			m_ctlACTIVE.SetCheck(BST_UNCHECKED);
			continue;
		}

		if (GetAsyncKeyState(input_simulator.CharToVK('8')) && (GetTickCount() - 500 >= AutoMacroDuration))
		{
			AutoMacroDuration = GetTickCount();

			if (wiz_macro.AutoMacro)
			{
				wiz_macro.AutoMacro = false;
				input_simulator.SendKeyUp(ElectrocuteHotkey);
				m_ctlMACROACTIVE.SetCheck(BST_UNCHECKED);
			}
			else
			{
				input_simulator.SendKeyDown(ElectrocuteHotkey);
				wiz_macro.AutoMacro = true;
				m_ctlMACROACTIVE.SetCheck(BST_CHECKED);
			}
		}

		HWND handle = ::GetForegroundWindow();
		int capacity = ::GetWindowTextLength(handle) * 2;
		wchar_t NewName[128];
		::GetWindowText(handle, NewName, 128);
		if (wcscmp(NewName, _T("Diablo III")) != 0) continue;


		

		bool UsePotion = tcp_connection.UsePotion();
		bool PotionIsOnCooldown = tcp_connection.PotionIsOnCooldown();
		if (UsePotion && !PotionIsOnCooldown && PotionCheck)
		{
			input_simulator.SendKeyOrMouse(PotionHotkey);
			Sleep(100);
		}

		if (tcp_connection.ImBarb())
		{
			//Ignore Pain
			bool IPWizInRange = tcp_connection.WizInRange();
			bool IPOnCooldown = tcp_connection.IPOnCooldown();
			bool BossIsSpawned = tcp_connection.BossIsSpawned();
			bool NecroInIPRange = tcp_connection.NecroInIPRange();

			if (!BossIsSpawned && IPWizInRange && !IPOnCooldown && IpCheck ||
				 BossIsSpawned && NecroInIPRange && !IPOnCooldown && IpCheck)
			{
				input_simulator.SendKeyOrMouse(IpHotkey);
				Sleep(100);
			}

			//War Cry
			bool WarCryOnCooldown = tcp_connection.WarCryOnCooldown();
			bool NecroInWCRange = tcp_connection.NecroInWCRange();

			if (((!WarCryOnCooldown && (GetTickCount() - 10000 >= WarCryDuration)) ||
				(!WarCryOnCooldown && NecroInWCRange)) && WcCheck)
			{
				input_simulator.SendKeyOrMouse(WcHotkey);
				WarCryDuration = GetTickCount();
				Sleep(100);
			}

			//Falter
			bool FalterOnCooldown = tcp_connection.FalterOnCooldown();
			bool WizInRange = tcp_connection.WizInRange();
			if (WizInRange && !FalterOnCooldown && FalterCheck)
			{
				input_simulator.SendKeyOrMouse(FalterHotkey);
				Sleep(100);
			}

			//Berserker
			bool BerserkerOnCooldown = tcp_connection.BerserkerOnCooldown();
			bool BerserkerBuffActive = tcp_connection.BerserkerBuffActive();
			if (!BerserkerOnCooldown && !BerserkerBuffActive && BerserkerCheck)
			{
				input_simulator.SendKeyOrMouse(BerserkerHotkey);
				Sleep(100);
			}

			//Sprint
			bool SprintOnCooldown = tcp_connection.SprintOnCooldown();
			bool EnoughFury = tcp_connection.EnoughFury();
			bool SprintBuffActive = tcp_connection.SprintBuffActive();
			if (!SprintOnCooldown && EnoughFury && !SprintBuffActive && SprintCheck)
			{
				input_simulator.SendKeyOrMouse(SprintHotkey);
				Sleep(100);
			}
		}

		if (tcp_connection.ImMonk())
		{
			//Epiphany
			bool EpiphanyOnCooldown = tcp_connection.EpiphanyOnCooldown();
			bool EpiphanyBuffActive = tcp_connection.EpiphanyBuffActive();
			if (!EpiphanyOnCooldown && (!EpiphanyBuffActive || (GetTickCount() - 14500 >= EpiphanyDuration)) && EpiphanyCheck)
			{
				input_simulator.SendKeyOrMouse(EpiphanyHotkey);
				EpiphanyDuration = GetTickCount();
				Sleep(100);
			}

			//Mantra of healing
			bool MantraOfHealingOnCooldown = tcp_connection.MantraOfHealingOnCooldown();
			bool EnoughSpirit = tcp_connection.EnoughSpirit();
			bool ShiftPressed = GetAsyncKeyState(VK_SHIFT);
			bool SpacePressed = GetAsyncKeyState(VK_SPACE);
			if (!MantraOfHealingOnCooldown && EnoughSpirit && MantraHealingCheck && (ShiftPressed || SpacePressed))
			{
				input_simulator.SendKeyOrMouse(MantraHealingHotkey);
				Sleep(100);
			}

			//Sweeping Wind
			bool RecastSweepingWind = tcp_connection.RecastSweepingWind();
			EnoughSpirit = tcp_connection.EnoughSpirit();
			if (RecastSweepingWind && EnoughSpirit && SweepingWindCheck)
			{
				input_simulator.SendKeyOrMouse(SweepingWindHotkey);
				Sleep(100);
			}

			//Breath of Heaven
			bool BohOnCooldown = tcp_connection.BohOnCooldown();
			if (!BohOnCooldown && (GetTickCount() - 3000 >= BoHDuration) && BohCheck)
			{
				input_simulator.SendKeyOrMouse(BohHotkey);
				BoHDuration = GetTickCount();
				Sleep(100);
			}

			//Mantra of Conviction
			EnoughSpirit = tcp_connection.EnoughSpirit();
			if (EnoughSpirit && (GetTickCount() - 3000 >= ConvictionDuration) && MantraConvictionCheck)
			{
				input_simulator.SendKeyOrMouse(MantraConvictionHotkey);
				ConvictionDuration = GetTickCount();
				Sleep(100);
			}
		}

		if (tcp_connection.ImWizard())
		{
			//Storm Armor
			bool StormArmorOnCooldown = tcp_connection.StormArmorOnCooldown();
			bool StormArmorBuffActive = tcp_connection.StormArmorBuffActive();

			if (!StormArmorOnCooldown && !StormArmorBuffActive && StormArmorCheck)
			{
				input_simulator.SendKeyOrMouse(StormArmorHotkey);
				Sleep(100);
			}

			//Magic Weapon
			bool MagicWeaponOnCooldown = tcp_connection.MagicWeaponOnCooldown();
			bool MagicWeaponBuffActive = tcp_connection.MagicWeaponBuffActive();

			if (!MagicWeaponOnCooldown && !MagicWeaponBuffActive && MagicWeaponCheck)
			{
				input_simulator.SendKeyOrMouse(MagicWeaponHotkey);
				Sleep(100);
			}
		}

		if (tcp_connection.ImNecro())
		{
			//Land of the Dead
			bool LotDOnCooldown = tcp_connection.LotDOnCooldown();
			bool LotDBuffActive = tcp_connection.LotDBuffActive();

			if (!LotDOnCooldown && !LotDBuffActive && LotdCheck)
			{
				input_simulator.SendKeyOrMouse(LotdHotkey);
				Sleep(100);
			}

			//Bone Armor
			bool BoneArmorAlmostRunningOut = tcp_connection.BoneArmorAlmostRunningOut();
			bool BoneArmorOnCooldown = tcp_connection.BoneArmorOnCooldown();
			bool Range25Enemies1 = tcp_connection.Range25Enemies1();
			bool Range25Enemies5 = tcp_connection.Range25Enemies5();

			if (((BoneArmorAlmostRunningOut && Range25Enemies1) || 
				(!BoneArmorAlmostRunningOut && Range25Enemies5)) && 
				!BoneArmorOnCooldown && BoneArmorCheck)
			{
				input_simulator.SendKeyOrMouse(BoneArmorHotkey);
				Sleep(100);
			}
		}
		
	}
	return 0;
}

DWORD CDiabloCalcFancyDlg::CoeReaderThread()
{
	CString OutputTextUpperBound;
	CString OutputTextLowerBound;
	CString OutputTextTime;
	CString OutputTextCoe;

	while (true)
	{
		Sleep(127);
		if (!tcp_connection.IsReady())
		{
			Sleep(100);
			continue;
		}
		if (!tcp_connection.IsActive() || !Active)
		{
			Sleep(100);
			continue;
		}
		if (!tcp_connection.ImWizard())
		{
			Sleep(1000);
			continue;
		}
		if (!MacroCheck)
		{
			Sleep(100);
			continue;
		}

		wiz_macro.GetCoe(&tcp_connection);

		OutputTextUpperBound.Format(_T("%d"), wiz_macro.UpperBound);
		OutputTextLowerBound.Format(_T("%d"), wiz_macro.LowerBound);
		OutputTextTime.Format(_T("%d"), wiz_macro.AdjustedTime);
		OutputTextCoe.Format(_T("%d %d %d %d"), tcp_connection.ConventionLight(), tcp_connection.ConventionArcane(), tcp_connection.ConventionCold(), tcp_connection.ConventionFire());

		m_ctlUPPERBOUND.SetSel(0, -1);
		m_ctlUPPERBOUND.ReplaceSel(OutputTextUpperBound);
		m_ctlLOWERBOUND.SetSel(0, -1);
		m_ctlLOWERBOUND.ReplaceSel(OutputTextLowerBound);
		m_ctlTIME.SetSel(0, -1);
		m_ctlTIME.ReplaceSel(OutputTextTime);
		m_ctlCOE.SetSel(0, -1);
		m_ctlCOE.ReplaceSel(OutputTextCoe);

	}
	return 0;
}

DWORD CDiabloCalcFancyDlg::WizMacroThread()
{
	while (true)
	{
		Sleep(10);
		if (!tcp_connection.IsReady())
		{
			wiz_macro.Stop(&input_simulator);
			Sleep(100);
			continue;
		}
		if (!tcp_connection.IsActive() || !Active)
		{
			wiz_macro.Stop(&input_simulator);
			Sleep(100);
			continue;
		}
		if (!tcp_connection.ImWizard())
		{
			wiz_macro.Stop(&input_simulator);
			Sleep(1000);
			continue;
		}
		if (!MacroCheck)
		{
			wiz_macro.Stop(&input_simulator);
			Sleep(100);
			continue;
		}

		wiz_macro.DoMacro(&input_simulator, &tcp_connection);
	}
	return 0;
}

DWORD CDiabloCalcFancyDlg::GenerateInput()
{
	while (true)
	{
		Sleep(10);
		if (!tcp_connection.IsReady())
		{
			Sleep(100);
			continue;
		}
		if (!tcp_connection.IsActive() || !Active)
		{
			Sleep(100);
			continue;
		}
		HWND handle = ::GetForegroundWindow();
		int capacity = ::GetWindowTextLength(handle) * 2;
		wchar_t NewName[128];
		::GetWindowText(handle, NewName, 128);
		if (wcscmp(NewName, _T("Diablo III")) != 0) continue;
		input_simulator.GenerateInput();
	}
	return 0;
}

CDiabloCalcFancyDlg::~CDiabloCalcFancyDlg() 
{
#ifdef DEBUG
	FreeConsole();
	TerminateThread(hThread[0], 0);
#endif
	TerminateThread(hThread[1], 0);
	TerminateThread(hThread[2], 0);
	TerminateThread(hThread[3], 0);
	TerminateThread(hThread[4], 0);
}

BOOL CDiabloCalcFancyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	Active = true;

#ifdef DEBUG
	if (!AllocConsole())
	{
		::MessageBox(NULL, _T("Failed to create the console"),
			_T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}
	//freopen("CONOUT$", "w", stdout);
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	hThread[0] = CreateThread(NULL,0,StaticPrint,(void*)this,0,&dwThreadID[0]);
	if (!hThread[0])
	{
		::MessageBox(NULL, _T("Failed to create the print thread"),
			_T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}
#endif


	hThread[1] = CreateThread(NULL, 0, StaticStartTcpConnection, (void*)this, 0, &dwThreadID[1]);
	hThread[2] = CreateThread(NULL, 0, StaticDoLogic, (void*)this, 0, &dwThreadID[2]);
	hThread[3] = CreateThread(NULL, 0, StaticCoeReader, (void*)this, 0, &dwThreadID[3]);
	hThread[4] = CreateThread(NULL, 0, StaticWizMacro, (void*)this, 0, &dwThreadID[4]);
	hThread[5] = CreateThread(NULL, 0, StaticGenerateInput, (void*)this, 0, &dwThreadID[5]);

	if (!hThread[1] || !hThread[2] || !hThread[3] || !hThread[4])
	{
		::MessageBox(NULL, _T("Failed to create a thread"),
			_T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}

	m_ctlIPCHECK.SetCheck(BST_CHECKED);
	m_ctlWCCHECK.SetCheck(BST_CHECKED);
	m_ctlFALTERCHECK.SetCheck(BST_CHECKED);
	m_ctlBERSERKERCHECK.SetCheck(BST_CHECKED);
	m_ctlSPRINTCHECK.SetCheck(BST_UNCHECKED);
	m_ctlEPIPHANYCHECK.SetCheck(BST_CHECKED);
	m_ctlMANTRAHEALINGCHECK.SetCheck(BST_UNCHECKED);
	m_ctlSWEEPINGWINDCHECK.SetCheck(BST_UNCHECKED);
	m_ctlBOHCHECK.SetCheck(BST_UNCHECKED);
	m_ctlMANTRACONVICTIONCHECK.SetCheck(BST_UNCHECKED);
	m_ctlLANDOFTHEDEADCHECK.SetCheck(BST_CHECKED);
	m_ctlBONEARMORCHECK.SetCheck(BST_UNCHECKED);
	m_ctlPOTIONCHECK.SetCheck(BST_CHECKED);
	m_ctlMACROCHECK.SetCheck(BST_CHECKED);
	m_ctlBLACKHOLECHECK.SetCheck(BST_CHECKED);
	m_ctlSTORMARMORCHECK.SetCheck(BST_UNCHECKED);
	m_ctlMAGICWEAPONCHECK.SetCheck(BST_UNCHECKED);
	m_ctlMACROACTIVE.SetCheck(BST_UNCHECKED);

	m_ctlIPHOTKEY.SetWindowText(_T("R"));
	m_ctlWCHOTKEY.SetWindowText(_T("4"));
	m_ctlFALTERHOTKEY.SetWindowText(_T("L"));
	m_ctlBERSERKERHOTKEY.SetWindowText(_T("1"));
	m_ctlSPRINTHOTKEY.SetWindowText(_T("1"));
	m_ctlEPIPHANYHOTKEY.SetWindowText(_T("R"));
	m_ctlMANTRAHEALINGHOTKEY.SetWindowText(_T("4"));
	m_ctlSWEEPINGWINDHOTKEY.SetWindowText(_T("4"));
	m_ctlBOHHOTKEY.SetWindowText(_T("2"));
	m_ctlMANTRACONVICTIONHOTKEY.SetWindowText(_T("1"));
	m_ctlLANDOFTHEDEADHOTKEY.SetWindowText(_T("1"));
	m_ctlBONEARMORHOTKEY.SetWindowText(_T("R"));
	m_ctlPOTIONHOTKEY.SetWindowText(_T("q"));
	m_ctlWAVEOFFORCEHOTKEY.SetWindowText(_T("1"));
	m_ctlELECTROCUTEHOTKEY.SetWindowText(_T("2"));
	m_ctlMETEORHOTKEY.SetWindowText(_T("3"));
	m_ctlDISINTEGRATEHOTKEY.SetWindowText(_T("4"));
	m_ctlBLACKHOLEHOTKEY.SetWindowText(_T("R"));
	m_ctlSTORMARMORHOTKEY.SetWindowText(_T("L"));
	m_ctlMAGICWEAPONHOTKEY.SetWindowText(_T("R"));

	return TRUE;
}

BOOL CDiabloCalcFancy::InitInstance() 
{
	CDiabloCalcFancyDlg myDlg;
	m_pMainWnd = &myDlg;
	myDlg.DoModal();

	return TRUE;
}

CDiabloCalcFancy MyApp;

BEGIN_MESSAGE_MAP(CDiabloCalcFancyDlg, CDialog)
	ON_BN_CLICKED(IDC_IPCHECK, Update)
	ON_BN_CLICKED(IDC_WCCHECK, Update)
	ON_BN_CLICKED(IDC_FALTERCHECK, Update)
	ON_BN_CLICKED(IDC_BERSERKERCHECK, Update)
	ON_BN_CLICKED(IDC_SPRINTCHECK, Update)
	ON_BN_CLICKED(IDC_EPIPHANYCHECK, Update)
	ON_BN_CLICKED(IDC_MANTRAHEALINGCHECK, Update)
	ON_BN_CLICKED(IDC_SWEEPINGWINDCHECK, Update)
	ON_BN_CLICKED(IDC_BOHCHECK, Update)
	ON_BN_CLICKED(IDC_MANTRACONVICTIONCHECK, Update)
	ON_BN_CLICKED(IDC_LANDOFTHEDEADCHECK, Update)
	ON_BN_CLICKED(IDC_BONEARMORCHECK, Update)
	ON_BN_CLICKED(IDC_POTIONCHECK, Update)
	ON_BN_CLICKED(IDC_MACROCHECK, Update)
	ON_BN_CLICKED(IDC_BLACKHOLECHECK, Update)
	ON_BN_CLICKED(IDC_STORMARMORCHECK, Update)
	ON_BN_CLICKED(IDC_MAGICWEAPONCHECK, Update)

	ON_EN_CHANGE(IDC_IPHOTKEY, Update)
	ON_EN_CHANGE(IDC_WCHOTKEY, Update)
	ON_EN_CHANGE(IDC_FALTERHOTKEY, Update)
	ON_EN_CHANGE(IDC_BERSERKERHOTKEY, Update)
	ON_EN_CHANGE(IDC_SPRINTHOTKEY, Update)
	ON_EN_CHANGE(IDC_EPIPHANYHOTKEY, Update)
	ON_EN_CHANGE(IDC_MANTRAHEALINGHOTKEY, Update)
	ON_EN_CHANGE(IDC_SWEEPINGWINDHOTKEY, Update)
	ON_EN_CHANGE(IDC_BOHHOTKEY, Update)
	ON_EN_CHANGE(IDC_MANTRACONVICTIONHOTKEY, Update)
	ON_EN_CHANGE(IDC_LANDOFTHEDEADHOTKEY, Update)
	ON_EN_CHANGE(IDC_BONEARMORHOTKEY, Update)
	ON_EN_CHANGE(IDC_POTIONTHOTKEY, Update)
	ON_EN_CHANGE(IDC_WAVEOFFORCEHOTKEY, Update)
	ON_EN_CHANGE(IDC_ELECTROCUTEHOTKEY, Update)
	ON_EN_CHANGE(IDC_METEORHOTKEY, Update)
	ON_EN_CHANGE(IDC_DISINTEGRATEHOTKEY, Update)
	ON_EN_CHANGE(IDC_BLACKHOLEHOTKEY, Update)
	ON_EN_CHANGE(IDC_STORMARMORHOTKEY, Update)
	ON_EN_CHANGE(IDC_MAGICWEAPONHOTKEY, Update)

END_MESSAGE_MAP()

void CDiabloCalcFancyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ACTIVE, m_ctlACTIVE);
	DDX_Control(pDX, IDC_MACROACTIVE, m_ctlMACROACTIVE);

	DDX_Control(pDX, IDC_IPCHECK, m_ctlIPCHECK);
	DDX_Control(pDX, IDC_WCCHECK, m_ctlWCCHECK);
	DDX_Control(pDX, IDC_FALTERCHECK, m_ctlFALTERCHECK);
	DDX_Control(pDX, IDC_BERSERKERCHECK, m_ctlBERSERKERCHECK);
	DDX_Control(pDX, IDC_SPRINTCHECK, m_ctlSPRINTCHECK);
	DDX_Control(pDX, IDC_EPIPHANYCHECK, m_ctlEPIPHANYCHECK);
	DDX_Control(pDX, IDC_MANTRAHEALINGCHECK, m_ctlMANTRAHEALINGCHECK);
	DDX_Control(pDX, IDC_SWEEPINGWINDCHECK, m_ctlSWEEPINGWINDCHECK);
	DDX_Control(pDX, IDC_BOHCHECK, m_ctlBOHCHECK);
	DDX_Control(pDX, IDC_MANTRACONVICTIONCHECK, m_ctlMANTRACONVICTIONCHECK);
	DDX_Control(pDX, IDC_LANDOFTHEDEADCHECK, m_ctlLANDOFTHEDEADCHECK);
	DDX_Control(pDX, IDC_BONEARMORCHECK, m_ctlBONEARMORCHECK);
	DDX_Control(pDX, IDC_POTIONCHECK, m_ctlPOTIONCHECK);
	DDX_Control(pDX, IDC_MACROCHECK, m_ctlMACROCHECK);
	DDX_Control(pDX, IDC_BLACKHOLECHECK, m_ctlBLACKHOLECHECK);
	DDX_Control(pDX, IDC_STORMARMORCHECK, m_ctlSTORMARMORCHECK);
	DDX_Control(pDX, IDC_MAGICWEAPONCHECK, m_ctlMAGICWEAPONCHECK);

	DDX_Control(pDX, IDC_IPHOTKEY, m_ctlIPHOTKEY);
	DDX_Control(pDX, IDC_WCHOTKEY, m_ctlWCHOTKEY);
	DDX_Control(pDX, IDC_FALTERHOTKEY, m_ctlFALTERHOTKEY);
	DDX_Control(pDX, IDC_BERSERKERHOTKEY, m_ctlBERSERKERHOTKEY);
	DDX_Control(pDX, IDC_SPRINTHOTKEY, m_ctlSPRINTHOTKEY);
	DDX_Control(pDX, IDC_EPIPHANYHOTKEY, m_ctlEPIPHANYHOTKEY);
	DDX_Control(pDX, IDC_MANTRAHEALINGHOTKEY, m_ctlMANTRAHEALINGHOTKEY);
	DDX_Control(pDX, IDC_SWEEPINGWINDHOTKEY, m_ctlSWEEPINGWINDHOTKEY);
	DDX_Control(pDX, IDC_BOHHOTKEY, m_ctlBOHHOTKEY);
	DDX_Control(pDX, IDC_MANTRACONVICTIONHOTKEY, m_ctlMANTRACONVICTIONHOTKEY);
	DDX_Control(pDX, IDC_LANDOFTHEDEADHOTKEY, m_ctlLANDOFTHEDEADHOTKEY);
	DDX_Control(pDX, IDC_BONEARMORHOTKEY, m_ctlBONEARMORHOTKEY);
	DDX_Control(pDX, IDC_POTIONTHOTKEY, m_ctlPOTIONHOTKEY);
	DDX_Control(pDX, IDC_WAVEOFFORCEHOTKEY, m_ctlWAVEOFFORCEHOTKEY);
	DDX_Control(pDX, IDC_ELECTROCUTEHOTKEY, m_ctlELECTROCUTEHOTKEY);
	DDX_Control(pDX, IDC_METEORHOTKEY, m_ctlMETEORHOTKEY);
	DDX_Control(pDX, IDC_DISINTEGRATEHOTKEY, m_ctlDISINTEGRATEHOTKEY);
	DDX_Control(pDX, IDC_BLACKHOLEHOTKEY, m_ctlBLACKHOLEHOTKEY);
	DDX_Control(pDX, IDC_STORMARMORHOTKEY, m_ctlSTORMARMORHOTKEY);
	DDX_Control(pDX, IDC_MAGICWEAPONHOTKEY, m_ctlMAGICWEAPONHOTKEY);

	DDX_Control(pDX, IDC_UPPERBOUND, m_ctlUPPERBOUND);
	DDX_Control(pDX, IDC_LOWERBOUND, m_ctlLOWERBOUND);
	DDX_Control(pDX, IDC_TIME, m_ctlTIME);
	DDX_Control(pDX, IDC_COE, m_ctlCOE);

}


void CDiabloCalcFancyDlg::Update()
{
	//Reset
	CString Blanc;
	Blanc.Format(_T(""));
	int len;
	CString strText;
	LPTSTR buffer;



	IpCheck = m_ctlIPCHECK.GetCheck();
	WcCheck = m_ctlWCCHECK.GetCheck();
	FalterCheck = m_ctlFALTERCHECK.GetCheck();
	BerserkerCheck = m_ctlBERSERKERCHECK.GetCheck();
	SprintCheck = m_ctlSPRINTCHECK.GetCheck();
	EpiphanyCheck = m_ctlEPIPHANYCHECK.GetCheck();
	MantraHealingCheck = m_ctlMANTRAHEALINGCHECK.GetCheck();
	SweepingWindCheck = m_ctlSWEEPINGWINDCHECK.GetCheck();
	BohCheck = m_ctlBOHCHECK.GetCheck();
	MantraConvictionCheck = m_ctlMANTRACONVICTIONCHECK.GetCheck();
	LotdCheck = m_ctlLANDOFTHEDEADCHECK.GetCheck();
	BoneArmorCheck = m_ctlBONEARMORCHECK.GetCheck();
	PotionCheck = m_ctlPOTIONCHECK.GetCheck();
	MacroCheck = m_ctlMACROCHECK.GetCheck();
	BlackholeCheck = m_ctlBLACKHOLECHECK.GetCheck();
	StormArmorCheck = m_ctlSTORMARMORCHECK.GetCheck();
	MagicWeaponCheck = m_ctlMAGICWEAPONCHECK.GetCheck();

	wiz_macro.BlackholeCheck = BlackholeCheck;

	len = m_ctlIPHOTKEY.LineLength(m_ctlIPHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlIPHOTKEY.GetLine(0, buffer, len);
		IpHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		IpHotkey = ' ';
	}

	len = m_ctlWCHOTKEY.LineLength(m_ctlWCHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlWCHOTKEY.GetLine(0, buffer, len);
		WcHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		WcHotkey = ' ';
	}

	len = m_ctlFALTERHOTKEY.LineLength(m_ctlFALTERHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlFALTERHOTKEY.GetLine(0, buffer, len);
		FalterHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		FalterHotkey = ' ';
	}

	len = m_ctlBERSERKERHOTKEY.LineLength(m_ctlBERSERKERHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlBERSERKERHOTKEY.GetLine(0, buffer, len);
		BerserkerHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		BerserkerHotkey = ' ';
	}

	len = m_ctlSPRINTHOTKEY.LineLength(m_ctlSPRINTHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlSPRINTHOTKEY.GetLine(0, buffer, len);
		SprintHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		SprintHotkey = ' ';
	}

	len = m_ctlEPIPHANYHOTKEY.LineLength(m_ctlEPIPHANYHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlEPIPHANYHOTKEY.GetLine(0, buffer, len);
		EpiphanyHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		EpiphanyHotkey = ' ';
	}

	len = m_ctlMANTRAHEALINGHOTKEY.LineLength(m_ctlMANTRAHEALINGHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlMANTRAHEALINGHOTKEY.GetLine(0, buffer, len);
		MantraHealingHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		MantraHealingHotkey = ' ';
	}

	len = m_ctlSWEEPINGWINDHOTKEY.LineLength(m_ctlSWEEPINGWINDHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlSWEEPINGWINDHOTKEY.GetLine(0, buffer, len);
		SweepingWindHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		SweepingWindHotkey = ' ';
	}

	len = m_ctlBOHHOTKEY.LineLength(m_ctlBOHHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlBOHHOTKEY.GetLine(0, buffer, len);
		BohHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		BohHotkey = ' ';
	}

	len = m_ctlMANTRACONVICTIONHOTKEY.LineLength(m_ctlMANTRACONVICTIONHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlMANTRACONVICTIONHOTKEY.GetLine(0, buffer, len);
		MantraConvictionHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		MantraConvictionHotkey = ' ';
	}

	len = m_ctlLANDOFTHEDEADHOTKEY.LineLength(m_ctlLANDOFTHEDEADHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlLANDOFTHEDEADHOTKEY.GetLine(0, buffer, len);
		LotdHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		LotdHotkey = ' ';
	}

	len = m_ctlBONEARMORHOTKEY.LineLength(m_ctlBONEARMORHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlBONEARMORHOTKEY.GetLine(0, buffer, len);
		BoneArmorHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		BoneArmorHotkey = ' ';
	}

	len = m_ctlPOTIONHOTKEY.LineLength(m_ctlPOTIONHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlPOTIONHOTKEY.GetLine(0, buffer, len);
		PotionHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		PotionHotkey = ' ';
	}

	len = m_ctlWAVEOFFORCEHOTKEY.LineLength(m_ctlWAVEOFFORCEHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlWAVEOFFORCEHOTKEY.GetLine(0, buffer, len);
		WaveOfForceHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		WaveOfForceHotkey = ' ';
	}

	len = m_ctlELECTROCUTEHOTKEY.LineLength(m_ctlELECTROCUTEHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlELECTROCUTEHOTKEY.GetLine(0, buffer, len);
		ElectrocuteHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		ElectrocuteHotkey = ' ';
	}

	len = m_ctlMETEORHOTKEY.LineLength(m_ctlMETEORHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlMETEORHOTKEY.GetLine(0, buffer, len);
		MeteorHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		MeteorHotkey = ' ';
	}

	len = m_ctlDISINTEGRATEHOTKEY.LineLength(m_ctlDISINTEGRATEHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlDISINTEGRATEHOTKEY.GetLine(0, buffer, len);
		DisintegrateHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		DisintegrateHotkey = ' ';
	}

	len = m_ctlBLACKHOLEHOTKEY.LineLength(m_ctlBLACKHOLEHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlBLACKHOLEHOTKEY.GetLine(0, buffer, len);
		BlackholeHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		BlackholeHotkey = ' ';
	}

	len = m_ctlSTORMARMORHOTKEY.LineLength(m_ctlSTORMARMORHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlSTORMARMORHOTKEY.GetLine(0, buffer, len);
		StormArmorHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		StormArmorHotkey = ' ';
	}

	len = m_ctlMAGICWEAPONHOTKEY.LineLength(m_ctlMAGICWEAPONHOTKEY.LineIndex(0));
	if (len > 0)
	{
		buffer = strText.GetBuffer(len);
		m_ctlMAGICWEAPONHOTKEY.GetLine(0, buffer, len);
		MagicWeaponHotkey = strText[0];
		strText.ReleaseBuffer(len);
	}
	else
	{
		MagicWeaponHotkey = ' ';
	}


	wiz_macro.WaveOfForceHotkey = WaveOfForceHotkey;
	wiz_macro.ElectrocuteHotkey = ElectrocuteHotkey;
	wiz_macro.MeteorHotkey = MeteorHotkey;
	wiz_macro.DisintegrateHotkey = DisintegrateHotkey;
	wiz_macro.BlackholeHotkey = BlackholeHotkey;

	DEBUG_MSG("Info Updated" << std::endl);
}

