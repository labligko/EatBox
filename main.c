#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void garisx();
void garisy();
void login(char nama[50], char pass[50]);
void supadm(char nama[50]);
int consoleW();
int consoleH();

int main(void)
{
    char nama[50], pass[50];
    system("color 5F"); //ini buat warna yang depan bg yang belakang text
    system("chcp 65001 > nul"); //ini buat baca UFT-8

    login(nama, pass);
    if (nama[0] != '\0' && pass[0] != '\0')
    {
        supadm(nama);

        getchar();
    }

    getchar();
    return 0;
}

void garisx()
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE); //akses cursor (posisi text nya)
    int width = consoleW();

    for (int x = 0; x < width; x++)
    {
        COORD kor = {x, 5}; //kordinat cursornya
        SetConsoleCursorPosition(move, kor); //buat mulai posisi nya sesuai kordinat
        printf("█");
    }

    COORD reset = {0, 7};
    SetConsoleCursorPosition(move, reset);
}
void garisy()
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE); //akses cursor (posisi text nya)
    int height = consoleH();

    for (int y = 0; y < height; y++)
    {
        COORD kor = {25, y}; //kordinat cursornya
        SetConsoleCursorPosition(move, kor); //buat mulai posisi nya sesuai kordinat
        printf("██");
    }
}

void login(char nama[50], char pass[50])
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(move, (COORD){55,2});
    printf("EATBOX");

    garisx();

    SetConsoleCursorPosition(move, (COORD){55,8});
    printf("LOGIN");

    for (int x = 31 ; x < 85; x++)
    {
        SetConsoleCursorPosition(move, (COORD){x, 10});
        printf("-");
        SetConsoleCursorPosition(move, (COORD){x, 20});
        printf("-");
    }
    SetConsoleCursorPosition(move, (COORD){30, 10}); printf("┌");
    SetConsoleCursorPosition(move, (COORD){85, 10}); printf("┐");

    for (int y = 11; y < 20; y++)
    {
        SetConsoleCursorPosition(move, (COORD){30, y});
        printf("|");
        SetConsoleCursorPosition(move, (COORD){85, y});
        printf("|");
    }
    SetConsoleCursorPosition(move, (COORD){30, 20}); printf("└");
    SetConsoleCursorPosition(move, (COORD){85, 20}); printf("┘");

    SetConsoleCursorPosition(move, (COORD){31, 11});
    printf("Usename\t: "); scanf("%s", nama);

    SetConsoleCursorPosition(move, (COORD){31, 12});
    printf("Password\t: "); scanf("%s", pass);
}
void supadm(char nama[50])
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    SetConsoleCursorPosition(move, (COORD){7,2});
    printf("EATBOX");

    garisx();
    garisy();

    SetConsoleCursorPosition(move, (COORD){30,2});
    printf("Halo, %s", nama);

    int left = 30;
    int right = 105;
    int top = 7;
    int bot = 28;

    for (int x = left; x < right; x++)
    {
        SetConsoleCursorPosition(move, (COORD){x, top});
        printf("─");
        SetConsoleCursorPosition(move, (COORD){x, bot});
        printf("─");
    }

    for (int y = top; y < bot; y++)
    {
        SetConsoleCursorPosition(move, (COORD){left, y});
        printf("│");
        SetConsoleCursorPosition(move, (COORD){right, y});
        printf("│");
    }

    for (int y = top; y < bot-1; y++)
    {
        SetConsoleCursorPosition(move, (COORD){left+23, y+1});
        printf("│");
        SetConsoleCursorPosition(move, (COORD){left+43, y+1});
        printf("│");
        SetConsoleCursorPosition(move, (COORD){left+63, y+1});
        printf("│");
    }


    SetConsoleCursorPosition(move, (COORD){left, top}); printf("┌");
    SetConsoleCursorPosition(move, (COORD){right, top}); printf("┐");
    SetConsoleCursorPosition(move, (COORD){left, bot}); printf("└");
    SetConsoleCursorPosition(move, (COORD){right, bot}); printf("┘");

    int yhead = top + 1;

    SetConsoleCursorPosition(move, (COORD){left + 3, yhead});
    printf("Nama Admin");

    SetConsoleCursorPosition(move, (COORD){left + 25, yhead});
    printf("No. telp");

    SetConsoleCursorPosition(move, (COORD){left + 45, yhead});
    printf("Email");

    SetConsoleCursorPosition(move, (COORD){left + 65, yhead});
    printf("Status");

    for (int x = left+1; x < right; x++)
    {
        SetConsoleCursorPosition(move, (COORD){x, yhead + 1});
        printf("─");
    }

    SetConsoleCursorPosition(move, (COORD){1,10}); printf("1. Tambah Admin");
    SetConsoleCursorPosition(move, (COORD){1,11}); printf("2. Ubah Admin");
    SetConsoleCursorPosition(move, (COORD){1,12}); printf("3. Hapus Admin");
    SetConsoleCursorPosition(move, (COORD){1,13}); printf("0. Keluar");
    SetConsoleCursorPosition(move, (COORD){1,15}); printf("Masukan Pilihan Anda :");
    int n; while (n < 0 || n > 3){scanf("%d", &n);}
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
