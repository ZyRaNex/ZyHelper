#pragma once

#ifndef INPUT_SIMULATOR_H_
#define INPUT_SIMULATOR_H_


enum MouseClick {Left, Right};

class InputSimulator
{
public:
	InputSimulator();
	void SendKeyOrMouse(wchar_t input);
	void SendKey(int key);
	void SendMouse(MouseClick Click);
	~InputSimulator();
};

#endif  // INPUT_SIMULATOR_H_