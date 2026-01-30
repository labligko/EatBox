#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#include "../include/data.h"
#include "../include/function.h"

DateTime now() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    DateTime d;
    d.hari = tm->tm_mday;
    d.bulan = tm->tm_mon + 1;
    d.tahun = tm->tm_year + 1900;
    d.jam = tm->tm_hour;
    d.menit = tm->tm_min;
    d.detik = tm->tm_sec;
    return d;
}
int hariIni(DateTime d)
{
    DateTime sekarang = now();
    return d.hari == sekarang.hari && d.bulan == sekarang.bulan && d.tahun == sekarang.tahun;
}

void formatTanggal(DateTime d, char *out){
    sprintf(out, "%02d/%02d/%04d", d.hari, d.bulan, d.tahun);//print string sampai batas (abaikan buffer)
}
void formatJam(DateTime d, char *out){
    snprintf(out, 6, "%02d:%02d", d.jam, d.menit);//print string sampai batas (abaikan buffer)
}
void formatTanggalJam(DateTime d, char *out){
    sprintf(out, "%02d/%02d/%04d %02d:%02d", d.hari, d.bulan, d.tahun, d.jam, d.menit);
}


// FUNGSI UTILITY DASAR
void gotoxy(int x, int y){
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
void Fullscreen() // Alt + Enter buat Fullscreen
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
    Fullscreen();
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
int inputusname(char input[])
{
    char ch;
    int i = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27) exit(0);

        if (ch == 13) // baca input ketika ENTER
        {
            input[i] = '\0'; //biar ENTER g masuk ke array
            return 1;
        }
        if (ch == 8 && i > 0) // baca input ketika BACKSPACE
        {
            i--;
            printf("\b \b"); //fungsi untuk backspace
        }
        // Hanya menerima: Angka (0-9) ATAU Huruf Besar (A-Z) ATAU Huruf Kecil (a-z)
        else if ((ch >= '0' && ch <= '9') ||
                 (ch >= 'A' && ch <= 'Z') ||
                 (ch >= 'a' && ch <= 'z'))
        {
            if (i < 20) { // limit buffer biar ga overflow
                input[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}
int inputpass(char pass[], int x, int y, char *ouput) //fungsi untuk password
{
    char ch;
    int i = 0, visible = 0;
    pass[0] = '\0';

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27)return 0;

        if (ch == 13) // baca input ketika ENTER
        {
            pass[i] = '\0'; //biar ENTER g masuk ke array
            return 1;
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
int inputtext(char input[])
{
    char ch;
    int i = 0;
    input[0] = '\0'; //hapus buffer string

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27)return 0;

        if (ch == 13) // baca input ketika ENTER
        {
            input[i] = '\0'; //biar ENTER g masuk ke array
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
int inputTelp08(char *input)
{
    // 1. Set Default "08"
    strcpy(input, "08");
    printf("08"); // Tampilkan langsung di layar

    int i = 2; // Mulai ketik dari karakter ke-3 (index 2)
    char ch;

    while (1)
    {
        ch = _getch();

        if (ch == 27) return 0; // ESC

        if (ch == 13) { // ENTER
            input[i] = '\0';
            return 1;
        }

        if (ch == 8) { // BACKSPACE
            // [PENTING] Cuma boleh hapus kalau i > 2
            // Jadi "08" gak bakal bisa kehapus
            if (i > 2) {
                i--;
                printf("\b \b");
            }
        }
        // Input Angka (0-9)
        else if (ch >= '0' && ch <= '9') {
            if (i < 13) { // Batasi max 13 digit (termasuk 08)
                input[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}
int inputbebas(char input[])
{
    char ch;
    int i = 0;
    input[0] = '\0';

    while (1)
    {
        ch = _getch();

        if (ch == 27) return 0; // ESC

        if (ch == 13) // ENTER
        {
            input[i] = '\0';
            // Validasi tambahan: Kalau isinya cuma spasi doang, anggap kosong
            if (i > 0 && input[0] == ' ') return 1;
            return 1;
        }

        if (ch == 8) // BACKSPACE
        {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // [PERUBAHAN DISINI]
        // Ganti 33 jadi 32 agar Spasi dianggap karakter valid
        else if (ch >= 32 && ch <= 126) {
            // Tambah limit biar gak overflow array (misal max 99 char)
            if (i < 99) {
                input[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}
int inputName(char input[])
{
    char ch;
    int i = 0;
    input[0] = '\0';

    while (1)
    {
        ch = _getch();

        if (ch == 27) return 0; // ESC

        if (ch == 13) // ENTER
        {
            input[i] = '\0';
            // Validasi: Tidak boleh kosong atau cuma spasi doang
            if (i > 0 && input[0] != ' ') return 1;
            // Kalau kosong/spasi doang, jangan return 1 dulu (tapi opsional, bisa dihandle di UI)
            if (i == 0) return 1;
        }

        if (ch == 8) // BACKSPACE
        {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // --- LOGIKA FILTER KARAKTER NAMA ---
        else if (
            (ch >= 'a' && ch <= 'z') || // Huruf Kecil
            (ch >= 'A' && ch <= 'Z') || // Huruf Besar
            ch == ' ' ||                // Spasi
            ch == '.' ||                // Titik
            ch == '\''||                // Petik (fungsi \ buat indikasi ' di anggap text bukan bungkus char)
            ch == '-'                   // Strip
        ) {
            if (i < 49) { // Limit sesuai size struct nama[50]
                input[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}
int inputField(char input[]) {
    char ch;
    int i = 0;
    input[0] = '\0';

    while (1)
    {
        ch = _getch();

        if (ch == 27) return 0; // ESC

        if (ch == 13) // ENTER
        {
            input[i] = '\0';
            // Validasi tambahan: Kalau isinya cuma spasi doang, anggap kosong
            if (i > 0 && input[0] == ' ') return 1;
            return 1;
        }

        // panah
        if (ch == -32 || ch == 224) {
            ch = _getch();
            if (ch == 75) return -1; //LEFT
            if (ch == 77) return -2; //RIGHT
        }

        if (ch == 8) // BACKSPACE
        {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch >= '0' && ch <= '9' && i < 9) {
            input[i++] = ch;
            printf("%c", ch);
        }
    }
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
char *cutname(char nama[])
{
    static char tampil[20]; // pakai static biar ga hilang setelah return

    strncpy(tampil, nama, 15);
    tampil[15] = '\0';

    if (strlen(nama) > 15)
        strcat(tampil, "..");

    return tampil;
}
int cekEmail(char *s)
{
    // --- 1. UBAH SEMUA JADI HURUF KECIL (NORMALIZE) ---
    // Ini bikin data di database jadi rapi juga
    for(int i = 0; s[i]; i++){
        s[i] = tolower(s[i]);
    }

    // --- 2. Validasi Dasar ---
    if (strlen(s) < 16) return 0; // @gmail.com aja 10 huruf
    if (strchr(s, ' ') != NULL) return 0; // gaboleh spasi

    char *at = strchr(s, '@'); //cari @
    if (at == NULL || at == s) return 0; // @ nya g ada, @ diawal
    if (strchr(at + 1, '@') != NULL) return 0; //cek @ duplikat

    char *dot = strchr(at + 1, '.'); //cari . setelah @
    if (dot == NULL || dot == at + 1 || dot[1] == '\0') return 0; // . g ada, . nempel satelah @, . diakhir

    // --- 3. VALIDASI DOMAIN ---
    char *domain = at + 1;

    const char *allowedDomains[] = {
        "gmail.com","yahoo.com","outlook.com"
    };

    int totalDomains = sizeof(allowedDomains) / sizeof(allowedDomains[0]);

    // Sekarang bisa pakai strcmp biasa karena input 's' sudah dikecilin semua
    for (int i = 0; i < totalDomains; i++) {
        if (strcmp(domain, allowedDomains[i]) == 0) {
            return 1; // Valid
        }
    }

    return 0; // Tidak ada di daftar
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
int onlyNum(char *s) {
    if (strlen(s) == 0) return 0;
    for (int i = 0; s[i] != '\0'; i++) {if (!isdigit(s[i])) {return 0;}}
    return 1;
}
int isDuplicate(char *jenis, char *isiData, char *idPengecualian) {
    FILE *f = fopen(FILE_KARYAWAN, "rb");
    if (!f) return 0;

    Karyawan k;

    while (fread(&k, sizeof(Karyawan), 1, f))
    {
        // Skip ID sendiri (saat update)
        if (strcmp(k.id, idPengecualian) == 0)
            continue;

        if (strcmp(jenis, "username") == 0)
        {
            if (strcmpi(k.username, isiData) == 0) {
                fclose(f);
                return 1;
            }
        }
        else if (strcmp(jenis, "telp") == 0)
        {
            if (strcmp(k.telp, isiData) == 0) {
                fclose(f);
                return 1;
            }
        }
        else if (strcmp(jenis, "email") == 0)
        {
            if (strcmpi(k.email, isiData) == 0) {
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

void resetColor() {
    printf("\x1b[0m"); //Reset semua atribut tampilan ke default.
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

int popupConfirm(char *msg, char *pesan1, char *pesan2)
{
    //matiin cursor
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // 1. Hitung Posisi Tengah Layar
    int cw = consoleW();
    int ch = consoleH();
    int width = 50;
    int height = 7;
    int x = (cw - width) / 2;
    int y = (ch - height) / 2;

    // 2. Setup Warna (Biar beda dari background form)
    setRGBColor(135, 30, 32, 1);
    setRGBColor(251, 255, 199, 0);

    // 3. Gambar Kotak Popup
    // Hapus area dulu biar gak numpuk teks belakang
    for(int i=0; i<=height; i++) {
        gotoxy(x, y+i);
        for(int j=0; j<=width; j++) printf(" ");
    }

    frame(x, y, x + width, y + height);

    // 4. Cetak Pesan (Tengah Kotak)
    int msgLen = strlen(msg);
    int textX = x + (width - msgLen) / 2;
    gotoxy(textX, y + 2);
    printf("%s", msg);

    // 5. Cetak Pilihan
    gotoxy(x + 10, y + 4);
    printf("[ENTER] %s        [ESC] %s", pesan1, pesan2);

    // 6. Logic Input
    while(1) {
        char ch = _getch();
        if (ch == 13) { // ENTER
            resetColor(); // Balikin warna
            return 1;
        }
        if (ch == 27) { // ESC
            resetColor();
            return 0;
        }
    }
}
void popupAlert(int code, char *msg)
{
    int cw = consoleW();
    int ch = consoleH();
    int width = 50;
    int height = 7;
    int x = (cw - width) / 2;
    int y = (ch - height) / 2;

    if (code == 1) setRGBColor(46, 125, 86, 1);
    else setRGBColor(180, 40, 40, 1);
    setRGBColor(251, 255, 199, 0);

    // Hapus area
    for(int i=0; i<=height; i++) {
        gotoxy(x, y+i);
        for(int j=0; j<=width; j++) printf(" ");
    }

    frame(x, y, x + width, y + height);

    int msgLen = strlen(msg);
    int textX = x + (width - msgLen) / 2;
    gotoxy(textX, y + 2);
    printf("%s", msg);

    // Tunggu enter/sembarang tombol
    Sleep(1000);
    resetColor();
}

void drawGantiPassBox(int x, int y, int w, int h) {
    clearArea(x, y, w, h);
    frame(x, y, x+w, y+h);
    gotoxy(x+15, y+2); printf("GANTI PASSWORD");
    gotoxy(x+2, y+4);  printf("[ESC] Batal");
}

int stringCek(char *mainStr, char *subStr) {
    char lowerMain[255];
    char lowerSub[255];

    // Copy dan ubah ke lowercase biar pencarian tidak peduli huruf besar/kecil
    strcpy(lowerMain, mainStr);
    strcpy(lowerSub, subStr);
    strlwr(lowerMain); // fungsi bawaan string.h (Windows)
    strlwr(lowerSub);

    // Cek apakah substring ada
    if (strstr(lowerMain, lowerSub) != NULL) {
        return 1; // Ketemu
    }
    return 0; // Gak ketemu
}
int getNamaKasir(const char* id, char* outNama)
{
    FILE* f = fopen(FILE_KARYAWAN, "rb");
    if (!f) return 0;

    Karyawan k;

    while (fread(&k, sizeof(Karyawan), 1, f))
    {
        if (strcmp(k.id, id) == 0)
        {
            strcpy(outNama, k.nama);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
int getMenuByID(const char *id, Menu *out) {
    FILE *f = fopen(FILE_MENU, "rb");
    if (!f) return 0;

    int total;
    fread(&total, sizeof(int), 1, f); // LOMPATI HEADER JUMLAH MENU

    Menu m;
    while (fread(&m, sizeof(Menu), 1, f)) {
        if (strcmp(m.id_menu, id) == 0) {
            *out = m;
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}