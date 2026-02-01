#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../../../include/data.h"
#include "../../../include/function.h"
#include "../../../include/master/karyawan/superadmin.h"
#include "../../../include/login.h"

#define KEY_F2 60


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
            if (strlen(a.username) == 0) { gotoxy(left+17, top+3); printf("Wajib diisi!       "); continue; }
            if (strlen(a.username) < 4) { //Minimal 4 huruf biar gak kependekan
                gotoxy(left+17, top+3); printf("Minimal 4 karakter!");
                continue;
            }
            if (isDuplicate("username", a.username, "")) { // CEK DUPLIKAT
                gotoxy(left+17, top+3); printf("Nama pengguna sudah dipakai!"); continue;
            }
            break;
        } while (1);
        clearinput(left+17, top+3, 40);

        // 2. PASSWORD
        do {
            clearinput(left+17, top+4, 35); gotoxy(left+17, top+4); showcurs();
            if (inputpass(a.password, left+2, top+4, "Kata Sandi   ") == 0) return;
            if (strlen(a.password) == 0) { gotoxy(left+17, top+5); printf("Wajib diisi!       "); continue;}
            if (strlen(a.password) < 6) {  gotoxy(left+17, top+5); printf("Minimal 6 karakter!");continue;}
            break;
        } while (1);
        clearinput(left+17, top+5, 30);

        // 3. NAMA LENGKAP (VALIDASI KHUSUS)
        do {
            clearinput(left+17, top+6, 35); gotoxy(left+17, top+6); showcurs();
            if (inputName(a.nama) == 0) return;

            if (strlen(a.nama) == 0) {
                gotoxy(left+17, top+7);  printf("Nama wajib diisi!");
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
            if (!cekEmail(a.email)) { clearinput(left+17, top+11, 40);
                gotoxy(left+17, top+11); printf("Email tidak sesuai / Format salah!"); }
            else if (isDuplicate("email", a.email, "")) { // Cek Duplikat
                gotoxy(left+17, top+11); printf("Email sudah terdaftar!");
            }
            else break;
        } while (1);
        clearinput(left+17, top+11, 40);

        // 6. ROLE
        do {
            clearinput(left+17, top+12, 20); gotoxy(left+17, top+12); showcurs();
            if (inputName(a.role) == 0) return;
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

        gotoxy(left, top-1); printf(" [ESC] Kembali    [ENTER] Lanjut");
        gotoxy(1,10); printf("UBAH DATA KARYAWAN");
        gotoxy(30,11);printf("Masukkan No. Urut: "); showcurs();

        if(inputid(inputNoStr) == 0) return;
        int noUrut = atoi(inputNoStr); // Convert string ke angka

        // CARI ID ASLI DARI NOMOR TERSEBUT
        if (finID(noUrut, realID) == 0) {
            gotoxy(30,12); printf("Nomor %d tidak ditemukan!", noUrut); Sleep(1000); continue;
        }

        FILE *f = fopen(FILE_KARYAWAN, "rb");
        if (!f) return;

        Karyawan a;
        int found = 0;

        while (fread(&a, sizeof(Karyawan), 1, f)) {
            if (strcmp(a.id, realID) == 0) {
                found = 1;
                break;
            }
        }
        fclose(f);

        if (!found) { gotoxy(30,12); printf("ID tidak ditemukan!"); Sleep(1000); return; }

        int left = 30, top = 11, right = 105, bot = 35;
        char buffer[100];

        formEdit(&a);

        // 1. Username
        while (1)
        {
            gotoxy(left+17, top+2); showcurs();
            setRGBColor(251, 255, 199, 0);
            if (inputusname(buffer) == 0) return;
            if (strlen(buffer) > 0) strcpy(a.username, buffer);
            if (strlen(buffer) < 4) {
                gotoxy(left+17, top+3); printf("Minimal 4 karakter!");
            }
            // CEK DUPLIKAT (a.id sebagai pengecualian)
            if (isDuplicate("username", buffer, a.id)) {
                gotoxy(left+17, top+3); printf("Nama pengguna sudah dipakai!"); continue;
            }
            break;
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
        gotoxy(left+17, top+6); showcurs();
        setRGBColor(251, 255, 199, 0);
        if (inputName(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(a.nama, buffer);
        gotoxy(left+17, top+6); printf("%-35s", a.nama);

        // 4. Telp
        do {
            gotoxy(left+17, top+8); showcurs();
            setRGBColor(251, 255, 199, 0);
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
            gotoxy(left+17, top+10); showcurs();
            setRGBColor(251, 255, 199, 0);
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

        // 7. Alamat
        gotoxy(left+17, top+12); showcurs();
        setRGBColor(251, 255, 199, 0);
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

        gotoxy(left, top-1); printf(" [ESC] Kembali    [ENTER] Lanjut");
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

        FILE *f = fopen(FILE_KARYAWAN, "rb");
        if (!f) return;

        Karyawan a;
        int found = 0;

        while (fread(&a, sizeof(Karyawan), 1, f)) {
            if (strcmp(a.id, realID) == 0) {
                target = a;
                found = 1;
                break;
            }
        }
        fclose(f);
        if(!found) { popupAlert(0,"Error: Data ID tidak sinkron."); continue; }

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
            int res = deleteKaryawan(realID);
            if (res == -1) {
                popupAlert(0, "SUPERADMIN tidak bisa dinonaktifkan!");
                return;
            }
            if(res == 1) {
                setRGBColor(202, 40, 44, 1);
                setRGBColor(251, 255, 199,0);
                gotoxy(30, 13); printf("Mengubah Data No %d (ID: %s)...", noUrut, realID);
                Sleep(500);
                popupAlert(1,"Status Berhasil Diubah!");
                return; // Keluar dari menu update
            }
            else
                popupAlert(0,"Gagal mengubah data!");
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
        gotoxy(left, top-1); printf(" [ESC] Kembali    [ENTER] Lanjut");
        gotoxy(30, 12); printf("Masukkan No. Urut (Dari Tabel): ");

        inputtext(inputNoStr);
        if (strlen(inputNoStr) == 0) return;

        int noUrut = atoi(inputNoStr);

        // Convert No -> ID
        if (finID(noUrut, realID) == 0) {
            gotoxy(30, 13); printf("Nomor %d tidak ditemukan!", noUrut);
            Sleep(1000); continue;
        }

        // --- 4. AMBIL DATA LENGKAP DARI file ---
        FILE *f = fopen(FILE_KARYAWAN, "rb");
        if (!f) return;

        Karyawan a;
        int found = 0;

        while (fread(&a, sizeof(Karyawan), 1, f)) {
            if (strcmp(a.id, realID) == 0) {
                found = 1;
                break;
            }
        }
        fclose(f);

        if (!found) {
            popupAlert(0,"Database Error: Data Tidak ada."); continue;
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

    int Data = dataKaryawan(left, yhead + 2, currentpage);
    return Data;
}
void supadm(char nama[50]){
    system("cls");
    applyColors();appname(43, 1);
    garisx(0,8);
    garisy(25,8); // Garis Sidebar

    char *menuSup[] = {
        " Kelola Karyawan", " Keluar"
    };

    while(1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        gotoxy(1,10); printf("Halo, %s", cutname(nama));
        gotoxy(1,20); printf(" [↕]      Pilih Menu");
        gotoxy(1,21); printf(" [ENTER]  Lanjut");

        dashboard(nama);

        int pilih = menuSelect(1, 12, menuSup, 2);

        if (pilih == 0) { // KELOLA DATA KARYAWAN
            kelolaKar(nama);
            currentpage = 1;
        }
        else if (pilih == 1) { // LOGOUT
            if (popupConfirm("Apakah anda yakin ingin keluar?", "Ya", "Tidak"))
                return;
        }
    }
}

void kelolaKar(char *nama)
{
    system("cls");
    applyColors();appname(43, 1);
    garisx(0,8);
    garisy(25,8); // Garis Sidebar

    gotoxy(1,10); printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕]      Pilih Menu");
    gotoxy(1,21); printf(" [ENTER]  Lanjut");

    int currentView = 1;

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

        if (currentView == 1) {
            totalData = lihatKar(); // Render tabel & dapatkan total data
            maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

            // Render Footer Paging
            int bot = 34;
            gotoxy(29, bot+1);
            setRGBColor(202, 40, 44, 1);
            setRGBColor(251, 255, 199,0);
            printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentpage, maxPage, totalData);

            gotoxy(1,10); printf("Halo, %s", cutname(nama));
            gotoxy(1,10); printf("DATA KARYAWAN");
        }

        // 5. Menu Select (Program Pauses Here)
        int pilih = menuSelect(1, 12, menuSup, 6);

        // 6. Logic Navigasi
        if (pilih == -1) { // Prev Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentpage > 1) currentpage--;
        }
        else if (pilih == -2) { // Next Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentpage < maxPage) currentpage++;
        }
        else if (pilih == 0) { // DATA KARYAWAN
            currentView = 1;
            currentpage = 1;
        }
        else if (pilih == 1) { // CARI KARYAWAN
            detailKar();
            // Setelah search selesai, kembalikan tampilan
            currentView = 1; // Atau 1 terserah mau balik kemana
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
        }
        else if (pilih == 2) { // TAMBAH
            createKar(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 1; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
        }
        else if (pilih == 3) { // UBAH
            updateKar();
            currentView = 1;
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
        }
        else if (pilih == 4) { // HAPUS
            hapusKar();
            currentView = 1;
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
        }
        else if (pilih == 5) { // KELUAR
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
            return;
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
    gotoxy(left, top-1); printf(" [ESC] Kembali   [ENTER] Lewati/Lanjut");

    int y = top + 2;
    // Tampilkan Data Lama (Sebagai referensi user)
    gotoxy(left+2, y);       printf("Nama Pengguna:");
    y+=2; gotoxy(left+2, y); printf("Kata Sandi   :");
    y+=2; gotoxy(left+2, y); printf("Nama Lengkap :");
    y+=2; gotoxy(left+2, y); printf("No. Telp     :");
    y+=2; gotoxy(left+2, y); printf("Email        :");
    y+=2; gotoxy(left+2, y); printf("Alamat       :");

    setRGBColor(235, 238, 215, 0);
    int yin = top + 2;
    gotoxy(left+16, yin);       printf(" %s", a->username);
    yin+=2; gotoxy(left+16, yin); printf(" "); for(int i=0;i<strlen(a->password);i++) printf("*");
    yin+=2; gotoxy(left+16, yin); printf(" %s", a->nama);
    yin+=2; gotoxy(left+16, yin); printf(" %s", a->telp);
    yin+=2; gotoxy(left+16, yin); printf(" %s", a->email);
    yin+=2; gotoxy(left+16, yin); printf(" %s", a->alamat);
}
int finID(int targetNo, char *destID){
    FILE *f = fopen(FILE_KARYAWAN, "rb");
    if (!f) return 0;

    Karyawan list[500], temp;
    int total = 0;

    //Load semua data
    while (fread(&list[total], sizeof(Karyawan), 1, f))
        total++;
    fclose(f);

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {

            // 1. Prioritas status (aktif dulu)
            if (list[j].status < list[j+1].status ||

                // 2. Kalau status sama, urutkan berdasarkan ID (baru dulu)
                (list[j].status == list[j+1].status &&
                 list[j].id < list[j+1].id)
            ) {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }

    if (targetNo < 1 || targetNo > total) return 0;
    strcpy(destID, list[targetNo-1].id);
    return 1;
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


void autoID(char *output, const char *format) {
    FILE *f = fopen(FILE_KARYAWAN, "rb");
    int max = 0;
    Karyawan k;

    if (f) {
        while (fread(&k, sizeof(Karyawan), 1, f)) {
            int num = atoi(k.id + 2); // KY###
            if (num > max) max = num;
        }
        fclose(f);
    }
    sprintf(output, format, max + 1);
}
void createKaryawan(Karyawan a)
{
    FILE *f = fopen(FILE_KARYAWAN, "ab");
    if (!f) return;

    autoID(a.id, "KY%03d");
    fwrite(&a, sizeof(Karyawan), 1, f);

    fclose(f);
}

int deleteKaryawan(char idTarget[])
{
    FILE *f = fopen(FILE_KARYAWAN, "rb+");
    if (!f) return 0;

    Karyawan k;
    while (fread(&k, sizeof(Karyawan), 1, f))
    {
        if (strcmp(k.id, idTarget) == 0) {
            if (strcmp(k.role, "superadmin") == 0) {
                fclose(f);
                return -1; // kode khusus: superadmin dilindungi
            }

            k.status = 0;
            fseek(f, -sizeof(Karyawan), SEEK_CUR);
            fwrite(&k, sizeof(Karyawan), 1, f);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
int updateKaryawan(const Karyawan *dataBaru)
{
    FILE *f = fopen(FILE_KARYAWAN, "rb+");
    if (!f) return 0;

    Karyawan k;
    while (fread(&k, sizeof(Karyawan), 1, f))
    {
        if (strcmp(k.id, dataBaru->id) == 0)
        {
            fseek(f, -sizeof(Karyawan), SEEK_CUR);
            fwrite(dataBaru, sizeof(Karyawan), 1, f);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int dataKaryawan(int left, int startY, int page)
{
    FILE *f = fopen(FILE_KARYAWAN,"rb");
    if (!f){
        gotoxy(left, startY+22);
        printf("File tidak ditemukan!");
        return 0;
    }

    Karyawan list[500], temp;
    int totalData = 0;

    // 1. LOAD SEMUA DATA (BINARY)
    while (fread(&list[totalData], sizeof(Karyawan), 1, f))
    {
        totalData++;
    }
    fclose(f);

    // 2. SORT AKTIF DI ATAS
    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {

            // 1. Prioritas status (aktif dulu)
            if (list[j].status < list[j+1].status ||

                // 2. Kalau status sama, urutkan berdasarkan ID (baru dulu)
                (list[j].status == list[j+1].status &&
                 list[j].id < list[j+1].id)
            ) {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }

    // 3. PAGINATION
    int limit = 20;
    int startIndex = (page - 1) * limit;
    int printed = 0;
    char stat[15];

    for (int i = startIndex; i < totalData && printed < limit; i++)
    {
        if (list[i].status == 1) {
            setRGBColor(251, 255, 199,0);
            strcpy(stat, "Aktif");
        } else {
            setRGBColor(210, 212, 200, 0);
            strcpy(stat, "Non-Aktif");
        }

        int y = startY + printed;
        int displayNo = i + 1;

        setRGBColor(202, 40, 44, 1);
        gotoxy(left+2, y);  printf("%-4d", displayNo);
        gotoxy(left+6, y);  printf("%-18.18s", cutname(list[i].username));
        gotoxy(left+20, y); printf("%-15.15s", cutname(list[i].nama));
        gotoxy(left+36, y); printf("%-13.13s", list[i].telp);
        gotoxy(left+50, y); printf("%-15.15s", list[i].email);
        gotoxy(left+66, y); printf("%-17.17s", list[i].alamat);
        gotoxy(left+84, y); printf("%-8.8s", list[i].role);
        gotoxy(left+93, y); printf("%s", stat);

        resetColor();
        printed++;
    }

    return totalData; // Kembalikan jumlah total data agar supadm tau max page nya
}

void injectDummyKaryawan() {
    char *names[] = {
        "Andra Wijaya","Ayunda Risu","Dimas Anggara","Fikri Haikal","Hana Pertiwi",
        "Ilham Saputra","Karin Novilda","Lutfi Halim","Maya Estianty","Nabil Makarim",
        "Raisa Andriana","Satria Baja","Tara Basro","Vania Larissa","Yoga Pratama",
        "Budi Santoso","Siti Aminah","Reza Rahadian","Dian Sastro","Joko Anwar",
        "Farel Pratama","Nadia Safira","Kevin Julio","Shinta Bachir","Rizky Febian",
        "Agnes Monica","Denny Cagur","Citra Kirana","Hafiz Suip","Tasya Kamila"
    };

    char *domains[] = {"gmail.com","yahoo.com","outlook.com"};

    char *roles[] = {
        "manajer","manajer",
        "staff","staff","staff","staff","staff","staff","staff","staff",
        "kasir","kasir","kasir","kasir","kasir","kasir","kasir","kasir","kasir","kasir",
        "staff","staff","kasir","kasir","staff","staff","kasir","kasir","staff","kasir"
    };

    for(int i = 0; i < 30; i++){
        Karyawan k = {0};
        char temp[50];

        strcpy(k.nama, names[i]);
        strcpy(temp, names[i]);

        char *first = strtok(temp, " ");
        strlwr(first);

        sprintf(k.username, "%s%d", first, rand()%900+100);
        sprintf(k.password, "pass%d", i+1);
        sprintf(k.telp, "08%09d", rand()%1000000000);
        sprintf(k.email, "%s@%s", k.username, domains[rand()%3]);
        sprintf(k.alamat, "Jl. Dummy No.%d", i+1);

        strcpy(k.role, roles[i]);
        k.status = 1;

        createKaryawan(k);
    }
}
void injectUserUtama()
{
    Karyawan list[] = {
        {"","SoeperAtmint","123456","superadmin",
         "0811111111","admin@sys.com","superadmin", "Jl. Mawar No. 1",1},

        {"","Munejer","123456","manajer",
         "0822222222","manager@sys.com","manajer", "Jl. Melati No. 2",1},

        {"","Stuff","123456","staff",
         "0833333333","staff@sys.com","staff", "Jl. Kenanga No. 3",1},

        {"","Kashier","123456SS","kasir",
         "0844444444","kasir@sys.com","kasir", "Jl. Anggrek No. 4",1}
    };

    int n = sizeof(list) / sizeof(list[0]);

    for (int i = 0; i < n; i++) {
        createKaryawan(list[i]);
    }
}
