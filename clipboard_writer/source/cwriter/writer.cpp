#include "writer.h"
#include <vector>
#include "../../converters.h"

using namespace std;

void cWriter::PressKeyB(char mK)
{
	HKL kbl = GetKeyboardLayout(0);
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwFlags = KEYEVENTF_UNICODE;
	if ((int)mK < 65 && (int)mK>90) //for lowercase
	{
		ip.ki.wScan = 0;
		ip.ki.wVk = VkKeyScanEx(mK, kbl);
	}
	else //for uppercase
	{
		if ((int)mK > 0) {
			ip.ki.wScan = mK;
			ip.ki.wVk = 0;
		}
	}
	ip.ki.dwExtraInfo = 0;
	SendInput(1, &ip, sizeof(INPUT));


	ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

}

void cWriter::PressEnter()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwFlags = KEYEVENTF_UNICODE;
	ip.ki.wScan = VK_RETURN; //VK_RETURN is the code of Return key
	ip.ki.wVk = 0;

	ip.ki.dwExtraInfo = 0;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void cWriter::PressTab()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.dwFlags = KEYEVENTF_UNICODE;
	ip.ki.wScan = VK_TAB; //VK_RETURN is the code of Return key
	ip.ki.wVk = 0;

	ip.ki.dwExtraInfo = 0;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

std::wstring cWriter::GetClipboardText()
{
	if (!OpenClipboard(nullptr))
	{
		CloseClipboard();
		return L"";
	}

	HANDLE hData = GetClipboardData(CF_UNICODETEXT);
	if (hData == nullptr)
	{
		CloseClipboard();
		return L"";
	}

	wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
	if (pszText == nullptr)
	{
		CloseClipboard();
		return L"";
	}

	wstring text(pszText);

	GlobalUnlock(hData);
	CloseClipboard();

	return text;
}

void cWriter::CheckStartState() {
	while (true) {
		if ((GetAsyncKeyState(g_Cvars.keyStartWrite) & 0x8000)) {
			this->m_isWriting = true;
		}
		if ((GetAsyncKeyState(g_Cvars.keyStopWrite) & 0x8000)) {
			this->m_isWriting = false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

std::string StringReplacer(const std::string& inputStr, const std::string& src, const std::string& dst)
{
	std::string result(inputStr);

	size_t pos = result.find(src);
	while (pos != std::string::npos) {
		result.replace(pos, src.size(), dst);
		pos = result.find(src, pos);
	}

	return result;
}

std::string Normalize(const std::string& inputStr) {

	string str1 = StringReplacer(inputStr, "    ", "\t");
	string str2 = StringReplacer(str1, "«", "<");
	string str3 = StringReplacer(str2, "»", ">>");
	string str4 = StringReplacer(str3, "\r\n", "\n"); 
	string str5 = StringReplacer(str4, "\r\r", "\n");

	return str5;

}


void cWriter::Start()
{
	std::locale system("");
	std::locale::global(system);
	SetConsoleOutputCP(65001);
	setlocale(LC_ALL, "en_US.UTF-8");
	srand(time(0));
	std::thread keyChecker(&cWriter::CheckStartState, this);

	while (true) {

		if (m_isWriting) {
			int writtenChars = 0;
			int maxWritternChars = 0;
			wstring clipboardText = GetClipboardText();
			string s = UtfConv<std::string>(clipboardText);
			s = Normalize(s);
			for (int i = 0; i < s.length(); i++)
			{
				//mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);

				switch (s[i]) {
				case '\n':
					PressEnter();
					if (g_Cvars.useSmartDelay)
						std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 180 + 350));
					break;
				case '\t':
					PressTab();
					if (g_Cvars.useSmartDelay)
						std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100 + 350));
					break;
				default:
					if (g_Cvars.useSmartDelay) {
						if (maxWritternChars == 0) {
							maxWritternChars = rand() % 10 + 7;
						}
						else {
							if (writtenChars < maxWritternChars) {
								writtenChars++;
								std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100 + 50));
							}
							else {
								maxWritternChars = 0;
								writtenChars = 0;
								std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 200 + 650));
							}
						}
					}

					PressKeyB(s[i]);
					break;
				}

				if (!g_Cvars.useSmartDelay) {
					if (g_Cvars.userRandomDelay) {
						std::this_thread::sleep_for(std::chrono::milliseconds(rand() % g_Cvars.delayRandom + g_Cvars.delay + 1));
					}
					else {
						std::this_thread::sleep_for(std::chrono::milliseconds(g_Cvars.delay));
					}
				}

				if (!m_isWriting)
					break;
			}
			m_isWriting = false;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}