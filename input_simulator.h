#pragma once

#ifndef INPUT_SIMULATOR_H_
#define INPUT_SIMULATOR_H_


enum MouseClick {Left, Right};

class InputSimulator
{
public:
	InputSimulator();
	int CharToVK(wchar_t input);
	void SendKeyOrMouse(wchar_t input);
	void SendKeyOrMouseWithoutMove(wchar_t input);
	void SendKey(int key);
	void SendKey(wchar_t key);
	void SendKeyDown(int key);
	void SendKeyDown(wchar_t key);
	void SendKeyUp(int key);
	void SendKeyUp(wchar_t key);
	void SendMouse(MouseClick Click);
	void SendMouseWithoutMove(MouseClick Click);

	~InputSimulator();
};

#endif  // INPUT_SIMULATOR_H_