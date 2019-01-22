#pragma once

#ifndef WIZ_MACRO_H_
#define WIZ_MACRO_H_

#include "tcp_connection.h"
#include "input_simulator.h"

class WizMacro
{
public:
	WizMacro();
	void GetCoe(TCPConnection* tcp_connection);
	void DoMacro(InputSimulator* input_simulator, TCPConnection* tcp_connection);
	void Stop(InputSimulator* input_simulator);
	~WizMacro();

	DWORD LowerBound;
	DWORD UpperBound;
	DWORD TimeShift;
	DWORD AdjustedTime;

	wchar_t WaveOfForceHotkey;
	wchar_t ElectrocuteHotkey;
	wchar_t MeteorHotkey;
	wchar_t DisintegrateHotkey;
	wchar_t BlackholeHotkey;
	wchar_t MacroHotkey;

	bool BlackholeCheck;
	bool MacroIsRunning;

	bool DooingArcane;
	bool SavedBlackHole;

	bool AutoMacro;
};

#endif  // WIZ_MACRO_H_