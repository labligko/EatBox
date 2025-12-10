#ifndef EATBOX_INTERFACE_H
#define EATBOX_INTERFACE_H

#include <time.h>

#include "../function.h"
#include "../data.h"
#include "../CRUD/create.h"
#include "../CRUD/read.h"
#include "../CRUD/delete.h"
#include "../CRUD/update.h"

void createAdmin(char nama[50]);
void updateAdmin(char nama[50]);
void hapusAdmin(char nama[50]);
void supadm(char nama[50]);

void createAdmin(char nama[50])
{
    Karyawan a;
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

        gotoxy(right+5, top+5);
        setRGBColor(251, 255, 199, 1);
        setRGBColor(202, 40, 44, 0);
        printf(" [ENTER] Lanjut     ");
        resetColor();

        int pilih = menuSelect(right+5, top+7, opsi, 9);

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
                a.status = (a.status != 1 ? 0 : 1);
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
                    createKaryawan(a);
                    gotoxy(right-30, bot-1);
                    setRGBColor(251, 255, 199, 1);
                    setRGBColor(202, 40, 44, 0);
                    printf("Data berhasil ditambahkan!");
                    resetColor();
                    Sleep(1500);
                    supadm(nama);
                }
                else {
                    gotoxy(right-30, bot-1);
                    setRGBColor(251, 255, 199, 1);
                    setRGBColor(202, 40, 44, 0);
                    printf("Lengkapi semua data!");
                    Sleep(1500);
                    resetColor();
                }
                break;

            case 8:
                return;
        }
    }
}
void updateAdmin(char nama[50])
{
    system("cls");
    applyColors();
    appname(43, 1);
    garisx(0,8);

    char targetID[20];
    gotoxy(30, 11);
    printf(" [ESC] Kembali      ");
    gotoxy(50, 11);
    printf(" [ENTER] Lanjut     ");
    gotoxy(30,10);
    printf("Masukkan ID Karyawan yang ingin diedit: ");
    showcurs(); inputid(targetID);

    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    if (!f) { printf("File tidak ditemukan!\n"); Sleep(1500); return; }

    Karyawan a;
    int found = 0;
    char str[255];

    while (fgets(str, sizeof(str), f)) {
        Karyawan temp;
        sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d",
               temp.id, temp.username, temp.password, temp.telp,
               temp.email, temp.role, temp.alamat, &temp.status, &temp.poin);

        if(strcmp(temp.id, targetID) == 0) {
            a = temp;
            found = 1;
            break;
        }
    }
    fclose(f);

    if (!found) {
        gotoxy(30,13); printf("ID '%s' tidak ditemukan!", targetID);
        Sleep(1500);
        supadm(nama);
    }

    int filled_username = 1, filled_password = 1, filled_telp = 1;
    int filled_email = 1, filled_role = 1, filled_alamat = 1, filled_status = 1;

    while (1)
    {
        applyColors();
        appname(43, 1);
        garisx(0,8);

        int left = 30, top = 9, right = 105, bot = 35;

        frame(left, top, right, bot);

        int y = top + 2;

        // Username
        gotoxy(left+2, y);
        printf("Username : %-30s", filled_username ? a.username : "");
        // %-30s gunanya buat 'padding' spasi biar tulisan lama ketimpa

        y+=2;
        gotoxy(left+2, y);
        printf("Password : ");
        if (filled_password) {
            int len = strlen(a.password);
            for (int i = 0; i < len; i++) printf("*");
            printf("               "); // Timpa sisa karakter lama kalau password memendek
        }

        y+=2;
        gotoxy(left+2, y);
        printf("Telp     : %-20s", filled_telp ? a.telp : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Email    : %-30s", filled_email ? a.email : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Role     : %-20s", filled_role ? a.role : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Alamat   : %-40s", filled_alamat ? a.alamat : "");

        y+=2;
        gotoxy(left+2, y);
        printf("Status   : %-10s", filled_status ? (a.status == 1 ? "Aktif" : "Non-Aktif") : "");


        // --- MENU NAVIGASI ---
        char *opsi[] = {
            " Username", " Password", " Telp", " Email",
            " Role", " Alamat", " Status", " Simpan", " Batal"
        };

        gotoxy(right+5, top+4);
        setRGBColor(251, 255, 199, 1); setRGBColor(202, 40, 44, 0);
        printf(" [↕] Pilih Input    ");

        gotoxy(right+5, top+5);
        setRGBColor(251, 255, 199, 1); setRGBColor(202, 40, 44, 0);
        printf(" [ENTER] Lanjut     ");
        resetColor();

        int pilih = menuSelect(right+5, top+7, opsi, 9);

        // --- LOGIKA INPUT (Update Logic) ---
        switch (pilih)
        {
            case 0: // Username
                gotoxy(left+13, top+2); clearinput(left+13, top+2, 40);
                gotoxy(left+13, top+2); showcurs();
                inputtext(a.username);
                filled_username = strlen(a.username) > 0;
                break;

            case 1: // Password
                gotoxy(left+13, top+4); clearinput(left+13, top+4, 40);
                gotoxy(left+13, top+4); showcurs();
                inputpass(a.password, left+2, top+4, "Password ");
                filled_password = strlen(a.password) > 0;
                break;

            case 2: // Telp (Looping Validation)
                do {
                    gotoxy(left+13, top+6); clearinput(left+13, top+6, 20);
                    gotoxy(left+13, top+6); showcurs();
                    inputtext(a.telp);

                    if (onlyNum(a.telp) && strlen(a.telp)>0) {
                        filled_telp = 1;
                        clearinput(left+13, top+7, 20); // Hapus error msg
                    } else {
                        gotoxy(left+13, top+7); printf("Nomor tidak valid!");
                    }
                } while (!filled_telp);
                break;

            case 3: // Email (Looping Validation)
                do {
                    gotoxy(left+13, top+8); clearinput(left+13, top+8, 30);
                    gotoxy(left+13, top+8); showcurs();
                    inputtext(a.email);

                    if (cekEmail(a.email)) {
                        filled_email = 1;
                        clearinput(left+13, top+9, 30);
                    } else {
                        gotoxy(left+13, top+9); printf("Email tidak valid!");
                    }
                } while (!filled_email);
                break;

            case 4: // Role (Looping Validation)
                do {
                    gotoxy(left+13, top+10); clearinput(left+13, top+10, 20);
                    gotoxy(left+13, top+10); showcurs();
                    inputtext(a.role);
                    a.role[strcspn(a.role, "\n")] = 0;

                    if (cekrole(a.role)) {
                        filled_role = 1;
                        clearinput(left+13, top+11, 20);
                    } else {
                        gotoxy(left+13, top+11); printf("Role: manajer/staff/kasir");
                    }
                } while (!filled_role); // Perbaiki logika loop
                break;

            case 5: // Alamat
                gotoxy(left+13, top+12); clearinput(left+13, top+12, 40);
                gotoxy(left+13, top+12); showcurs();
                inputtext(a.alamat);
                filled_alamat = strlen(a.alamat) > 0;
                break;

            case 6: // Status
                a.status = (a.status == 1) ? 0 : 1;
                filled_status = 1;
                break;

            case 7: // Simpan
                if (filled_username && filled_password && filled_telp &&
                    filled_email && filled_role && filled_alamat)
                {
                    if(updateKaryawan(&a)){
                        gotoxy(right-30, bot-1);
                        setRGBColor(251, 255, 199, 1); setRGBColor(202, 40, 44, 0);
                        printf("Data berhasil diperbarui!");
                        resetColor();
                    } else {
                        gotoxy(right-30, bot-1); printf("Gagal update data!");
                    }
                    Sleep(1500);
                    return; // Selesai
                }
                else {
                    gotoxy(right-30, bot-1); printf("Lengkapi semua data!"); Sleep(1500);
                }
                break;

            case 8: // Batal
                return;
        }
    }
}
void hapusAdmin(char nama[50])
{
    while (1)
    {
        system("cls");

        applyColors();
        appname(43, 1);
        garisx(0,8);

        int left = 30;
        int top  = 9;
        int right = 105;
        int bot   = 35;

        char id[20];
        gotoxy(left, top);
        printf("Masukkan ID yang ingin dihapus: ");
        gotoxy(left+35, top);
        scanf("%s", id);
        getchar();

        // MENU KONFIRMASI
        char *opsi[] = { " Hapus", " Batal" };

        gotoxy(right+5, top+4);
        printf(" [↕] Pilih Input    ");
        gotoxy(right+5, top+5);
        printf(" [ENTER] Lanjut     ");

        int pilih = menuSelect(right+5, top+7, opsi, 2);

        if (pilih == 0)   // HAPUS
        {
            if (deleteKaryawan(id))
            {
                gotoxy(right-20, bot-1);
                printf("Data berhasil dihapus!");
                Sleep(1500);
                break;
            }
            else
            {
                gotoxy(right-20, bot-1);
                printf("ID tidak ditemukan!");
                Sleep(1500);
                break;
            }
        }
        else if (pilih == 1)
        {
            return;
        }
    }

    supadm(nama);
}

