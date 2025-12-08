#ifndef EATBOX_LOGIN_H
#define EATBOX_LOGIN_H

#include "function.h"
#include "interface.h"

int cekLogin(const char *nama, const char *pass, char *role)
{
    FILE *f = fopen("akun.txt", "r");
    if (!f) return 0;

    char line[1024];
    char fileUser[50], filePass[50], fileRole[50];

    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = '\0'; //BUAT HAPUS NEWLINE
        sscanf(line, "%[^;];%[^;];%[^;]", fileUser, filePass, fileRole);

        if (strcmp(nama, fileUser) == 0 && strcmp(pass, filePass) == 0)
        {
            strcpy(role, fileRole);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void login(char nama[50], char pass[50])
{
    char role[50];

    appname(43, 2);
    garisx(0, 10);
    garisy(5, 0);
    garisy(consoleW()-5, 0);
    gotoxy(65, 15);
    printf("");
    logname(55, 13);

    for (int x = 41 ; x < 95; x++)
    {
        gotoxy(x, 20);
        printf("-");
        gotoxy(x, 30);
        printf("-");
    }
    gotoxy(40,20); printf("┌");
    gotoxy(95,20); printf("┐");

    for (int y = 21; y < 30; y++)
    {
        gotoxy(40, y);printf("|");
        gotoxy(95, y);printf("|");
    }
    gotoxy(40, 30); printf("└");
    gotoxy(95, 30); printf("┘");

    while (1){
        gotoxy(42, 19);
        printf("[ESC] Keluar");
        gotoxy(56, 19);
        printf("[TAB] Lihat/Sembunyikan");
        gotoxy(81, 19);
        printf("[ENTER] Masuk");

        clearinput(41, 21, 50);
        clearinput(41, 22, 50);
        clearinput(41, 23, 50);

        gotoxy(42, 21); printf("Nama Pengguna\t: ");
        gotoxy(42, 22); printf("Kata Sandi\t: ");

        gotoxy(58, 21); fflush(stdin); inputusname(nama);
        gotoxy(58, 22); fflush(stdin); inputpasslog(pass, 42, 22, "Kata Sandi");

        if (strcmp(nama, "superadmin") == 0 && strcmp(pass, "superadmin") == 0) {break;}
        // if (cekLogin(nama, pass, role)){break;}

        gotoxy(53, 27);
        printf("Username atau Password salah!\n");
    }
    supadm(nama);

    if (strcmp(role, "superadmin") == 0){supadm(nama);}
    else if (strcmp(role, "admin") == 0){admin(nama);}
    else if (strcmp(role, "manajer") == 0){manajer(nama);}
    else if (strcmp(role, "kasir") == 0){kasir(nama);}
}

#endif //EATBOX_LOGIN_H