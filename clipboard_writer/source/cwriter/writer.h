#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <thread>
#include "../cvars/cvars.h"

class cWriter 
{
private:
	bool m_isWriting = false;

	void PressEnter();
	void PressTab();
	void PressKeyB(char mK);
	void CheckStartState();
	std::wstring GetClipboardText();

public:
	void Start();
};