
#include <windows.h>
#include "win_lcd.h"
#include "lcd.h"
#include "lcd_conf.h"
#include "gui.h"
#include "stdio.h"
#include "tty.h"
#include "win_key.h"

static HWND g_hwnd;
tty_t tty;
win_key key;
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
    case WM_CHAR:
    {
        char ch = (char)w;
        win_key_isr(&key,ch);
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
        //lcd_clear(0x202020);
    gui_init(0,0xFF0000,0x202020,0);
    //gui_draw_line(10,0,100);
    while (1)
    {
        // /* 模拟 MCU GUI 刷新 */
        // lcd_draw_pixel(10 + x, 20, 0xFF0000);
        // lcd_draw_pixel(10, 20 + x, 0x00FF00);

        // x = (x + 1) % 200;

        // /* 请求刷新窗口（注意：不是直接画） */
        tty_display(&tty);
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
        LCD_WIDTH + 100,
        LCD_HEIGHT + 80,
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
    tty_init(&tty);
    win_key_init(&key,tty_rx_callback,&tty);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
