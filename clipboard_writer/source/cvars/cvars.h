#pragma once

class cCvars
{
private:
public:
	int keyStartWrite, keyStopWrite;
	int delay;
	int delayRandom;
	bool userRandomDelay;
	bool useSmartDelay;
	bool bigDataInsert;

	void Load();
	void Save();

};
extern cCvars g_Cvars;

