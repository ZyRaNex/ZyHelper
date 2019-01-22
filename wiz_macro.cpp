#include <Windows.h>
#include <tchar.h>

#include "Debug.h"
#include "wiz_macro.h"



WizMacro::WizMacro()
{
	LowerBound = 32000;
	UpperBound = 32000;
	TimeShift = 0;
	AdjustedTime = 0;
	BlackholeCheck = false;
	MacroIsRunning = false;
	DooingArcane = false;
	SavedBlackHole = false;
	AutoMacro = false;
}

void WizMacro::GetCoe(TCPConnection* tcp_connection)
{
	DWORD OldDistance = (UpperBound - LowerBound + 16000) % 16000;
	DWORD Time = GetTickCount() % 16000;
	DWORD Distance = 0;

	if (LowerBound == 32000)
	{
		OldDistance = 100000;
	}
	if (UpperBound == 32000)
	{
		OldDistance = 100000;
	}

	
	if (tcp_connection->ConventionLight())
	{
		Distance = (Time - LowerBound + 32000) % 16000;
		if (Distance < OldDistance)
		{
			UpperBound = (Time + 32000) % 16000;
		}

		Distance = (UpperBound + 4000 - Time + 32000) % 16000;
		if (Distance < OldDistance)
		{
			LowerBound = (Time - 4000 + 32000) % 16000;
		}
	}

	if (tcp_connection->ConventionArcane())
	{
		Distance = (Time - LowerBound - 4000 + 32000) % 16000;
		if (Distance < OldDistance)
		{
			UpperBound = (Time - 4000 + 32000) % 16000;
		}

		Distance = (UpperBound + 8000 - Time + 32000) % 16000;
		if (Distance < OldDistance)
		{
			LowerBound = (Time - 8000 + 32000) % 16000;
		}
	}

	if (tcp_connection->ConventionCold())
	{

		Distance = (Time - LowerBound - 8000 + 32000) % 16000;
		if (Distance < OldDistance)
		{
			UpperBound = (Time - 8000 + 32000) % 16000;
		}

		Distance = (UpperBound + 12000 - Time + 32000) % 16000;
		if (Distance < OldDistance)
		{
			LowerBound = (Time - 12000 + 32000) % 16000;
		}
	}

	if (tcp_connection->ConventionFire())
	{
		Distance = (Time - LowerBound - 12000 + 32000) % 16000;
		if (Distance < OldDistance)
		{
			UpperBound = (Time - 12000 + 32000) % 16000;
		}

		Distance = (UpperBound - Time + 32000) % 16000;
		if (Distance < OldDistance)
		{
			LowerBound = (Time + 32000) % 16000;
		}
	}

	int BoundDistance = abs((int)UpperBound - (int)LowerBound);

	if (BoundDistance > 8000)
	{
		TimeShift = (UpperBound + LowerBound + 16000) / 2;
	}
	else
	{
		TimeShift = (UpperBound + LowerBound) / 2;
	}

	AdjustedTime = (GetTickCount() - TimeShift) % 16000;
}

