﻿// DesktopLricsFix.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <tchar.h>
#include <iostream>

int main()
{
	std::cout << "Netease CloudMusic Destop Lrics Capture Fix\n";
	std::cout << "网易云音乐桌面歌词捕获修复\n";
	std::cout << "作者：Shugen (https://github.com/shugen002) \n";
	std::cout << "欢迎关注作者B站：https://space.bilibili.com/2304086\n";
	std::cout << "注意：任务栏中出现一个无法关闭的“桌面歌词”属正常现象\n";
	std::cout << "开始查找桌面歌词窗口\n";
	HWND window_handle = NULL;
	DWORD dwProcId = 0;
	TCHAR buffer[MAX_PATH] = { 0 };
#ifdef UNICODE
	int size = MultiByteToWideChar(CP_ACP, 0, "cloudmusic.exe", -1, NULL, 0);
	TCHAR* ncm_process_name = new TCHAR[size];
	MultiByteToWideChar(CP_ACP, 0, "cloudmusic.exe", -1, ncm_process_name, size);
#else
	TCHAR* ncm_process_name = _strdup("cloudmusic.exe");
#endif
	while (window_handle == NULL) {
		window_handle = FindWindow(NULL, L"桌面歌词");
		if (window_handle != NULL) {
			GetWindowThreadProcessId(window_handle, &dwProcId);
			HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
			GetModuleFileName((HMODULE)hProc, buffer, MAX_PATH);
			CloseHandle(hProc);
#ifdef UNICODE
			if (!wcscmp(ncm_process_name, buffer)) {
#else
			if (!strcmp(ncm_process_name, buffer)) {
#endif
				std::cout << "存在其他名为桌面歌词的窗口，请先暂时关闭。\n";
				window_handle = NULL;
				Sleep(3000);
			}
		}
		else
		{
			Sleep(1000);
		}

	}
	std::cout << "捕捉到窗口句柄 " << window_handle << "\n";
	LONG_PTR current_style = GetWindowLongPtr(window_handle, GWL_EXSTYLE);
	std::cout << "当前窗口样式 " << current_style << "\n";
	if (current_style & WS_EX_TOOLWINDOW) {
		std::cout << "检测到 WS_EX_TOOLWINDOW 样式，尝试移除。" << "\n";
		SetWindowLongPtr(window_handle, GWL_EXSTYLE, current_style ^ WS_EX_TOOLWINDOW);
		std::cout << "已移除 WS_EX_TOOLWINDOW 样式，请在OBS中使用窗口捕获中的“Windows 10 (1903及以上版本)”方式捕获“桌面歌词”窗口" << "\n";
		std::cout << "再次提醒，任务栏中出现一个无法关闭的“桌面歌词”属正常现象" << "\n";
	}
	else {
		std::cout << "未检测到 WS_EX_TOOLWINDOW 样式，退出。" << "\n";
	}
	std::cout << "按任意键退出...";
	std::cin.get();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
