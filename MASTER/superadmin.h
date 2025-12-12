#ifndef EATBOX_INTERFACE_H
#define EATBOX_INTERFACE_H

#include <time.h>

#include "../function.h"
#include "../data.h"
#include "../CRUD/create.h"
#include "../CRUD/read.h"
#include "../CRUD/delete.h"
#include "../CRUD/update.h"

void createKar();
void updateKar();
void hapusKar();
int lihatKar();
void dashboard(char *nama);
void supadm(char nama[50]);
int findIDByVisualNo(int targetNo, char *destID);

// Variable global/static untuk menyimpan posisi halaman terakhir
static int currentPage = 1;

void dashboard(char *nama)
{
    int left = 28, right = 131, top = 11, bot = 34;
    frame(left, top, right, bot);

    gotoxy(left + 5, top + 2);printf("DASHBOARD SUPERADMIN");
    gotoxy(left + 5, top + 3);for(int i=0; i<95; i++) printf("─");

    gotoxy(left + 5, top + 6);printf("Selamat Datang, %s!", cutname(nama));
    gotoxy(left + 5, top + 7);printf("Silakan pilih menu di samping.");

    int box1_x = left + 5, box_y = top + 10;
    frame(box1_x, box_y, box1_x + 30, box_y + 6);
    gotoxy(box1_x + 2, box_y + 1); printf("STATUS SISTEM");
    gotoxy(box1_x + 2, box_y + 3); printf("Database: Karyawan");

    gotoxy(left+2, bot-2); printf(" Role: SUPERADMIN");
}
void createKar()
{
    Karyawan a;
    memset(&a, 0, sizeof(a)); //ngisi buffer di a jadi 0 semua

    int filled_username=0, filled_password=0, filled_telp=0;
    int filled_email=0, filled_role=0, filled_alamat=0, filled_status=0;

    int left = 30, top  = 10, right = 105, bot   = 35;

    while (1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        frame(left, top, right, bot);
        gotoxy(1,10); printf("TAMBAH DATA KARYAWAN");

        int y = top + 2;
        gotoxy(left+2, y); printf("Username : %s", filled_username ? a.username : "");
        y+=2; gotoxy(left+2, y); printf("Password : "); if(filled_password) { for(int i=0;i<strlen(a.password);i++) printf("*"); }
        y+=2; gotoxy(left+2, y); printf("Telp     : %s", filled_telp ? a.telp : "");
        y+=2; gotoxy(left+2, y); printf("Email    : %s", filled_email ? a.email : "");
        y+=2; gotoxy(left+2, y); printf("Role     : %s", filled_role ? a.role : "");
        y+=2; gotoxy(left+2, y); printf("Alamat   : %s", filled_alamat ? a.alamat : "");
        y+=2; gotoxy(left+2, y); printf("Status   : %s", filled_status ? (a.status == 1 ? "1" : "0") : "");

        char *opsi[] = {" Username"," Password"," Telp"," Email"," Role"," Alamat"," Status"," Simpan"," Batal"};
        int pilih = menuSelect(1, 12, opsi, 9);

        switch (pilih)
        {
            case 0: // Username
                gotoxy(left+13, top+2); clearinput(left+13, top+2, 40); showcurs();
                inputtext(a.username); filled_username = strlen(a.username)>0;
                break;
            case 1: // Password
                gotoxy(left+13, top+4); clearinput(left+13, top+4, 40); showcurs();
                inputpass(a.password, left+2, top+4, "Password "); filled_password = strlen(a.password)>0;
                break;
            case 2: // Telp
                 do {
                    gotoxy(left+13, top+6); clearinput(left+13, top+6, 20); showcurs();
                    inputtext(a.telp);
                    if (onlyNum(a.telp)) filled_telp = 1;
                    else { gotoxy(left+13, top+7); printf("Nomor tidak valid!"); }
                } while (!filled_telp);
                clearinput(left+13, top+7, 20);
                break;
            case 3: // Email
                 do {
                    gotoxy(left+13, top+8); clearinput(left+13, top+8, 30); showcurs();
                    inputtext(a.email);
                    if (cekEmail(a.email)) filled_email = 1;
                    else { gotoxy(left+13, top+9); printf("Email tidak valid!"); }
                } while (!filled_email);
                clearinput(left+13, top+9, 30);
                break;
            case 4: // Role
                 do {
                    gotoxy(left+13, top+10); clearinput(left+13, top+10, 20); showcurs();
                    inputtext(a.role); a.role[strcspn(a.role, "\n")] = 0;
                    if (cekrole(a.role)) filled_role = 1;
                    else { gotoxy(left+13, top+11); printf("Role: manajer/staff/kasir"); }
                } while (!filled_role);
                clearinput(left+13, top+11, 20);
                break;
            case 5: // Alamat
                gotoxy(left+13, top+12); clearinput(left+13, top+12, 40); showcurs();
                inputtext(a.alamat); filled_alamat = strlen(a.alamat)>0;
                break;
            case 6: // Status (Toggle)
                a.status = (a.status == 1) ? 0 : 1; filled_status = 1;
                break;
            case 7: // Simpan
                if (filled_username && filled_password && filled_telp && filled_email && filled_role && filled_alamat && filled_status) {
                    createKaryawan(a);
                    gotoxy(right-30, bot-1); printf("Data berhasil ditambahkan!"); Sleep(1000);
                    return; // KEMBALI KE SUPADM
                } else {
                    gotoxy(right-30, bot-1); printf("Lengkapi data!"); Sleep(1000);
                }
                break;
            case 8: // Batal
                return; // KEMBALI KE SUPADM
        }
    }
}
void updateKar()
{
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    char inputNoStr[10];
    char realID[20]; // Ini buat nampung ID asli (KY00..)
    gotoxy(1,10); printf("UBAH DATA KARYAWAN");
    gotoxy(30,10);printf("Masukkan No. Urut: "); showcurs();
    if(inputid(inputNoStr) == 0) return;

    int noUrut = atoi(inputNoStr); // Convert string ke angka

    // CARI ID ASLI DARI NOMOR TERSEBUT
    if (findIDByVisualNo(noUrut, realID) == 0) {
        gotoxy(30,12); printf("Nomor %d tidak ditemukan!", noUrut);
        Sleep(1000); return;
    }

    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    if (!f) { return; }

    Karyawan a;
    int found = 0;
    char str[255];
    // Parsing manual agar aman
    while (fgets(str, sizeof(str), f)) {
        str[strcspn(str, "\n")] = 0;
        Karyawan temp;
        int p = sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               temp.id, temp.username, temp.password, temp.telp,
               temp.email, temp.role, temp.alamat, &temp.status);
        if(p < 8) continue;

        // Bandingkan dengan ID asli yang sudah didapat
        if(strcmp(temp.id, realID) == 0) { a = temp; found = 1; break; }
    }
    fclose(f);

    if (!found) { gotoxy(30,12); printf("ID tidak ditemukan!"); Sleep(1000); return; }

    int left = 30, top = 9, right = 105, bot = 35;
    while (1)
    {
        clearArea(27, 9, clearW, clearH);
        frame(left, top, right, bot);
        int y = top + 2;

        gotoxy(left+2, y); printf("Username : %s", a.username);
        y+=2; gotoxy(left+2, y); printf("Password : "); for(int i=0;i<strlen(a.password);i++) printf("*");
        y+=2; gotoxy(left+2, y); printf("Telp     : %s", a.telp);
        y+=2; gotoxy(left+2, y); printf("Email    : %s", a.email);
        y+=2; gotoxy(left+2, y); printf("Role     : %s", a.role);
        y+=2; gotoxy(left+2, y); printf("Alamat   : %s", a.alamat);
        y+=2; gotoxy(left+2, y); printf("Status   : %s", (a.status == 1 ? "1" : "0"));

        char *opsi[] = {" Username"," Password"," Telp"," Email"," Role"," Alamat"," Status"," Simpan"," Batal"};
        int pilih = menuSelect(1, 12, opsi, 9);

        switch (pilih)
        {
            case 0: gotoxy(left+13, top+2); clearinput(left+13, top+2, 40); showcurs(); inputtext(a.username); break;
            case 1: gotoxy(left+13, top+4); clearinput(left+13, top+4, 40); showcurs(); inputpass(a.password, left+2, top+4, "Password "); break;
            case 2:
                do { gotoxy(left+13, top+6); clearinput(left+13, top+6, 20); showcurs(); inputtext(a.telp);
                } while (!onlyNum(a.telp)); break;
            case 3:
                do { gotoxy(left+13, top+8); clearinput(left+13, top+8, 30); showcurs(); inputtext(a.email);
                } while (!cekEmail(a.email)); break;
            case 4:
                do { gotoxy(left+13, top+10); clearinput(left+13, top+10, 20); showcurs(); inputtext(a.role);
                } while (!cekrole(a.role)); break;
            case 5: gotoxy(left+13, top+12); clearinput(left+13, top+12, 40); showcurs(); inputtext(a.alamat); break;
            case 6: a.status = !a.status; break;
            case 7: if(updateKaryawan(&a))
            {
                gotoxy(right-30, bot-1); printf("Berhasil!"); Sleep(1000); return;
            } break;
            case 8: return;
        }
    }
}
void hapusKar()
{
    while (1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        char inputNoStr[10];
        char realID[20];

        gotoxy(1,10); printf("HAPUS DATA KARYAWAN ");
        gotoxy(30,10); printf("Masukkan No. Urut : "); // Minta Nomor

        showcurs();
        inputtext(inputNoStr);
        if (strlen(inputNoStr) == 0) return;

        int noUrut = atoi(inputNoStr);

        // Convert No -> ID
        if (findIDByVisualNo(noUrut, realID) == 0) {
            gotoxy(30, 12); printf("Nomor %d tidak ditemukan!", noUrut);
            Sleep(1000); continue;
        }

        gotoxy(30, 13); printf("Menghapus No %d (ID: %s)...", noUrut, realID);
        Sleep(500);

        // Hapus berdasarkan ID Asli
        if(deleteKaryawan(realID)) {
            gotoxy(30, 13); printf("Data berhasil dihapus!           "); Sleep(1000); return;
        } else {
            gotoxy(30, 13); printf("Gagal menghapus database!        "); Sleep(1000);
        }
    }
}
int lihatKar()
{
    int left = 28, right = 131, top = 11, bot = 34;
    gotoxy(60, 10); printf("DATA KARYAWAN");
    frame(left, top, right, bot);

    int yhead = top + 1;
    gotoxy(left+2, yhead);  printf("No");
    gotoxy(left+10, yhead); printf("Nama Karyawan");
    gotoxy(left+27, yhead); printf("No. telp");
    gotoxy(left+44, yhead); printf("Email");
    gotoxy(left+60, yhead); printf("Alamat");
    gotoxy(left+80, yhead); printf("Posisi");
    gotoxy(left+90, yhead); printf("Status");

    for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

    int Data = dataKaryawan(left, yhead + 2, currentPage);
    return Data;
}
void supadm(char nama[50])
{
    system("cls");
    applyColors();appname(43, 1);
    garisx(0,8);
    garisy(25,8); // Garis Sidebar

    gotoxy(1,10); printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕] Pilih Menu");

    int currentView = 0;

    char *menuSup[] = {
        " Data Karyawan", " Tambah Karyawan", " Ubah Karyawan", " Hapus Karyawan", " Keluar"
    };

    while(1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        clearinput(1,10,24);

        int totalData = 0;
        int maxPage = 1;

        if (currentView == 0) {
            dashboard(nama);
        }
        else if (currentView == 1) {
            totalData = lihatKar(); // Render tabel & dapatkan total data
            maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

            // Render Footer Paging
            int bot = 34; // Sesuaikan dengan bot di lihatKar
            gotoxy(29, bot+1);
            setRGBColor(202, 40, 44, 1);
            setRGBColor(251, 255, 199,0);
            printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentPage, maxPage, totalData);
        }

        // 4. Handle Sidebar Title (Biar balik lagi kalo abis diganti submenu)
        if(currentView == 0) { gotoxy(1,10); printf("Halo, %s", cutname(nama)); }
        else if(currentView == 1) { gotoxy(1,10); printf("DATA KARYAWAN"); }

        // 5. Menu Select (Program Pauses Here)
        int pilih = menuSelect(1, 12, menuSup, 5);

        // 6. Logic Navigasi
        if (pilih == -1) { // Prev Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentPage > 1) currentPage--;
        }
        else if (pilih == -2) { // Next Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentPage < maxPage) currentPage++;
        }
        else if (pilih == 0) { // DATA KARYAWAN
            currentView = 1;
            currentPage = 1;
        }
        else if (pilih == 1) { // TAMBAH
            createKar(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 1; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 2) { // UBAH
            updateKar();
            currentView = 1;
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 3) { // HAPUS
            hapusKar();
            currentView = 1;
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 4) { // KELUAR
            exit(0);
        }
    }
}

