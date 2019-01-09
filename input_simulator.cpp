#include "input_simulator.h"

#include <Windows.h>
#include <queue>

#include "Debug.h"

InputSimulator::InputSimulator()
{
}

int InputSimulator::CharToVK(wchar_t input)
{
	switch (input)
	{
	case '1':
		return 0x31;
		break;
	case '2':
		return 0x32;
		break;
	case '3':
		return 0x33;
		break;
	case '4':
		return 0x34;
		break;
	case '5':
		return 0x35;
		break;
	case '6':
		return 0x36;
		break;
	case '7':
		return 0x37;
		break;
	case '8':
		return 0x38;
		break;
	case '9':
		return 0x39;
		break;
	case 'q':
		return 0x51;
		break;
	case 'w':
		return 0x57;
		break;
	case 'e':
		return 0x45;
		break;
	case 'r':
		return 0x52;
		break;
	case 'a':
		return 0x41;
		break;
	case 's':
		return 0x53;
		break;
	case 'd':
		return 0x44;
		break;
	case 'f':
		return 0x46;
		break;
	}
	return 0;
}

void InputSimulator::SendKeyOrMouse(wchar_t input)
{
	switch (input) 
	{
	  case 'L':
		SendMouse(Left);
		break;
	  case 'R':
	 	SendMouse(Right);
		break;
	  default:
		  SendKey(input);
		break;
	}
}

void InputSimulator::SendKeyOrMouseWithoutMove(wchar_t input)
{
	switch (input)
	{
	case 'L':
		SendMouseWithoutMove(Left);
		break;
	case 'R':
		SendMouseWithoutMove(Right);
		break;
	default:
		SendKey(input);
		break;
	}
}

void InputSimulator::SendKey(int key)
{
	Input input;
	input.VkKey = key;
	input.type = VkKey;

	inputmutex.lock();
	InputQueue.push(input);
	inputmutex.unlock();
}

void InputSimulator::SendKey(wchar_t key)
{
	Input input;
	input.key = key;
	input.type = Key;

	inputmutex.lock();
	InputQueue.push(input);
	inputmutex.unlock();
}

void InputSimulator::SendKeyDown(int key)
{
	Input input;
	input.VkKey = key;
	input.type = VkKeyDown;

	inputmutex.lock();
	InputQueue.push(input);
	inputmutex.unlock();
}

void InputSimulator::SendKeyDown(wchar_t key)
{
	Input input;
	input.key = key;
	input.type = KeyDown;

	inputmutex.lock();
	InputQueue.push(input);
	inputmutex.unlock();
}

void InputSimulator::SendKeyUp(int key)
{
	Input input;
	input.VkKey = key;
	input.type = VkKeyUp;

	inputmutex.lock();
	InputQueue.push(input);
	inputmutex.unlock();
}

void InputSimulator::SendKeyUp(wchar_t key)
{
	Input input;
	input.key = key;
	input.type = KeyUp;

	inputmutex.lock();
	InputQueue.push(input);
	inputmutex.unlock();
}

void InputSimulator::SendMouse(MouseClick Click)
{
	Input input;
	input.type = Mouse;
	input.Click = Click;

	inputmutex.lock();
	InputQueue.push(input);
	inputmutex.unlock();
}

void InputSimulator::SendMouseWithoutMove(MouseClick Click)
{
	
}

void InputSimulator::GenerateInput()
{
	bool inputwaiting = false;
	inputmutex.lock();
	inputwaiting = !InputQueue.empty();
	inputmutex.unlock();

	if (inputwaiting)
	{
		Input data;
		inputmutex.lock();
		data = InputQueue.front();
		InputQueue.pop();
		inputmutex.unlock();

		DEBUG_MSG("Sending Input " << data.type << " " << data.key << " " << data.VkKey << std::endl);
		INPUT ip;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		ip.ki.dwFlags = 0;

		switch(data.type)
		{
		case Key:
			ip.type = INPUT_KEYBOARD;
			ip.ki.wVk = CharToVK(data.key);
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
			break;

		case VkKey:
			ip.type = INPUT_KEYBOARD;
			ip.ki.wVk = data.VkKey;
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
			break;

		case KeyDown:
			ip.type = INPUT_KEYBOARD;
			ip.ki.wVk = CharToVK(data.key);
			SendInput(1, &ip, sizeof(INPUT));
			break;

		case VkKeyDown:
			ip.type = INPUT_KEYBOARD;
			ip.ki.wVk = data.VkKey;
			SendInput(1, &ip, sizeof(INPUT));
			break;

		case KeyUp:
			ip.type = INPUT_KEYBOARD;
			ip.ki.wVk = CharToVK(data.key);
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
			break;

		case VkKeyUp:
			ip.type = INPUT_KEYBOARD;
			ip.ki.wVk = data.VkKey;
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
			break;

		case Mouse:
			if (data.Click == Left)
			{
				INPUT ipShift;
				ipShift.ki.wScan = 0;
				ipShift.ki.time = 0;
				ipShift.ki.dwExtraInfo = 0;
				ipShift.ki.dwFlags = 0;
				ipShift.type = INPUT_KEYBOARD;
				ipShift.ki.wVk = VK_SHIFT;
				SendInput(1, &ipShift, sizeof(INPUT));
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

			if (data.Click == Left)
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
			if (data.Click == Left)
			{
				ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			}
			else
			{
				ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			}
			SendInput(1, &ip, sizeof(INPUT));

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

			if (data.Click == Left)
			{
				INPUT ipShift;
				ipShift.ki.wScan = 0;
				ipShift.ki.time = 0;
				ipShift.ki.dwExtraInfo = 0;
				ipShift.type = INPUT_KEYBOARD;
				ipShift.ki.dwFlags = KEYEVENTF_KEYUP;
				ipShift.ki.wVk = VK_SHIFT;
				SendInput(1, &ipShift, sizeof(INPUT));
			}
			break;
		case MouseWithoutMove:
			INPUT ip;

			if (data.Click == Left)
			{
				INPUT ipShift;
				ipShift.ki.wScan = 0;
				ipShift.ki.time = 0;
				ipShift.ki.dwExtraInfo = 0;
				ipShift.ki.dwFlags = 0;
				ipShift.type = INPUT_KEYBOARD;
				ipShift.ki.wVk = VK_SHIFT;
				SendInput(1, &ipShift, sizeof(INPUT));
			}


			ZeroMemory(&ip, sizeof(ip));

			Sleep(1);

			ip.type = INPUT_MOUSE;
			ip.mi.dx = 0;
			ip.mi.dy = 0;
			ip.mi.mouseData = 0;
			ip.mi.time = 0;
			ip.mi.dwExtraInfo = 0;

			if (data.Click == Left)
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
			if (data.Click == Left)
			{
				ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			}
			else
			{
				ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			}
			SendInput(1, &ip, sizeof(INPUT));

			Sleep(1);

			if (data.Click == Left)
			{
				INPUT ipShift;
				ipShift.ki.wScan = 0;
				ipShift.ki.time = 0;
				ipShift.ki.dwExtraInfo = 0;
				ipShift.type = INPUT_KEYBOARD;
				ipShift.ki.dwFlags = KEYEVENTF_KEYUP;
				ipShift.ki.wVk = VK_SHIFT;
				SendInput(1, &ipShift, sizeof(INPUT));
			}
			break;
		}
	}
}

InputSimulator::~InputSimulator()
{
}