// Variable global/static untuk menyimpan posisi halaman terakhir
static int currentPage = 1;

void supadm(char nama[50])
{
    system("cls");
    applyColors();

    appname(43, 1);
    garisx(0,8);
    garisy(25,8);

    gotoxy(60, 10);
    printf("DATA KARYAWAN");

    int left = 28, right = 131, top = 11, bot = 34;

    frame(left, top, right, bot);

    for (int y = top; y < bot-1; y++) {
        gotoxy(left+8, y+1);  printf("│");
        gotoxy(left+25, y+1); printf("│");
        gotoxy(left+42, y+1); printf("│");
        gotoxy(left+58, y+1); printf("│");
        gotoxy(left+78, y+1); printf("│");
        gotoxy(left+88, y+1); printf("│");
    }
    gotoxy(left, top); printf("┌"); gotoxy(right,top); printf("┐");
    gotoxy(left, bot); printf("└"); gotoxy(right,bot); printf("┘");

    int yhead = top + 1;
    gotoxy(left+2, yhead);  printf("Id");
    gotoxy(left+10, yhead); printf("Nama Karyawan");
    gotoxy(left+27, yhead); printf("No. telp");
    gotoxy(left+44, yhead); printf("Email");
    gotoxy(left+60, yhead); printf("Alamat");
    gotoxy(left+80, yhead); printf("Posisi");
    gotoxy(left+90, yhead); printf("Status");

    for (int x = left+1; x < right; x++) {
        gotoxy(x, yhead+1); printf("─");
    }

    // Panggil fungsi read dan tampung total datanya
    int totalData = dataKaryawan(left, yhead + 2, currentPage);

    // Hitung Maksimal Halaman (Rumus: (Total-1) / 20 + 1)
    int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

    // Validasi agar page tidak error saat data dihapus habis
    if (currentPage > maxPage) currentPage = maxPage;
    if (currentPage < 1) currentPage = 1;

    // Tampilkan Info Halaman di bawah tabel
    gotoxy(left+1, bot+1);
    printf("Halaman: %d / %d (Total: %d)   [<] Sebelumnya  [>] Selanjutnya", currentPage, maxPage, totalData);


    // array menu
    char *menuSup[] = {
        " Data Karyawan",
        " Tambah Karyawan",
        " Ubah Karyawan",
        " Hapus Karyawan",
        " Keluar"
    };

    // Tampilan Kiri
    gotoxy(1,10); printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕] Pilih Menu");

    // Panggil menuSelect dengan jumlah index yang dinamis
    int pilih = menuSelect(1,12, menuSup, 5);

    if (pilih == -1)
    {
        if (currentPage > 1)
        {
            currentPage--;
        }
        supadm(nama);
    }
    else if (pilih == -2)
    {
        if (currentPage < maxPage)
        {
            currentPage++;
        }
        supadm(nama);
    }
    else if (pilih == 0)
    {
        currentPage = 1;
        supadm(nama);
    }
    else if (pilih == 1) createAdmin(nama);
    else if (pilih == 2) updateAdmin(nama);
    else if (pilih == 3) hapusAdmin(nama);
    else if (pilih == 4) exit(0);
}