int findIDByVisualNo(int targetNo, char *destID)
{
    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    if (!f) return 0;

    Karyawan list[500], temp;
    char str[512];
    int totalData = 0;

    // 1. Load data persis seperti di read.h
    while (fgets(str, sizeof(str), f)) {
        str[strcspn(str, "\n")] = 0;
        int parsed = sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               list[totalData].id, list[totalData].username, list[totalData].password,
               list[totalData].telp, list[totalData].email, list[totalData].role,
               list[totalData].alamat, &list[totalData].status);
        if (parsed < 8) continue;
        totalData++;
    }
    fclose(f);

    // 2. Sorting persis seperti di read.h (Aktif diatas)
    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            if (list[j].status < list[j+1].status) {
                temp = list[j]; list[j] = list[j+1]; list[j+1] = temp;
            }
        }
    }

    // 3. Ambil ID berdasarkan index (targetNo - 1)
    if (targetNo > 0 && targetNo <= totalData) {
        strcpy(destID, list[targetNo - 1].id); // Copy ID asli ke variable tujuan
        return 1;
    }
    return 0; // Nomor tidak ada
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

        int name_index = rand() % num_names;
        sprintf(k.username, "%s%d", names[name_index], rand() % 99);
        sprintf(k.password, "pass%d", i + 100);

        sprintf(k.telp, "0812345%05d", rand() % 100000);

        int domain_index = rand() % num_domain;
        sprintf(k.email, "%s%d@%s", names[name_index], rand() % 50, domain[domain_index]);

        int role_index = rand() % num_roles;
        strcpy(k.role, roles[role_index]);

        sprintf(k.alamat, "Jl. Dummy No. %d, Kota Test", i + 1);

        k.status = 1; // Aktif

        createKaryawan(k);
    }
    printf("Injeksi dummy data selesai! 50 data baru ditambahkan.\n");
    printf("Tekan ENTER untuk melanjutkan...\n");
    getchar(); // Tunggu user tekan enter
}

#endif //EATBOX_INTERFACE_H