#ifndef EATBOX_INTERFACE_H
#define EATBOX_INTERFACE_H

#include "function.h"
#include "data.h"
#include "CRUD/create.h"
#include "CRUD/read.h"

void createAdmin(char nama[50]);
void ubahAdmin(char nama[50]);
void hapusAdmin(char nama[50]);
void supadm(char nama[50]);

void createAdmin(char nama[50])
{
    Akun a;
    memset(&a, 0, sizeof(a)); //ngisi buffer di a jadi 0 semua

    system("cls");

    int filled_username = 0;
    int filled_password = 0;
    int filled_telp = 0;
    int filled_email = 0;
    int filled_role = 0;
    int filled_alamat = 0;
    int filled_status = 0;

    while (1)
    {
        applyColors();
        appname(43, 1);
        garisx(0,8);

        int left = 30;
        int top  = 9;
        int right = 105;
        int bot   = 35;

        frame(left, top, right, bot);
        int y = top + 2;

        // BUAT FORM PENGISIAN NYA
        gotoxy(left+2, y);
        printf("Username : %s", filled_username ? a.username : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Password : ");
        if (filled_password) {
            int len = strlen(a.password);
            for (int i = 0; i < len; i++) {printf("*");}
        } else {printf("");}

        y+=2;
        gotoxy(left+2, y);
        printf("Telp     : %s", filled_telp ? a.telp : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Email    : %s", filled_email ? a.email : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Role     : %s", filled_role ? a.role : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Alamat   : %s", filled_alamat ? a.alamat : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Status   : %s", filled_status ? (a.status == 1 ? "1" : "0") : "");

        char *opsi[] = {
            " Username",
            " Password",
            " Telp",
            " Email",
            " Role",
            " Alamat",
            " Status",
            " Simpan",
            " Batal"
        };

        gotoxy(right+5, top+4);
        setRGBColor(251, 255, 199, 1);
        setRGBColor(202, 40, 44, 0);
        printf(" [↕] Pilih Input    ");
        resetColor();

        int pilih = menuSelect(right+5, top+6, opsi, 9);

        switch (pilih)
        {
            case 0:
                gotoxy(left+13, top+2);
                clearinput(left+13, top+2, 40);

                gotoxy(left+13, top+2);
                showcurs();
                inputtext(a.username);
                filled_username = strlen(a.username) > 0;
                break;

            case 1:
                gotoxy(left+13, top+4);
                clearinput(left+13, top+4, 40);

                gotoxy(left+13, top+4);
                showcurs();
                inputpass(a.password, left+2, top+4, "Password ");
                filled_password = strlen(a.password) > 0;
                break;

            case 2:
                do {
                    gotoxy(left+13, top+6);
                    clearinput(left+13, top+6, 20);

                    gotoxy(left+13, top+6);
                    showcurs();
                    inputtext(a.telp);

                    if (onlyNum(a.telp)) {
                        filled_telp = 1;
                    } else {
                        gotoxy(left+13, top+7);
                        printf("Nomor tidak valid!");
                    }
                } while (!filled_telp);
                clearinput(left+13, top+7, 20);
                break;

            case 3:
                do {
                    gotoxy(left+13, top+8);
                    clearinput(left+13, top+8, 30);

                    gotoxy(left+13, top+8);
                    showcurs();
                    inputtext(a.email);

                    if (cekEmail(a.email)) {
                        filled_email = 1;
                    } else {
                        gotoxy(left+13, top+9);
                        printf("Email tidak valid!");
                    }
                } while (!filled_email);
                clearinput(left+13, top+9, 30);
                break;

        case 4:
            do {
                filled_role = 0;

                gotoxy(left+13, top+10);
                clearinput(left+13, top+10, 20);

                gotoxy(left+13, top+10);
                showcurs();
                inputtext(a.role);

                //buat biar g ada enter yang ikut masuk ke array
                a.role[19] = '\0';
                a.role[strcspn(a.role, "\n")] = '\0';

                if (cekrole(a.role)) {
                    filled_role = 1;
                } else {
                    gotoxy(left+13, top+11);
                    printf("Role tidak valid! hanya (manajer, staff, kasir)");
                }

            } while (!filled_role);

            clearinput(left+13, top+11, 20);
            break;

            case 5:
                gotoxy(left+13, top+12);
                clearinput(left+13, top+12, 40);

                gotoxy(left+13, top+12);
                showcurs();
                inputtext(a.alamat);
                filled_alamat = strlen(a.alamat) > 0;
                break;

            case 6:
                gotoxy(left+13, top+14);
                clearinput(left+13, top+14, 40);

                gotoxy(left+13, top+14);
                showcurs();
                scanf("%d", &a.status); getchar();
                a.status = (a.status == 1 ? 1 : 0);
                filled_status = 1;
                break;

            case 7:
                if (filled_username &&
                    filled_password &&
                    filled_telp &&
                    filled_email &&
                    filled_role &&
                    filled_alamat &&
                    filled_status)
                {
                    createAkun(a);
                    printf("Data berhasil ditambahkan!");
                    return;
                }
                else {
                    gotoxy(right-20, bot-1);
                    printf("Lengkapi semua data!");
                }
                break;

            case 8:
                return;
        }
    }
}

void ubahAdmin(char nama[50]){}
void hapusAdmin(char nama[50]){}

void supadm(char nama[50])
{
    char *menuSup[] = {" Data Karyawan", " Tambah Karyawan", " Ubah Karyawan", " Hapus Karyawan", " Keluar"};
    system("cls");
    applyColors();

    appname(43, 1);
    garisx(0,8);
    garisy(25,8);

    gotoxy(60, 10);
    printf("DATA KARYAWAN");

    int left = 30;
    int right = 130;
    int top = 11;
    int bot = 32;

    for (int x = left; x < right; x++)
    {
        gotoxy(x, top);
        printf("─");
        gotoxy(x, bot);
        printf("─");
    }
    for (int y = top; y < bot; y++)
    {
        gotoxy(left, y);
        printf("│");
        gotoxy(right, y);
        printf("│");
    }
    for (int y = top; y < bot-1; y++)
    {
        gotoxy(left+5, y+1);
        printf("│");
        gotoxy(left+28, y+1);
        printf("│");
        gotoxy(left+43, y+1);
        printf("│");
        gotoxy(left+58, y+1);
        printf("│");
        gotoxy(left+78, y+1);
        printf("│");
        gotoxy(left+88, y+1);
        printf("│");
    }

    gotoxy(left, top); printf("┌");
    gotoxy(right,top); printf("┐");
    gotoxy(left, bot); printf("└");
    gotoxy(right,bot); printf("┘");

    int yhead = top + 1;

    gotoxy(left+2, yhead);
    printf("No");

    gotoxy(left+8, yhead);
    printf("Nama Karyawan");

    gotoxy(left+30, yhead);
    printf("No. telp");

    gotoxy(left+45, yhead);
    printf("Email");

    gotoxy(left+60, yhead);
    printf("Alamat");

    gotoxy(left+80, yhead);
    printf("Posisi");

    gotoxy(left+90, yhead);
    printf("Status");

    for (int x = left+1; x < right; x++)
    {
        gotoxy(x, yhead+1);
        printf("─");
    }

    //DOWNMENU
    gotoxy(1,10);printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕] Pilih Menu");

    int pilih = menuSelect(1,12, menuSup, 5);
    switch (pilih)
    {
        case 0: supadm(nama); break;
        case 1: createAdmin(nama); break;
        case 2: ubahAdmin(nama); break;
        case 3: hapusAdmin(nama); break;
        case 4: exit(0);
    }
}

void admin(char nama[50]){}
void manajer(char nama[50]){}
void kasir(char nama[50]){}

void tampilan(char nama[50])
{
    supadm(nama);
}

#endif //EATBOX_INTERFACE_H