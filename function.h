#ifndef EATBOX_FUNCTION_H
#define EATBOX_FUNCTION_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "data.h"

// FUNGSI UTILITY DASAR
void gotoxy(int x, int y)
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD kor = {x, y};
    SetConsoleCursorPosition(move, kor);
}
int consoleW() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
int consoleH() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void appname(int x, int y)
{
    gotoxy(x, y  ); printf("███████╗ █████╗ ████████╗██████╗  ██████╗ ██╗  ██╗");
    gotoxy(x, y+1); printf("██╔════╝██╔══██╗╚══██╔══╝██╔══██╗██╔═══██╗╚██╗██╔╝");
    gotoxy(x, y+2); printf("█████╗  ███████║   ██║   ██████╔╝██║   ██║ ╚███╔╝ ");
    gotoxy(x, y+3); printf("██╔══╝  ██╔══██║   ██║   ██╔══██╗██║   ██║ ██╔██╗ ");
    gotoxy(x, y+4); printf("███████╗██║  ██║   ██║   ██████╔╝╚██████╔╝██╔╝ ██╗");
    gotoxy(x, y+5); printf("╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═════╝  ╚═════╝ ╚═╝  ╚═╝");
}
void logname(int x, int y)
{
    gotoxy(x, y  ); printf(" ____ ____ ____ ____ ____ ");
    gotoxy(x, y+1); printf("││M │││A │││S │││U │││K ││");
    gotoxy(x, y+2); printf("││__│││__│││__│││__│││__││");
    gotoxy(x, y+3); printf("│╱__╲│╱__╲│╱__╲│╱__╲│╱__╲│");
}

// ILANGIN SCROLL
void Borderless() {
    HWND console = GetConsoleWindow();

    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(console, GWL_STYLE, style);

    HMONITOR monitor = MonitorFromWindow(console, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(monitor, &mi);

    SetWindowPos(console, HWND_TOP,
        mi.rcMonitor.left,
        mi.rcMonitor.top,
        mi.rcMonitor.right - mi.rcMonitor.left,
        mi.rcMonitor.bottom - mi.rcMonitor.top,
        SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}

// FUNGSI WARNA RGB (ANSI)
void enableANSI() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Virtual Terminal Processing untuk kode warna ANSI/RGB
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    mode |= 0x0004; // 0x0004 = ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(h, mode);
}
void setRGBColor(int r, int g, int b, int isBackground) {
    if (isBackground) {
        printf("\x1b[48;2;%d;%d;%dm", r, g, b); // warna background
    } else {
        printf("\x1b[38;2;%d;%d;%dm", r, g, b); // warna text:
    }
}
void fillScreenBG() {
    int w = consoleW();
    int h = consoleH();

    setRGBColor(202, 40, 44, 1);

    gotoxy(0, 0);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf(" ");
        }
    }
}
void applyColors()
{
    RGBColor red = {202, 40, 44};
    RGBColor cream = {251, 255, 199};

    setRGBColor(red.R, red.G, red.B, 1);
    setRGBColor(cream.R, cream.G, cream.B, 0);

    fillScreenBG();
    gotoxy(0,0);
}
void goFullscreen() // Alt + Enter buat Fullscreen
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1C, 0, 0);
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    Sleep(150);
}
void maximizeConsole()
{
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
    Sleep(150);
}
void fixConsoleBuffer() {
    HWND console = GetConsoleWindow();
    HMONITOR monitor = MonitorFromWindow(console, MONITOR_DEFAULTTONEAREST);

    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(monitor, &mi);

    int width  = mi.rcMonitor.right  - mi.rcMonitor.left;
    int height = mi.rcMonitor.bottom - mi.rcMonitor.top;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hOut, (COORD){ width, height });
}
void warna()
{
    RGBColor red = {202, 40, 44};
    RGBColor cream = {251, 255, 199};
    setRGBColor(red.R, red.G, red.B, 1);
    setRGBColor(cream.R, cream.G, cream.B, 0);
}