void injectDummyData()
{
    printf("Memulai injeksi 50 data dummy...\n");
    srand(time(NULL)); // Inisiasi random seed

    // Array data acak
    char *names[] = {"budi", "citra", "dino", "eko", "fira", "gilang", "hadi", "ina", "joko", "kiki"};
    char *roles[] = {"kasir", "staff", "manajer"};
    char *domain[] = {"gmail.com", "yahoo.com", "mail.co", "corp.id"};
    int num_names = sizeof(names) / sizeof(names[0]);
    int num_roles = sizeof(roles) / sizeof(roles[0]);
    int num_domain = sizeof(domain) / sizeof(domain[0]);

    for (int i = 0; i < 50; i++)
    {
        Karyawan k;

        // 1. Username dan Password acak
        int name_index = rand() % num_names;
        sprintf(k.username, "%s%d", names[name_index], rand() % 99);
        sprintf(k.password, "pass%d", i + 100);

        // 2. Telepon (10 digit, harusnya 12-15 digit sesuai onlyNum, kita buat 12)
        // Note: Asumsi field telp di struct Karyawan cukup menampung 12 karakter.
        sprintf(k.telp, "0812345%05d", rand() % 100000);

        // 3. Email acak
        int domain_index = rand() % num_domain;
        sprintf(k.email, "%s%d@%s", names[name_index], rand() % 50, domain[domain_index]);

        // 4. Role acak (kasir, staff, manajer)
        int role_index = rand() % num_roles;
        strcpy(k.role, roles[role_index]);

        // 5. Alamat acak
        sprintf(k.alamat, "Jl. Dummy No. %d, Kota Test", i + 1);

        // 6. Status dan Poin default
        k.status = 1; // Aktif
        k.poin = 0;

        // 7. Panggil fungsi yang kamu buat untuk menyimpan dan membuat ID
        createKaryawan(k);
    }
    printf("Injeksi dummy data selesai! 50 data baru ditambahkan.\n");
    printf("Tekan ENTER untuk melanjutkan...\n");
    getchar(); // Tunggu user tekan enter
}

#endif //EATBOX_INTERFACE_H