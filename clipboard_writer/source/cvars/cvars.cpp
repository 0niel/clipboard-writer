#include "cvars.h"
#include "../settings/settings.h"

#pragma warning (disable: 4244) 

cCvars g_Cvars;

void cCvars::Load()
{
	if (!g_Settings.bFileExists(g_Settings.IniFile))
		return;

	const char *Section = "Settings";

	//g_Cvars.ESPEnabled = atoi(g_Settings.Read(g_Settings.IniFile, Section, "GlowEnabled", "0"));
	//g_Cvars.GlowTeammates = atoi(g_Settings.Read(g_Settings.IniFile, Section, "DrawTeam", "0"));

	//g_Cvars.col[0] = atof(g_Settings.Read(g_Settings.IniFile, Section, "EnemyGlowR", "0"));
	//g_Cvars.col[1] = atof(g_Settings.Read(g_Settings.IniFile, Section, "EnemyGlowG", "0"));
	//g_Cvars.col[2] = atof(g_Settings.Read(g_Settings.IniFile, Section, "EnemyGlowB", "0"));
	//g_Cvars.col[3] = atof(g_Settings.Read(g_Settings.IniFile, Section, "EnemyGlowA", "0"));

	//g_Cvars.colorTeam[0] = atof(g_Settings.Read(g_Settings.IniFile, Section, "TeamGlowR", "0"));
	//g_Cvars.colorTeam[1] = atof(g_Settings.Read(g_Settings.IniFile, Section, "TeamGlowG", "0"));
	//g_Cvars.colorTeam[2] = atof(g_Settings.Read(g_Settings.IniFile, Section, "TeamGlowB", "0"));
	//g_Cvars.colorTeam[3] = atof(g_Settings.Read(g_Settings.IniFile, Section, "TeamGlowA", "0"));

	//g_Cvars.TriggerEnabled = atof(g_Settings.Read(g_Settings.IniFile, Section, "Triggerbot", "0"));
	//g_Cvars.TeammatesEnabled = atof(g_Settings.Read(g_Settings.IniFile, Section, "TriggerTeam", "0"));
	//g_Cvars.TriggerbotKeyId = atof(g_Settings.Read(g_Settings.IniFile, Section, "TriggerbotKey", "0"));
	//g_Cvars.TriggerbotBoneAllWeapons = atof(g_Settings.Read(g_Settings.IniFile, Section, "TriggerbotBone", "0"));
	//g_Cvars.TriggerbotEnableAwait = atof(g_Settings.Read(g_Settings.IniFile, Section, "TriggerbotAwaitEnabled", "0"));
	//g_Cvars.TriggerbotAwait = atof(g_Settings.Read(g_Settings.IniFile, Section, "TriggerbotAwait", "0"));

	//g_Cvars.FullCompensationEnable = atof(g_Settings.Read(g_Settings.IniFile, Section, "FullCompensationEnable", "0"));

	//g_Cvars.RadarHackEnabled = atof(g_Settings.Read(g_Settings.IniFile, Section, "Radarhack", "0"));

	//g_Cvars.AutoPistolEnabled = atof(g_Settings.Read(g_Settings.IniFile, Section, "AutoPistolEnabled", "0"));
	//g_Cvars.AutoPistolKeyId = atof(g_Settings.Read(g_Settings.IniFile, Section, "AutoPistolKey", "0"));
}

void cCvars::Save()
{
	const char *Section = "Settings";
	char s[32];

	//g_Settings.Write(g_Settings.IniFile, Section, "GlowEnabled", g_Settings.dtoa(s, g_Cvars.ESPEnabled));
	//g_Settings.Write(g_Settings.IniFile, Section, "DrawTeam", g_Settings.dtoa(s, g_Cvars.GlowTeammates));

	//g_Settings.Write(g_Settings.IniFile, Section, "EnemyGlowR", g_Settings.dtoa(s, g_Cvars.col[0]));
	//g_Settings.Write(g_Settings.IniFile, Section, "EnemyGlowG", g_Settings.dtoa(s, g_Cvars.col[1]));
	//g_Settings.Write(g_Settings.IniFile, Section, "EnemyGlowB", g_Settings.dtoa(s, g_Cvars.col[2]));
	//g_Settings.Write(g_Settings.IniFile, Section, "EnemyGlowA", g_Settings.dtoa(s, g_Cvars.col[3]));

	//g_Settings.Write(g_Settings.IniFile, Section, "TeamGlowR", g_Settings.dtoa(s, g_Cvars.colorTeam[0]));
	//g_Settings.Write(g_Settings.IniFile, Section, "TeamGlowG", g_Settings.dtoa(s, g_Cvars.colorTeam[1]));
	//g_Settings.Write(g_Settings.IniFile, Section, "TeamGlowB", g_Settings.dtoa(s, g_Cvars.colorTeam[2]));
	//g_Settings.Write(g_Settings.IniFile, Section, "TeamGlowA", g_Settings.dtoa(s, g_Cvars.colorTeam[3]));

	//g_Settings.Write(g_Settings.IniFile, Section, "Triggerbot", g_Settings.dtoa(s, g_Cvars.TriggerEnabled));
	//g_Settings.Write(g_Settings.IniFile, Section, "TriggerTeam", g_Settings.dtoa(s, g_Cvars.TeammatesEnabled));
	//g_Settings.Write(g_Settings.IniFile, Section, "TriggerbotKey", g_Settings.dtoa(s, g_Cvars.TriggerbotKeyId));
	//g_Settings.Write(g_Settings.IniFile, Section, "TriggerbotBone", g_Settings.dtoa(s, g_Cvars.TriggerbotBoneAllWeapons));
	//g_Settings.Write(g_Settings.IniFile, Section, "TriggerbotAwaitEnabled", g_Settings.dtoa(s, g_Cvars.TriggerbotEnableAwait));
	//g_Settings.Write(g_Settings.IniFile, Section, "TriggerbotAwait", g_Settings.dtoa(s, g_Cvars.TriggerbotAwait));

	//g_Settings.Write(g_Settings.IniFile, Section, "FullCompensationEnable", g_Settings.dtoa(s, g_Cvars.FullCompensationEnable));

	//g_Settings.Write(g_Settings.IniFile, Section, "Radarhack", g_Settings.dtoa(s, g_Cvars.RadarHackEnabled));

	//g_Settings.Write(g_Settings.IniFile, Section, "AutoPistolEnabled", g_Settings.dtoa(s, g_Cvars.AutoPistolEnabled));
	//g_Settings.Write(g_Settings.IniFile, Section, "AutoPistolKey", g_Settings.dtoa(s, g_Cvars.AutoPistolKeyId));
}
