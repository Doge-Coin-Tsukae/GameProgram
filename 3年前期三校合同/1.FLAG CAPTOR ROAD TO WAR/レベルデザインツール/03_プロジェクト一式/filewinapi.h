#pragma once

int __stdcall BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
bool GetDir(HWND hWnd, TCHAR* def_dir, TCHAR* path);
