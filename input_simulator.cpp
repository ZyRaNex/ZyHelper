#include "input_simulator.h"

#include <Windows.h>

InputSimulator::InputSimulator()
{
}

void InputSimulator::SendKeyOrMouse(wchar_t input)
{
	switch (input) 
	{
	  case '1': 
		SendKey(0x31);
		break;
	  case '2':
		SendKey(0x32);
		break;
	  case '3':
		SendKey(0x33);
		break;
	  case '4':
		SendKey(0x34);
		break;
	  case '5':
		SendKey(0x35);
		break;
	  case '6':
		SendKey(0x36);
		break;
	  case 'q':
		  SendKey(0x51);
		  break;
	  case 'w':
		  SendKey(0x57);
		  break;
	  case 'e':
		  SendKey(0x45);
		  break;
	  case 'r':
		  SendKey(0x52);
		  break;
	  case 'L':
		SendMouse(Left);
		break;
	  case 'R':
	 	SendMouse(Right);
		break;
	  default:
		break;
	}
}

void InputSimulator::SendKey(int key)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void InputSimulator::SendMouse(MouseClick Click)
{
	INPUT ip;

	if (Click == Left)//hold force stand still
	{
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		ip.ki.wVk = VK_SHIFT;
		ip.ki.dwFlags = 0;
		SendInput(1, &ip, sizeof(INPUT));
	}


	ZeroMemory(&ip, sizeof(ip));

	POINT CursorPos;
	GetCursorPos(&CursorPos);

	Sleep(1);

	ip.type = INPUT_MOUSE;
	ip.mi.dx = (700 + 1) * (65535 / GetSystemMetrics(SM_CXSCREEN));
	ip.mi.dy = (500 + 1) * (65535 / GetSystemMetrics(SM_CYSCREEN));
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
	ip.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(1);

	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;

	if (Click == Left)
	{
		ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	}
	else
	{
		ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	}
	SendInput(1, &ip, sizeof(INPUT));


	Sleep(1);

	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
	if (Click == Left)
	{
		ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	}
	else
	{
		ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	}
	SendInput(1, &ip, sizeof(INPUT));
	// Set up a generic keyboard event.

	Sleep(1);

	ip.type = INPUT_MOUSE;
	ip.mi.dx = (CursorPos.x + 3) * (65535 / GetSystemMetrics(SM_CXSCREEN));
	ip.mi.dy = (CursorPos.y + 5) * (65535 / GetSystemMetrics(SM_CYSCREEN));
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
	ip.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(1);

	if (Click == Left)//hold force stand still
	{
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		ip.ki.wVk = VK_SHIFT;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}
}

InputSimulator::~InputSimulator()
{
}