void startupSequence() {
    enableANSI();
    maximizeConsole();
    goFullscreen();
    Borderless();
    Sleep(200);
    fixConsoleBuffer();
    applyColors();
    Sleep(50);
}

//PERULANGAN GARIS DARI UJUNG KE UJUNG
void garisx(int x, int y)
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE); //akses cursor (posisi text nya)
    int width = consoleW();

    for (int i = x; i < width; i++)
    {
        COORD kor = {i, y}; //kordinat cursornya
        SetConsoleCursorPosition(move, kor); //buat mulai posisi nya sesuai kordinat
        printf("█");
    }

    COORD reset = {0, 7};
    SetConsoleCursorPosition(move, reset);
}
void garisy(int x, int y)
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE); //akses cursor (posisi text nya)
    int height = consoleH();

    for (int i = y; i < height; i++)
    {
        COORD kor = {x, i}; //kordinat cursornya
        SetConsoleCursorPosition(move, kor); //buat mulai posisi nya sesuai kordinat
        printf("██");
    }
}

//INPUT SAAT LOGIN
void clearinput(int x, int y, int l) // membersihkan input yang salah
{
    gotoxy(x, y);
    warna();
    for (int i = 0; i < l; i++)
        printf(" ");
}
void inputpasslog(char pass[], int x, int y, char *ouput) //fungsi untuk password
{
    char ch;
    int i = 0, visible = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27)exit(0);

        if (ch == 13) // baca input ketika ENTER
        {
            pass[i] = '\0'; //biar ENTER g masuk ke array
            break;
        }
        else if (ch == 9) // baca input ketika TAB (show/hide)
        {
            visible = !visible;

            gotoxy(x, y);
            printf("%s\t: ", ouput);
            for (int j = 0; j < i; j++)
                printf(visible ? "%c" : "*", pass[j]);
        }
        else if (ch == 8) // baca input ketika BACKSPACE
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); //fungsi untuk backspace
            }
        }
        else if (ch >= 33 && ch <= 126)
        {
            pass[i++] = ch;
            printf(visible ? "%c" : "*", ch);
        }
    }
}
void inputpass(char pass[], int x, int y, char *ouput) //fungsi untuk password
{
    char ch;
    int i = 0, visible = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        // if (ch == 27)exit(0);

        if (ch == 13) // baca input ketika ENTER
        {
            pass[i] = '\0'; //biar ENTER g masuk ke array
            break;
        }
        else if (ch == 9) // baca input ketika TAB (show/hide)
        {
            visible = !visible;

            gotoxy(x, y);
            printf("%s: ", ouput);
            for (int j = 0; j < i; j++)
                printf(visible ? "%c" : "*", pass[j]);
        }
        else if (ch == 8) // baca input ketika BACKSPACE
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); //fungsi untuk backspace
            }
        }
        else if (ch >= 33 && ch <= 126)
        {
            pass[i++] = ch;
            printf(visible ? "%c" : "*", ch);
        }
    }
}
void inputusname(char input[])
{
    char ch;
    int i = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27)exit(0);

        if (ch == 13) // baca input ketika ENTER
        {
            input[i] = '\0'; //biar ENTER g masuk ke array
            break;
        }
        if (ch == 8 && i > 0) // baca input ketika BACKSPACE
        {
            i--;
            printf("\b \b"); //fungsi untuk backspace
        }
        else if (ch >= 33 && ch <= 126) {
            input[i++] = ch;
            printf("%c", ch);
        }
    }
}
void inputtext(char input[])
{
    char ch;
    int i = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        // if (ch == 27)exit(0);

        if (ch == 13) // baca input ketika ENTER
        {
            input[i] = '\0'; //biar ENTER g masuk ke array
            break;
        }
        if (ch == 8 && i > 0) // baca input ketika BACKSPACE
        {
            i--;
            printf("\b \b"); //fungsi untuk backspace
        }
        else if (ch >= 33 && ch <= 126) {
            input[i++] = ch;
            printf("%c", ch);
        }
    }
}
int inputid(char input[])
{
    char ch;
    int i = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27)return 0;

        if (ch == 13) // baca input ketika ENTER
        {
            input[i] = '\0';
            return 1;
        }
        if (ch == 8 && i > 0) // baca input ketika BACKSPACE
        {
            i--;
            printf("\b \b"); //fungsi untuk backspace
        }
        else if (ch >= 33 && ch <= 126) {
            input[i++] = ch;
            printf("%c", ch);
        }
    }
}

