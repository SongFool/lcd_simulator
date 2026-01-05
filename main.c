
#include <windows.h>
#include "win_lcd.h"
#include "lcd.h"
#include "lcd_conf.h"

static HWND g_hwnd;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        win_lcd_flush(hdc);
        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, w, l);
}

DWORD WINAPI gui_thread(LPVOID param)
{
    HWND hwnd = (HWND)param;

    lcd_clear(0x202020);

    int x = 0;

    while (1)
    {
        /* 模拟 MCU GUI 刷新 */
        lcd_draw_pixel(10 + x, 20, 0xFF0000);
        lcd_draw_pixel(10, 20 + x, 0x00FF00);

        x = (x + 1) % 200;

        /* 请求刷新窗口（注意：不是直接画） */
        InvalidateRect(hwnd, NULL, FALSE);

        Sleep(16);   // ~60Hz，≈ SysTick
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)

{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "LCD_SIM";

    RegisterClass(&wc);

    g_hwnd = CreateWindow(
        "LCD_SIM",
        "MCU LCD Simulator",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
        100, 100,
        600,
        450,
        NULL, NULL, hInst, NULL
    );

    ShowWindow(g_hwnd, SW_SHOW);

    win_lcd_init(g_hwnd);
    lcd_init();
    CreateThread(
        NULL,
        0,
        gui_thread,
        g_hwnd,
        0,
        NULL
    );

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
