#pragma once

#include "common.h"

namespace StdClr { enum {
    black   = 0x000000,
    maroon  = 0x000080,
    green   = 0x008000,
    olive   = 0x008080,
    navy    = 0x800000,
    purple  = 0x800080,
    teal    = 0x808000,
    silver  = 0xc0c0c0,
    gray    = 0x808080,
    red     = 0x0000ff,
    lime    = 0x00ff00,
    yellow  = 0x00ffff,
    blue    = 0xff0000,
    magenta = 0xff00ff,
    cyan    = 0xffff00,
    white   = 0xffffff,
}; }

bool IsWndRectEmpty(HWND hWnd);
HWND GetNonChildParent(HWND hWnd);
HWND GetTopParent(HWND hWnd);
bool IsProgManWnd(HWND hWnd);
bool IsTaskBar(HWND hWnd);
bool IsTopMost(HWND hWnd);
void Error(HWND hWnd, const ef::tchar* s);
void Warning(HWND hWnd, const ef::tchar* s);
bool GetScrSize(SIZE& szScr);

inline bool strmatch(const ef::tchar* s1, const ef::tchar* s2)
{
    return _tcscmp(s1, s2) == 0;
}

inline bool strimatch(const ef::tchar* s1, const ef::tchar* s2)
{
    return _tcsicmp(s1, s2) == 0;
}

HRGN MakeRegionFromBmp(HBITMAP hBmp, COLORREF clrMask);
void PinWindow(HWND hWnd, HWND hHitWnd, int trackRate, bool silent = false);
void TogglePin(HWND hWnd, HWND hTarget, int trackRate);

HMENU LoadLocalizedMenu(LPCTSTR lpMenuName);
HMENU LoadLocalizedMenu(WORD id);
int   LocalizedDialogBoxParam(LPCTSTR lpTemplateName, HWND hWndParent, 
                              DLGPROC lpDialogFunc, LPARAM dwInitParam);
int   LocalizedDialogBoxParam(WORD id, HWND hWndParent, 
                              DLGPROC lpDialogFunc, LPARAM dwInitParam);
HWND  CreateLocalizedDialog  (LPCTSTR lpTemplate, HWND hWndParent, 
                              DLGPROC lpDialogFunc);
HWND  CreateLocalizedDialog  (WORD id, HWND hWndParent, 
                              DLGPROC lpDialogFunc);


bool RectContains(const RECT& rc1, const RECT& rc2);
void EnableGroup(HWND hWnd, int id, bool mode);

std::vector<ef::tstring> GetFiles(ef::tstring mask);


COLORREF Light(COLORREF clr);
COLORREF Dark(COLORREF clr);


// automatically handles language
class ResStr {
public:
    ResStr(DWORD id, int bufLen = 256) {
        str = new ef::tchar[bufLen];
        if (!app.hResMod || !LoadString(app.hResMod, id, str, bufLen))
            LoadString(app.hInst, id, str, bufLen);
    }

    ResStr(DWORD id, int bufLen, DWORD p1) {
        initFmt(id, bufLen, &p1);
    }

    ResStr(DWORD id, int bufLen, DWORD p1, DWORD p2) {
        DWORD params[] = {p1,p2};
        initFmt(id, bufLen, params);
    }

    ResStr(DWORD id, int bufLen, DWORD p1, DWORD p2, DWORD p3) {
        DWORD params[] = {p1,p2,p3};
        initFmt(id, bufLen, params);
    }

    ResStr(DWORD id, int bufLen, DWORD* params) {
        initFmt(id, bufLen, params);
    }

    ResStr(const ResStr& other)
    {
        const size_t buflen = _tcslen(other.str) + 1;
        str = new ef::tchar[buflen];
        _tcscpy_s(str, buflen, other.str);
    }

    ResStr& operator=(const ResStr& other)
    {
        if (*this != other) {
            delete[] str;
            const size_t buflen = _tcslen(other.str) + 1;
            str = new ef::tchar[buflen];
            _tcscpy_s(str, buflen, other.str);
        }
    }

    ~ResStr() {
        delete[] str;
    }

    operator const ef::tchar*() const {
        return str;
    }

    operator ef::tchar*() {
        return str;
    }

protected:
    void initFmt(DWORD id, int bufLen, DWORD* params) {
        str = new ef::tchar[bufLen];
        if (!app.hResMod || !LoadString(app.hResMod, id, str, bufLen))
            LoadString(app.hInst, id, str, bufLen);

        DWORD flags = FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY;
        va_list* va = reinterpret_cast<va_list*>(params);
        if (!FormatMessage(flags, tstring(str).c_str(), 0, 0, str, bufLen, va))
            *str = 0;
    }

private:
    ef::tchar* str;

};


BOOL MoveWindow(HWND hWnd, const RECT& rc, BOOL repaint = TRUE);
BOOL Rectangle(HDC hDC, const RECT& rc);


bool PSChanged(HWND hPage);
ef::tstring RemAccel(ef::tstring s);

bool getBmpSize(HBITMAP hBmp, SIZE& sz);

bool remapBmpColors(HBITMAP hBmp, COLORREF clrs[][2], int cnt);


ef::tstring substrAfterLast(const ef::tstring& s, const ef::tstring& delim);
