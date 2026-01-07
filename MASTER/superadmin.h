#ifndef EATBOX_INTERFACE_H
#define EATBOX_INTERFACE_H

#include <time.h>

#include "../function.h"
#include "../data.h"
#include "../CRUD/create.h"
#include "../CRUD/read.h"
#include "../CRUD/delete.h"
#include "../CRUD/update.h"
#define KEY_F2 60

void createKar();
void updateKar();
void hapusKar();
void detailKar();
int lihatKar();
void dashboard(char *nama);
void supadm(char nama[50]);
void formEdit(Karyawan *a);
int finID(int targetNo, char *destID);
int gantiPass(char *passAwal);

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

    int left = 30, top  = 11, right = 105, bot   = 35;

    while (1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        frame(left, top, right, bot);
        gotoxy(1,10); printf("TAMBAH DATA KARYAWAN");
        gotoxy(left, top-1); printf(" [ESC] Kembali    [ENTER] Lanjut");

        int y = top + 2;
        gotoxy(left+2, y);       printf("Nama Pengguna: ");
        y+=2; gotoxy(left+2, y); printf("Kata Sandi   : ");
        y+=2; gotoxy(left+2, y); printf("Nama Lengkap : ");
        y+=2; gotoxy(left+2, y); printf("No. Telp     : ");
        y+=2; gotoxy(left+2, y); printf("Email        : ");
        y+=2; gotoxy(left+2, y); printf("Role         : ");
        y+=2; gotoxy(left+2, y); printf("Alamat       : ");

        // 1. USERNAME
        do {
            clearinput(left+17, top+2, 35); gotoxy(left+17, top+2); showcurs();
            if (inputusname(a.username) == 0) return;
            if (strlen(a.username) == 0) { gotoxy(left+17, top+3); printf("Wajib diisi!"); }
            else if (strlen(a.username) < 4) { //Minimal 4 huruf biar gak kependekan
                gotoxy(left+17, top+3); printf("Minimal 4 karakter!");
            }
            else if (isDuplicate("username", a.username, "")) { // CEK DUPLIKAT
                gotoxy(left+17, top+3); printf("Nama pengguna sudah dipakai!");
            }
        } while (strlen(a.username) == 0);
        clearinput(left+17, top+3, 40);

        // 2. PASSWORD
        do {
            clearinput(left+17, top+4, 35); gotoxy(left+17, top+4); showcurs();
            if (inputpass(a.password, left+2, top+4, "Kata Sandi   ") == 0) return;
            if (strlen(a.password) == 0) { gotoxy(left+17, top+5); printf("Wajib diisi!"); }
        } while (strlen(a.password) == 0);
        clearinput(left+17, top+5, 30);

        // 3. NAMA LENGKAP (VALIDASI KHUSUS)
        do {
            clearinput(left+17, top+6, 35); gotoxy(left+17, top+6); showcurs();
            if (inputName(a.nama) == 0) return;

            if (strlen(a.nama) == 0) {
                gotoxy(left+17, top+7); printf("Nama wajib diisi!");
            } else if (strlen(a.nama) < 3) {
                 gotoxy(left+17, top+7); printf("Nama terlalu pendek!");
            } else {
                break;
            }
        } while (1);
        clearinput(left+17, top+7, 40);

        // 4. TELP
        do {
            clearinput(left+17, top+8, 20); gotoxy(left+17, top+8); showcurs();
            if (inputTelp08(a.telp) == 0) return;
            if (strlen(a.telp) < 10) { clearinput(left+17, top+9, 40); gotoxy(left+17, top+9); printf("Min 10 digit!"); }
            else if (isDuplicate("telp", a.telp, "")) { // Cek Duplikat
                gotoxy(left+17, top+9); printf("Nomor sudah terdaftar!");
            }
            else break;
        } while (1);
        clearinput(left+17, top+9, 40);

        // 5. EMAIL
        do {
            clearinput(left+17, top+10, 30); gotoxy(left+17, top+10); showcurs();
            if (inputtext(a.email) == 0) return;
            if (!cekEmail(a.email)) { clearinput(left+17, top+11, 40); gotoxy(left+17, top+11); printf("Format salah!"); }
            else if (isDuplicate("email", a.email, "")) { // Cek Duplikat
                gotoxy(left+17, top+11); printf("Email sudah terdaftar!");
            }
            else break;
        } while (1);
        clearinput(left+17, top+11, 40);

        // 6. ROLE
        do {
            clearinput(left+17, top+12, 20); gotoxy(left+17, top+12); showcurs();
            if (inputtext(a.role) == 0) return;
            if (!cekrole(a.role)) { gotoxy(left+17, top+13); printf("manajer/staff/kasir"); }
            else break;
        } while (1);
        clearinput(left+17, top+13, 30);

        // 7. ALAMAT
        do {
            clearinput(left+17, top+14, 40); gotoxy(left+17, top+14); showcurs();
            if (inputbebas(a.alamat) == 0) return;
            if (strlen(a.alamat) == 0) { gotoxy(left+17, top+15); printf("Wajib diisi!"); }
            else break;
        } while (1);
        clearinput(left+17, top+15, 30);

        // --- PROSES SIMPAN ---
        a.status = 1;
        createKaryawan(a);
        popupAlert(1,"Data berhasil ditambahkan!");
        Sleep(1000);
        return;
    }
}
void updateKar()
{
    while (1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        char inputNoStr[10];
        char realID[20]; // Ini buat nampung ID asli (KY00..)

        gotoxy(30, 10); printf("[ESC] Batal   [ENTER] Lanjut");
        gotoxy(1,10); printf("UBAH DATA KARYAWAN");
        gotoxy(30,11);printf("Masukkan No. Urut: "); showcurs();

        if(inputid(inputNoStr) == 0) return;
        int noUrut = atoi(inputNoStr); // Convert string ke angka

        // CARI ID ASLI DARI NOMOR TERSEBUT
        if (finID(noUrut, realID) == 0) {
            gotoxy(30,12); printf("Nomor %d tidak ditemukan!", noUrut); Sleep(1000); continue;
        }

        FILE *f = fopen("../FILE/karyawan.dat", "rb");
        if (!f) { return; }

        Karyawan a;
        int found = 0;
        char str[255];
        // Parsing manual agar aman
        while (fgets(str, sizeof(str), f)) {
            str[strcspn(str, "\n")] = 0;
            sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
                   a.id, a.username, a.password, a.nama, a.telp,
                   a.email, a.role, a.alamat, &a.status);

            // Bandingkan dengan ID asli yang sudah didapat
            if(strcmp(a.id, realID) == 0) { found = 1; break; }
        }
        fclose(f);

        if (!found) { gotoxy(30,12); printf("ID tidak ditemukan!"); Sleep(1000); return; }

        int left = 30, top = 11, right = 105, bot = 35;
        char buffer[100];

        formEdit(&a);

        // 1. Username
        clearinput(left+17, top+2, 35); gotoxy(left+17, top+2); showcurs();
        if (inputusname(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(a.username, buffer);
        if (strlen(buffer) < 4) {
            gotoxy(left+17, top+3); printf("Minimal 4 karakter!");
        }
        // CEK DUPLIKAT (a.id sebagai pengecualian)
        else if (isDuplicate("username", buffer, a.id)) {
            gotoxy(left+17, top+3); printf("Nama pengguna sudah dipakai!");
        }
        gotoxy(left+17, top+2); printf("%-35s", a.username);
        clearinput(left+17, top+3, 40);

        // 2. Password
        clearinput(left+17, top+4, 35);
        gotoxy(left+17, top+4);
        printf("[F2] Ganti / [ENTER] Lewati");

        while (1)
        {
            int key = _getch();

            // --- JIKA ENTER (LEWATI) ---
            if (key == 13) {
                break;
            }

            // --- JIKA ESC (BATAL UPDATE) ---
            else if (key == 27) {
                return;
            }

            // --- JIKA TOMBOL FUNGSI ---
            else if (key == 0 || key == 224) {
                key = _getch();

                if (key == KEY_F2) {

                    if (gantiPass(a.password)) {
                        // SUKSES: Alert DULU, baru bersihkan layar
                        popupAlert(1, "Password Berhasil Diubah!");

                        // [FIX] Redraw form SETELAH alert biar alertnya ilang
                        formEdit(&a);
                        gotoxy(32, 33); printf("Selesaikan untuk menyimpan perubahan...");
                        break;
                    } else {
                        // BATAL: Cukup redraw form untuk hapus kotak gantiPass
                        formEdit(&a);

                        // Tulis ulang instruksi
                        gotoxy(left+17, top+4);
                        printf("[F2] Ganti / [ENTER] Lewati");
                    }
                }
            }
        }
        // Tutup instruksi dengan bintang
        clearinput(left+17, top+4, 35);
        gotoxy(left+17, top+4); for(int i=0;i<strlen(a.password);i++) printf("*");

        // 3. Nama Lengkap
        clearinput(left+17, top+6, 35); gotoxy(left+17, top+6); showcurs();
        if (inputName(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(a.nama, buffer);
        gotoxy(left+17, top+6); printf("%-35s", a.nama);

        // 4. Telp
        do {
            clearinput(left+17, top+8, 20); gotoxy(left+17, top+8); showcurs();
            if (inputTelp08(buffer) == 0) return;
            if (strcmp(buffer, "08") == 0) break; // Skip

            if (strlen(buffer) < 10) { gotoxy(left+17, top+9); printf("Min 10 digit!"); }
            else if (isDuplicate("telp", buffer, a.id)) { // Cek Duplikat (kecuali ID sendiri)
                gotoxy(left+17, top+9); printf("Nomor sudah terdaftar!");
            }
            else { strcpy(a.telp, buffer); break; }
        } while (1);
        clearinput(left+17, top+9, 30);
        gotoxy(left+17, top+8); printf("%-20s", a.telp);

        // 5. Email
        do {
            clearinput(left+17, top+10, 30); gotoxy(left+17, top+10); showcurs();
            if (inputtext(buffer) == 0) return;
            if (strlen(buffer) == 0) break;

            if (!cekEmail(buffer)) { gotoxy(left+17, top+11); printf("Format salah!"); }
            else if (isDuplicate("email", buffer, a.id)) { // Cek Duplikat (kecuali ID sendiri)
                gotoxy(left+17, top+11); printf("Email sudah terdaftar!");
            }
            else { strcpy(a.email, buffer); break; }
        } while (1);
        clearinput(left+17, top+11, 30);
        gotoxy(left+17, top+10); printf("%-30s", a.email);

        // 6. Role (Sama kayak sebelumnya)
        clearinput(left+17, top+12, 20); gotoxy(left+17, top+12);
        if (inputtext(buffer) == 0) return;
        if (strlen(buffer) > 0 && cekrole(buffer)) strcpy(a.role, buffer);
        gotoxy(left+17, top+12); printf("%-20s", a.role);

        // 7. Alamat
        clearinput(left+17, top+14, 40); gotoxy(left+17, top+14);
        if (inputbebas(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(a.alamat, buffer);
        gotoxy(left+17, top+14); printf("%-40s", a.alamat);

        // --- KONFIRMASI SIMPAN ---
        if (popupConfirm("Simpan Perubahan Data Ini?", "Ya", "Batal"))
        {
            // User pilih ENTER (Ya)
            if(updateKaryawan(&a)) {
                popupAlert(1,"Data Berhasil Diupdate!");
                return; // Keluar dari menu update
            } else {
                popupAlert(0,"Gagal Perbarui Data!");
            }
        }
        else
        {
            //create ulang hapus popup
            clearArea(27, 9, clearW, clearH);
            frame(left, top, right, bot);
        }
    }
}
void hapusKar(){
    Karyawan target;
    while (1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        char inputNoStr[10];
        char realID[20];

        gotoxy(30, 10); printf("[ESC] Batal   [ENTER] Lanjut");
        gotoxy(1,10); printf("HAPUS DATA KARYAWAN ");
        gotoxy(30,12); printf("Masukkan No. Urut : ");

        showcurs();
        inputtext(inputNoStr);
        if (strlen(inputNoStr) == 0) return;

        int noUrut = atoi(inputNoStr);

        // Convert No -> ID
        if (finID(noUrut, realID) == 0) {
            gotoxy(30, 12); printf("Nomor %d tidak ditemukan!", noUrut);
            Sleep(1000); continue;
        }
        
        FILE *f = fopen("../FILE/karyawan.dat", "r");
        char line[512];
        int ketemu = 0;

        if (f) {
            while (fgets(line, sizeof(line), f)) {
                Karyawan temp;
                // Parse baris file ke struct temp (Sesuaikan format sscanf dengan datamu)
                sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
                       temp.id, temp.username, temp.password,
                       temp.nama, temp.telp, temp.email, temp.role,
                       temp.alamat, &temp.status);

                // Cek apakah ID-nya cocok
                if (strcmp(temp.id, realID) == 0) {
                    target = temp; // Salin data ke variabel target
                    ketemu = 1;
                    break;
                }
            }
            fclose(f);
        }
        if(!ketemu) { popupAlert(0,"Error: Data ID tidak sinkron."); continue; }

        int y = 14;
        gotoxy(30, y++); printf("ID           : %s", target.id);
        gotoxy(30, y++); printf("Nama Pengguna: %s", target.username);
        gotoxy(30, y++); printf("Nama Lengkap : %s", target.nama);
        gotoxy(30, y++); printf("No. Telp     : %s", target.telp);
        gotoxy(30, y++); printf("Email        : %s", target.email);
        gotoxy(30, y++); printf("Alamat       : %s", target.alamat);
        gotoxy(30, y++); printf("Role         : %s", target.role);
        // Tampilkan status text
        gotoxy(30, y++); printf("Status     : %s", (target.status == 1) ? "Aktif" : "Non-Aktif");
        gotoxy(30,y++);printf("tekan ENTER untuk lanjut..."); getchar();

        // --- KONFIRMASI SIMPAN ---
        if (popupConfirm("Non-aktifkan karyawan Ini?", "Ya", "Batal"))
        {
            // User pilih ENTER (Ya)
            if(deleteKaryawan(realID)) {
                setRGBColor(202, 40, 44, 1);
                setRGBColor(251, 255, 199,0);
                gotoxy(30, 13); printf("Mengubah Data No %d (ID: %s)...", noUrut, realID);
                Sleep(500);
                popupAlert(1,"Status Berhasil Diubah!");
                return; // Keluar dari menu update
            } else {
                popupAlert(0,"Gagal mengubah data!");
            }
        }
        else
        { clearArea(27, 9, clearW, clearH); }
    }
}
void detailKar(){
    while (1) {
        // --- 1. SIAPKAN BACKGROUND ---
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        char inputNoStr[10];
        char realID[20];

        // --- 2. INPUT NOMOR URUT ---

        gotoxy(1, 10);  printf("DETAIL DATA KARYAWAN");
        gotoxy(30, 10); printf("[ESC] Kembali");
        gotoxy(30, 12); printf("Masukkan No. Urut (Dari Tabel): ");

        inputtext(inputNoStr);
        if (strlen(inputNoStr) == 0) return;

        int noUrut = atoi(inputNoStr);

        // Convert No -> ID
        if (finID(noUrut, realID) == 0) {
            gotoxy(30, 13); printf("Nomor %d tidak ditemukan!", noUrut);
            Sleep(1000); continue;
        }

        // --- 4. AMBIL DATA LENGKAP DARI FILE ---
        FILE *f = fopen("../FILE/karyawan.dat", "rb");
        if (!f) return;

        Karyawan a;
        int found = 0;
        char str[512];

        while (fgets(str, sizeof(str), f)) {
            str[strcspn(str, "\n")] = 0;
            // Parse data lengkap (9 Kolom)
            sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
                   a.id, a.username, a.password, a.nama, a.telp,
                   a.email, a.role, a.alamat, &a.status);

            if (strcmp(a.id, realID) == 0) {
                found = 1;
                break;
            }
        }
        fclose(f);

        if (!found) {
            popupAlert(0,"Database Error: ID Hilang."); continue;
        }

        // --- 5. TAMPILKAN OVERLAY (KOTAK DETAIL) ---
        // Bersihkan layar lagi biar bersih pas nampilin kotak
        clearArea(27, 9, clearW, clearH);

        int left = 30, top = 11, right = 105, bot = 32;
        frame(left, top, right, bot);

        gotoxy(left + 2, top - 1);
        printf("[ESC] / [ENTER] Cari Nomor Lain");

        setRGBColor(202, 40, 44, 1);
        setRGBColor(251, 255, 199,0);
        gotoxy(left + 25, top + 2);
        printf("DETAIL KARYAWAN");

        int y = top + 5;
        int xLabel = left + 5;
        int xTitik = left + 25;
        int xValue = left + 27;

        // TAMPILKAN DATA
        gotoxy(xLabel, y); printf("ID Karyawan");      gotoxy(xTitik, y); printf(":"); gotoxy(xValue, y); printf("%s", a.id);
        y++;
        gotoxy(xLabel, y); printf("Nama Pengguna");    gotoxy(xTitik, y); printf(":"); gotoxy(xValue, y); printf("%s", a.username);
        y++;
        gotoxy(xLabel, y); printf("Nama Lengkap");     gotoxy(xTitik, y); printf(":"); gotoxy(xValue, y); printf("%s", a.nama);
        y++;
        gotoxy(xLabel, y); printf("Role / Posisi");    gotoxy(xTitik, y); printf(":"); gotoxy(xValue, y); printf("%s", a.role);
        y++;
        gotoxy(xLabel, y); printf("No. Telepon");      gotoxy(xTitik, y); printf(":"); gotoxy(xValue, y); printf("%s", a.telp);
        y++;
        gotoxy(xLabel, y); printf("Email");            gotoxy(xTitik, y); printf(":"); gotoxy(xValue, y); printf("%s", a.email);
        y++;
        gotoxy(xLabel, y); printf("Status");           gotoxy(xTitik, y); printf(":"); gotoxy(xValue, y);

        // Warna status biar cakep
        if(a.status == 1) { printf("AKTIF"); }
        else { printf("NON-AKTIF"); }

        y+=2;

        // ALAMAT (Dengan Logic Word Wrap biar gak nabrak garis)
        gotoxy(xLabel, y); printf("Alamat Lengkap");   gotoxy(xTitik, y); printf(":");
        gotoxy(xValue, y);

        char *ptr = a.alamat;
        int maxLen = (right - xValue) - 2; // Batas kanan
        int count = 0;

        while(*ptr) {
            printf("%c", *ptr);
            count++;
            ptr++;
            // Kalau sudah mentok kanan, pindah baris bawahnya
            if(count >= maxLen) {
                y++;
                gotoxy(xValue, y);
                count = 0;
            }
        }

        // --- 6. TUNGGU TOMBOL
        getch(); // Tekan apa aja untuk loop lagi (minta input nomor lagi)
    }
}
int lihatKar(){
    int left = 28, right = 131, top = 11, bot = 34;
    gotoxy(60, 10); printf("DATA KARYAWAN");
    frame(left, top, right, bot);

    int yhead = top + 1;
    gotoxy(left+2, yhead);  printf("No");
    gotoxy(left+6, yhead);  printf("Nama Pengguna");
    gotoxy(left+20, yhead); printf("Nama Lengkap");
    gotoxy(left+36, yhead); printf("No. Telp");
    gotoxy(left+50, yhead); printf("Email");
    gotoxy(left+66, yhead); printf("Alamat");
    gotoxy(left+84, yhead); printf("Posisi");
    gotoxy(left+93, yhead); printf("Status");

    for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

    int Data = dataKaryawan(left, yhead + 2, currentPage);
    return Data;
}
void supadm(char nama[50]){
    system("cls");
    applyColors();appname(43, 1);
    garisx(0,8);
    garisy(25,8); // Garis Sidebar

    gotoxy(1,10); printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕] Pilih Menu");

    int currentView = 0;

    char *menuSup[] = {
        " Data Karyawan", " Detail Karyawan", " Tambah Karyawan", " Ubah Karyawan", " Hapus Karyawan", " Keluar"
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
            int bot = 34;
            gotoxy(29, bot+1);
            setRGBColor(202, 40, 44, 1);
            setRGBColor(251, 255, 199,0);
            printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentPage, maxPage, totalData);
        }

        // 4. Handle Sidebar Title (Biar balik lagi kalo abis diganti submenu)
        if(currentView == 0) { gotoxy(1,10); printf("Halo, %s", cutname(nama)); }
        else if(currentView == 1) { gotoxy(1,10); printf("DATA KARYAWAN"); }

        // 5. Menu Select (Program Pauses Here)
        int pilih = menuSelect(1, 12, menuSup, 6);

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
        else if (pilih == 1) { // CARI KARYAWAN
            detailKar();
            // Setelah search selesai, kembalikan tampilan
            currentView = 0; // Atau 1 terserah mau balik kemana
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 2) { // TAMBAH
            createKar(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 1; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 3) { // UBAH
            updateKar();
            currentView = 1;
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 4) { // HAPUS
            hapusKar();
            currentView = 1;
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 5) { // KELUAR
            exit(0);
        }
    }
}

void formEdit(Karyawan *a)
{
    int left = 30, top = 11, right = 105, bot = 35;
    clearArea(27, 9, consoleW() - 27, consoleH() - 9);
    frame(left, top, right, bot);

    gotoxy(1,10); printf("UBAH DATA KARYAWAN  ");
    clearinput(left, top-1, 40);
    gotoxy(left, top-1); printf(" [ESC] Batal   [ENTER] Lewati/Lanjut");

    int y = top + 2;

    // Tampilkan Data Lama (Sebagai referensi user)
    gotoxy(left+2, y);       printf("Nama Pengguna: %s", a->username);
    y+=2; gotoxy(left+2, y); printf("Kata Sandi   : "); for(int i=0;i<strlen(a->password);i++) printf("*");
    y+=2; gotoxy(left+2, y); printf("Nama Lengkap : %s", a->nama);
    y+=2; gotoxy(left+2, y); printf("No. Telp     : %s", a->telp);
    y+=2; gotoxy(left+2, y); printf("Email        : %s", a->email);
    y+=2; gotoxy(left+2, y); printf("Role         : %s", a->role);
    y+=2; gotoxy(left+2, y); printf("Alamat       : %s", a->alamat);
    // STATUS HANYA DITAMPILKAN (READ ONLY)
    y+=2; gotoxy(left+2, y); printf("Status       : %s", (a->status == 1 ? "Aktif" : "Non-Aktif"));
}
int finID(int targetNo, char *destID){
    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    if (!f) return 0;

    Karyawan list[500], temp;
    char str[512];
    int totalData = 0;

    // 1. Load data persis seperti di read.h
    while (fgets(str, sizeof(str), f)) {
        str[strcspn(str, "\n")] = 0;
        int parsed = sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               list[totalData].id, list[totalData].username, list[totalData].password,
               list[totalData].nama,
               list[totalData].telp, list[totalData].email, list[totalData].role,
               list[totalData].alamat, &list[totalData].status);

        if (parsed < 9) continue; // Pastikan 9 data terbaca
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
int gantiPass(char *passAwal)
{
    int cw = consoleW(), ch = consoleH();
    int w = 50, h = 12;
    int x = (cw - w) / 2, y = (ch - h) / 2;

    char oldPass[50], newPass[50], confirmPass[50];

    drawGantiPassBox(x, y, w, h);

    // ==========================================
    // STEP 1: INPUT PASSWORD LAMA
    // ==========================================
    gotoxy(x+5, y+6); printf("Kata Sandi Lama  :");
    do {
        clearinput(x+24, y+6, 25); gotoxy(x+24, y+6); showcurs();
        if (inputpass(oldPass, x+5, y+6, "Kata Sandi Lama  ") == 0) return 0; // ESC pressed

        // Validasi: Apakah sesuai password user sekarang?
        if (strcmp(oldPass, passAwal) != 0) {
            // Tampilkan error di sebelah kanan atau baris bawah
            gotoxy(x+5, y+7); printf("Password Salah!");
            Sleep(1000); // Tahan sebentar biar user baca
            clearinput(x+5, y+7, 20); // Hapus pesan error
        } else {
            break; // Jika benar, keluar loop lanjut ke Step 2
        }
    } while (1);

    // ==========================================
    // STEP 2: INPUT PASSWORD BARU
    // ==========================================
    gotoxy(x+5, y+8); printf("Kata Sandi Baru  :");
    do {
        clearinput(x+24, y+8, 25); gotoxy(x+24, y+8); showcurs();
        if (inputpass(newPass, x+5, y+8, "Kata Sandi Baru  ") == 0) return 0;

        // Validasi: Panjang karakter
        if (strlen(newPass) < 4) {
            gotoxy(x+5, y+9); printf("Min. 4 Karakter!");
            Sleep(1000);
            clearinput(x+5, y+9, 20);
        } else {
            break;
        }
    } while (1);


    // ==========================================
    // STEP 3: KONFIRMASI PASSWORD
    // ==========================================
    gotoxy(x+5, y+10); printf("Ulangi Kata Sandi:");
    do {
        clearinput(x+24, y+10, 25); gotoxy(x+24, y+10); showcurs();
        if (inputpass(confirmPass, x+5, y+10, "Ulangi Kata Sandi") == 0) return 0;

        // Validasi: Cocokkan dengan password baru
        if (strcmp(newPass, confirmPass) != 0) {
            gotoxy(x+5, y+11); printf("Tidak Cocok!");
            Sleep(1000);
            clearinput(x+5, y+11, 20);
        } else {
            break;
        }
    } while (1);

    // ==========================================
    // FINISHING
    // ==========================================
    strcpy(passAwal, newPass); // Update password di struct/variable utama
    return 1;
}

void injectDummyData(){
    printf("Menambahkan 20 data dummy ke database...\n");
    srand(time(NULL));

    // 1. DATA MASTER (NAMA LENGKAP)
    char *fullNames[] = {
        "Andra Wijaya", "Ayunda Risu", "Dimas Anggara", "Fikri Haikal", "Hana Pertiwi",
        "Ilham Saputra", "Karin Novilda", "Lutfi Halim", "Maya Estianty", "Nabil Makarim",
        "Raisa Andriana","Satria Baja", "Tara Basro", "Vania Larissa", "Yoga Pratama",
        "Budi Santoso", "Siti Aminah", "Reza Rahadian", "Dian Sastro", "Joko Anwar"
    };

    char *domain[] = {"gmail.com", "yahoo.com", "outlook.com"};
    int num_names = sizeof(fullNames) / sizeof(fullNames[0]);

    // 2. SETUP DISTRIBUSI ROLE
    char *rolePool[20];
    int r = 0;
    for(int i=0; i<2; i++) rolePool[r++] = "manajer";
    for(int i=0; i<8; i++) rolePool[r++] = "staff";
    for(int i=0; i<10; i++) rolePool[r++] = "kasir";

    // 3. KOCOK ROLE
    for (int i = 0; i < 20; i++) {
        int swapIdx = rand() % 20;
        char *temp = rolePool[i];
        rolePool[i] = rolePool[swapIdx];
        rolePool[swapIdx] = temp;
    }

    // 4. GENERATE DATA
    for (int i = 0; i < 20; i++)
    {
        Karyawan k;
        int idx = rand() % num_names;

        // Nama Lengkap
        strcpy(k.nama, fullNames[idx]);

        // Username (Kata depan + angka acak)
        char tempName[50];
        strcpy(tempName, fullNames[idx]);
        char *firstName = strtok(tempName, " ");
        sprintf(k.username, "%s%d", strlwr(firstName), rand() % 999);

        // Data Lain
        sprintf(k.password, "pass%d", i + 100);
        sprintf(k.telp, "0812345%05d", rand() % 100000);
        sprintf(k.email, "%s@%s", k.username, domain[rand() % 3]);
        sprintf(k.alamat, "Jl. Dummy No. %d", i + 1);

        strcpy(k.role, rolePool[i]);
        k.status = 1;

        // CREATE (MODE APPEND/NAMBAH)
        // Pastikan fungsi createKaryawan pakai "ab+"
        createKaryawan(k);
    }

    printf("Injeksi selesai! 20 data baru telah ditambahkan.\n");
    printf("Tekan ENTER untuk melanjutkan...\n");
    getchar();
}

#endif //EATBOX_INTERFACE_H