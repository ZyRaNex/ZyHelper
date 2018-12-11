#include <afxwin.h>
#include <iostream>

#include "Main.h"

#include "tcp_connection.h"
#include "input_simulator.h"
#include "Debug.h"

using namespace std;

CDiabloCalcFancyDlg::CDiabloCalcFancyDlg() :CDialog(CDiabloCalcFancyDlg::IDD) 
{

}

DWORD CDiabloCalcFancyDlg::StartTcpConnection()
{
	tcp_connection.Init();
	tcp_connection.Listen();
	tcp_connection.Exit();
	return 0;
}

DWORD CDiabloCalcFancyDlg::Print()
{
	while (true)
	{
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

		DEBUG_MSG(endl);
		Sleep(1000);
	}
	return 0;
}

DWORD CDiabloCalcFancyDlg::DoLogic()
{
	DWORD WarCryDuration = GetTickCount();
	DWORD BoHDuration = GetTickCount();
	DWORD ConvictionDuration = GetTickCount();

	while (true)
	{
		if (!tcp_connection.IsReady()) continue;

		if (tcp_connection.IsActive())
		{
			m_ctlACTIVE.SetCheck(BST_CHECKED);
		}
		else
		{
			m_ctlACTIVE.SetCheck(BST_UNCHECKED);
			continue;
		}
		
		
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
			if (IPWizInRange && !IPOnCooldown && IpCheck)
			{
				input_simulator.SendKeyOrMouse(IpHotkey);
				Sleep(100);
			}

			//War Cry
			bool WarCryOnCooldown = tcp_connection.WarCryOnCooldown();
			bool NecroInRange = tcp_connection.NecroInRange();;

			if (((!WarCryOnCooldown && (GetTickCount() - 10000 >= WarCryDuration)) ||
				(!WarCryOnCooldown && NecroInRange)) && WcCheck)
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
			if (!EpiphanyOnCooldown && !EpiphanyBuffActive && EpiphanyCheck)
			{
				input_simulator.SendKeyOrMouse(EpiphanyHotkey);
				Sleep(100);
			}

			//Mantra of healing
			bool MantraOfHealingOnCooldown = tcp_connection.MantraOfHealingOnCooldown();
			bool EnoughSpirit = tcp_connection.EnoughSpirit();
			if (!MantraOfHealingOnCooldown && EnoughSpirit && MantraHealingCheck)
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
			bool Range25Enemies10 = tcp_connection.Range25Enemies10();

			if (((BoneArmorAlmostRunningOut && Range25Enemies1) || 
				(!BoneArmorAlmostRunningOut && Range25Enemies10)) && 
				!BoneArmorOnCooldown && BoneArmorCheck)
			{
				input_simulator.SendKeyOrMouse(BoneArmorHotkey);
				Sleep(100);
			}
		}
		Sleep(1);
	}
	return 0;
}

CDiabloCalcFancyDlg::~CDiabloCalcFancyDlg() 
{
#ifdef DEBUG
	FreeConsole();
#endif
	TerminateThread(hThread[0], 0);
	TerminateThread(hThread[1], 0);
	TerminateThread(hThread[2], 0);
}

BOOL CDiabloCalcFancyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

#ifdef DEBUG
	if (!AllocConsole())
	{
		::MessageBox(NULL, _T("Failed to create the console"),
			_T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
	}
	//freopen("CONOUT$", "w", stdout);
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
#endif

	hThread[0] = CreateThread(NULL,0,StaticPrint,(void*)this,0,&dwThreadID[0]);
	hThread[1] = CreateThread(NULL,0,StaticStartTcpConnection,(void*)this,0,&dwThreadID[1]);
	hThread[2] = CreateThread(NULL,0,StaticDoLogic,(void*)this,0,&dwThreadID[2]);


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

END_MESSAGE_MAP()

void CDiabloCalcFancyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ACTIVE, m_ctlACTIVE);

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
}


void CDiabloCalcFancyDlg::Update()
{
	//Reset
	CString Blanc;
	Blanc.Format(_T(""));

	int len;

	CString strText;
	LPTSTR buffer;

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

	DEBUG_MSG("Info Updated");
}