char *cutname(char nama[])
{
    static char tampil[20]; // pakai static biar ga hilang setelah return

    strncpy(tampil, nama, 15);
    tampil[15] = '\0';

    if (strlen(nama) > 15)
        strcat(tampil, "..");

    return tampil;
}
int onlyNum(char *s)
{
    int len = strlen(s);

    if (len <= 10 || len >15) return 0;
    for (int i = 0; s[i] != '\0'; i++)
        if (!isdigit(s[i])) return 0; //CEK KHUSUS ANGKA
    return 1;
}
int cekEmail(char *s)
{
    char *at = strchr(s, '@');
    return at != NULL && at != s && at[1] != '\0'; //CEK ADA @ GK, CEK @ G DI AWAL, CEK @ G DI AKHIR
}
int cekrole(char *r)
{
    if (
        strcmp(r, "superadmin") == 0 ||
        strcmp(r, "staff") == 0 ||
        strcmp(r, "manajer") == 0 ||
        strcmp(r, "kasir") == 0 ||
        strcmp(r, "member") == 0 ||
        strcmp(r, "supplier") == 0
    ) {
        return 1;
    }
    return 0;
}
void frame(int left, int top, int right, int bot)
{
    for (int x = left; x <= right; x++) {
        gotoxy(x, top); printf("─");
        gotoxy(x, bot); printf("─");
    }
    for (int y = top; y <= bot; y++) {
        gotoxy(left, y); printf("│");
        gotoxy(right, y); printf("│");
    }
    gotoxy(left, top); printf("┌");
    gotoxy(right, top);printf("┐");
    gotoxy(left, bot); printf("└");
    gotoxy(right, bot);printf("┘");
}

//MENU
extern void setRGBColor(int r, int g, int b, int isBackground);
void resetColor() {
    printf("\x1b[0m");
}
int menuSelect(int x, int y, char *menu[], int count)
{
    int pos = 0;
    int key;

    //matiin kursor
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    while (1)
    {
        // DRAW MENU
        for (int i = 0; i < count; i++)
        {
            gotoxy(x, y + i);

            if (i == pos) {
                setRGBColor(251, 255, 199, 1);
                setRGBColor(202, 40, 44, 0);
                printf("➤ %-18s", menu[i]);
                resetColor();
            } else {
                setRGBColor(202, 40, 44, 1);
                setRGBColor(251, 255, 199, 0);
                printf("  %-18s", menu[i]);
                resetColor();
            }
        }

        key = _getch();

        // panah
        if (key == -32 || key == 224) {
            key = _getch();
            if (key == 72) pos--; // UP
            if (key == 80) pos++; // DOWN
            if (key == 75) return -1; //LEFT
            if (key == 77) return -2; //RIGHT
        }

        // w/s
        if (key == 'w' || key == 'W') pos--;
        if (key == 's' || key == 'S') pos++;

        // enter
        if (key == 13) return pos;

        // WRAP
        if (pos < 0) pos = count - 1;
        if (pos >= count) pos = 0;
    }
}
void showcurs()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = TRUE;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void clearArea(int x, int y, int width, int height)
{
    setRGBColor(202, 40, 44, 1);   // Background Merah
    setRGBColor(251, 255, 199, 0); // Text Cream

    for (int i = 0; i < height; i++)
    {
        gotoxy(x, y + i);
        for(int j = 0; j < width; j++) {
            printf(" ");
        }
    }
}

#endif //EATBOX_FUNCTION_H