void WizMacro::DoMacro(InputSimulator* input_simulator, TCPConnection* tcp_connection)
{
	if (WaveOfForceHotkey == 'L' || WaveOfForceHotkey == 'R')
	{
		::MessageBox(NULL, _T("WARNING atm WaveOfForce cant be on the mouse"),
			_T("WARNING"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (ElectrocuteHotkey == 'L' || ElectrocuteHotkey == 'R')
	{
		::MessageBox(NULL, _T("WARNING atm Electrocute cant be on the mouse"),
			_T("WARNING"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (DisintegrateHotkey == 'L' || DisintegrateHotkey == 'R')
	{
		::MessageBox(NULL, _T("WARNING atm Disintegrate cant be on the mouse"),
			_T("WARNING"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (WaveOfForceHotkey == MacroHotkey || ElectrocuteHotkey == MacroHotkey || MeteorHotkey == MacroHotkey || DisintegrateHotkey == MacroHotkey)
	{
		::MessageBox(NULL, _T("WARNING cant have macro key the same as a skill"),
			_T("WARNING"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	if (BlackholeCheck)
	{
		if(GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)))
		{
			if (!MacroIsRunning)//just started
			{
				input_simulator->SendKeyDown(ElectrocuteHotkey);
			}
		}
		else
		{
			if (!AutoMacro)
			{
				if (MacroIsRunning)//just stopped
				{
					input_simulator->SendKeyUp(ElectrocuteHotkey);
					MacroIsRunning = false;
					return;
				}
				else
				{
					return;
				}
			}
		}

		MacroIsRunning = true;

		DWORD Convention = AdjustedTime;
		DooingArcane = false;
		SavedBlackHole = false;
	
		if (Convention > 1150 && Convention < 1900)
		{
			DooingArcane = true;
			input_simulator->SendKey(WaveOfForceHotkey);

			if (tcp_connection->BlackholeBuffActive())
			{
				SavedBlackHole = true;
				//got blackhole from ES so dont use it
			}
			else
			{
				if (BlackholeCheck)
				{
					input_simulator->SendKeyOrMouseWithoutMove(BlackholeHotkey);
				}
			}
			Sleep(200);
			input_simulator->SendKeyDown(ElectrocuteHotkey);
			Sleep(1400);
			input_simulator->SendKeyOrMouseWithoutMove(MeteorHotkey);
			Sleep(1200);

			if (!GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)) && !AutoMacro)
			{
				Stop(input_simulator);
				return;
			}

			if (SavedBlackHole)
			{
				input_simulator->SendKeyUp(ElectrocuteHotkey);
			}

			input_simulator->SendKeyDown(DisintegrateHotkey);
			Sleep(400);
			input_simulator->SendKeyUp(DisintegrateHotkey);

			if (!GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)) && !AutoMacro)
			{
				Stop(input_simulator);
				return;
			}

			if (SavedBlackHole && BlackholeCheck)
			{
				Sleep(300);
				input_simulator->SendKey(WaveOfForceHotkey);
				input_simulator->SendKeyOrMouseWithoutMove(BlackholeHotkey);
				input_simulator->SendKeyDown(ElectrocuteHotkey);
			}
			else
			{
				input_simulator->SendKeyDown(WaveOfForceHotkey);
				Sleep(100);
				input_simulator->SendKeyUp(WaveOfForceHotkey);
				Sleep(200);
			}
			Sleep(1500);
			if (!GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)) && !AutoMacro)
			{
				Stop(input_simulator);
				return;
			}
			input_simulator->SendKeyOrMouseWithoutMove(MeteorHotkey);
			Sleep(1200);
			input_simulator->SendKeyDown(DisintegrateHotkey);
			Sleep(400);
			input_simulator->SendKeyUp(DisintegrateHotkey);
			input_simulator->SendKeyDown(WaveOfForceHotkey);
			Sleep(100);
			input_simulator->SendKeyUp(WaveOfForceHotkey);
		}
		if (Convention > 4000 && Convention < 7000 && !DooingArcane)
		{
			input_simulator->SendKeyOrMouseWithoutMove(MeteorHotkey);
			Sleep(1200);
			if (!GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)) && !AutoMacro)
			{
				Stop(input_simulator);
				return;
			}

			input_simulator->SendKeyDown(DisintegrateHotkey);
			Sleep(400);
			input_simulator->SendKeyUp(DisintegrateHotkey);
			input_simulator->SendKeyDown(WaveOfForceHotkey);
			Sleep(100);
			input_simulator->SendKeyUp(WaveOfForceHotkey);
		}
		else if (Convention > 9300 && Convention < 10300)
		{
			input_simulator->SendKeyOrMouseWithoutMove(MeteorHotkey);
			Sleep(1200);
			if (!GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)) && !AutoMacro)
			{
				Stop(input_simulator);
				return;
			}
			input_simulator->SendKeyDown(DisintegrateHotkey);
			Sleep(400);
			input_simulator->SendKeyUp(DisintegrateHotkey);
			input_simulator->SendKeyDown(WaveOfForceHotkey);
			Sleep(100);
			input_simulator->SendKeyUp(WaveOfForceHotkey);
		}
		else if (Convention > 12200 && Convention < 13200)
		{
			input_simulator->SendKeyOrMouseWithoutMove(MeteorHotkey);
			Sleep(1200);
			if (!GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)) && !AutoMacro)
			{
				Stop(input_simulator);
				return;
			}
			input_simulator->SendKeyDown(DisintegrateHotkey);
			Sleep(400);
			input_simulator->SendKeyUp(DisintegrateHotkey);
			input_simulator->SendKeyDown(WaveOfForceHotkey);
			Sleep(100);
			input_simulator->SendKeyUp(WaveOfForceHotkey);
		}
		else if (Convention > 15100)
		{
			input_simulator->SendKeyOrMouseWithoutMove(MeteorHotkey);
			Sleep(1200);
			if (!GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)) && !AutoMacro)
			{
				Stop(input_simulator);
				return;
			}
			input_simulator->SendKeyDown(DisintegrateHotkey);
			Sleep(400);
			input_simulator->SendKeyUp(DisintegrateHotkey);
			input_simulator->SendKeyUp(ElectrocuteHotkey);
		}
	}
	else
	{
		if (GetAsyncKeyState(input_simulator->CharToVK(MacroHotkey)))
		{
			input_simulator->SendKeyOrMouseWithoutMove(MeteorHotkey);
			Sleep(1200);
			input_simulator->SendKeyDown(DisintegrateHotkey);
			Sleep(500);
			input_simulator->SendKeyDown(WaveOfForceHotkey);
			input_simulator->SendKeyUp(DisintegrateHotkey);
			Sleep(100);
			input_simulator->SendKeyUp(WaveOfForceHotkey);
			Sleep(800);
		}
	}
}

void WizMacro::Stop(InputSimulator* input_simulator)
{
	if (MacroIsRunning)
	{
		input_simulator->SendKeyUp(ElectrocuteHotkey);
		MacroIsRunning = false;	
	}
	return;
}

WizMacro::~WizMacro()
{
}
