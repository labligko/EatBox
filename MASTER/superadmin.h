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
void searchKar();
int lihatKar();
void dashboard(char *nama);
void supadm(char nama[50]);
int finID(int targetNo, char *destID);

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
        gotoxy(left+2, y); printf("Username : ");
        y+=2; gotoxy(left+2, y); printf("Password : ");
        y+=2; gotoxy(left+2, y); printf("Telp     : ");
        y+=2; gotoxy(left+2, y); printf("Email    : ");
        y+=2; gotoxy(left+2, y); printf("Role     : ");
        y+=2; gotoxy(left+2, y); printf("Alamat   : ");

        // --- 1. USERNAME (Wajib Diisi) ---
        do {
            clearinput(left+13, top+2, 40); gotoxy(left+13, top+2); showcurs();
            if (inputtext(a.username) == 0) return; // ESC

            if (strlen(a.username) == 0) {
                gotoxy(left+13, top+3); printf("Username wajib diisi!");
            }
        } while (strlen(a.username) == 0);
        clearinput(left+13, top+3, 30); // Hapus pesan error

        // --- 2. PASSWORD (Wajib Diisi) ---
        do {
            clearinput(left+13, top+4, 40); gotoxy(left+13, top+4); showcurs();
            if (inputpass(a.password, left+2, top+4, "Password ") == 0) return; // ESC

            if (strlen(a.password) == 0) {
                gotoxy(left+13, top+5); printf("Password wajib diisi!");
            }
        } while (strlen(a.password) == 0);
        clearinput(left+13, top+5, 30);

        // --- 3. TELP (Wajib Diisi + Validasi Angka) ---
        do {
            clearinput(left+13, top+6, 20); gotoxy(left+13, top+6); showcurs();
            if (inputTelp08(a.telp) == 0) return;

            int len = strlen(a.telp);

            if (len < 10) {
                gotoxy(left+13, top+7); printf("Minimal 10 digit!");
            }
            else {
                break;
            }
        } while (1);
        clearinput(left+13, top+7, 20);

        // --- 4. EMAIL (Wajib Diisi + Validasi Format) ---
        do {
            clearinput(left+13, top+8, 30); gotoxy(left+13, top+8); showcurs();
            if (inputtext(a.email) == 0) return;

            if (strlen(a.email) == 0) {
                gotoxy(left+13, top+9); printf("Email wajib diisi!");
            }
            else if (!cekEmail(a.email)) {
                gotoxy(left+13, top+9); printf("Format email salah! (gmail,yahoo,outlook)");
            }
            else {
                break; // Valid
            }
        } while (1);
        clearinput(left+13, top+9, 45);

        // --- 5. ROLE (Wajib Diisi + Validasi Role) ---
        do {
            clearinput(left+13, top+10, 20); gotoxy(left+13, top+10); showcurs();
            if (inputtext(a.role) == 0) return;

            if (strlen(a.role) == 0) {
                gotoxy(left+13, top+11); printf("Role wajib diisi!");
            }
            else if (!cekrole(a.role)) {
                gotoxy(left+13, top+11); printf("Hanya: manajer/staff/kasir");
            }
            else {
                break; // Valid
            }
        } while (1);
        clearinput(left+13, top+11, 30);

        // --- 6. ALAMAT (Wajib Diisi) ---
        do {
            clearinput(left+13, top+12, 40); gotoxy(left+13, top+12); showcurs();
            // Perbaikan bug copy-paste kemarin (a.alamat, bukan a.username)
            if (inputbebas(a.alamat) == 0) return;

            if (strlen(a.alamat) == 0) {
                gotoxy(left+13, top+13); printf("Alamat wajib diisi!");
            }
        } while (strlen(a.alamat) == 0);
        clearinput(left+13, top+13, 30);

        // --- PROSES SIMPAN ---
        a.status = 1;

        createKaryawan(a);
        popupAlert("Data berhasil ditambahkan!");
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
            gotoxy(30,12); printf("Nomor %d tidak ditemukan!", noUrut);
            Sleep(1000); continue;
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

        int left = 30, top = 11, right = 105, bot = 35;
        char buffer[100];
        clearArea(27, 9, clearW, clearH);
        frame(left, top, right, bot);

        gotoxy(1,10); printf("UBAH DATA KARYAWAN  ");
        clearinput(left, top-1, 40);
        gotoxy(left, top-1); printf(" [ESC] Batal   [ENTER] Lewati/Lanjut");

        int y = top + 2;

        // Tampilkan Data Lama (Sebagai referensi user)
        gotoxy(left+2, y); printf("Username : %s", a.username);
        y+=2; gotoxy(left+2, y); printf("Password : "); for(int i=0;i<strlen(a.password);i++) printf("*");
        y+=2; gotoxy(left+2, y); printf("Telp     : %s", a.telp);
        y+=2; gotoxy(left+2, y); printf("Email    : %s", a.email);
        y+=2; gotoxy(left+2, y); printf("Role     : %s", a.role);
        y+=2; gotoxy(left+2, y); printf("Alamat   : %s", a.alamat);
        y+=2; gotoxy(left+2, y); printf("Status   : %s", (a.status == 1 ? "Aktif" : "Non-Aktif"));

        // 1. USERNAME
        clearinput(left+13, top+2, 40); gotoxy(left+13, top+2); showcurs();
        if (inputtext(buffer) == 0) return; // ESC = Batal
        if (strlen(buffer) > 0) strcpy(a.username, buffer); // Kalau ada isi, update. Kalau kosong, skip.
        // Print ulang biar user liat hasil akhirnya (data lama atau baru)
        gotoxy(left+13, top+2); printf("%s", a.username);

        // 2. PASSWORD
        clearinput(left+13, top+4, 40); gotoxy(left+13, top+4); showcurs();
        // Gunakan inputpass tapi logicnya kalau kosong return 1 (sukses empty)
        if (inputpass(buffer, left+2, top+4, "Password ") == 0) return;
        if (strlen(buffer) > 0) strcpy(a.password, buffer);
        // Kita hide lagi passwordnya
        gotoxy(left+13, top+4); for(int i=0; i<strlen(a.password); i++) printf("*");

        // 3. TELP
        do {
            clearinput(left+13, top+6, 20); gotoxy(left+13, top+6); showcurs();
            if (inputTelp08(buffer) == 0) return;

            if (strlen(buffer) == 0) break; // Skip (pakai data lama)

            int len = strlen(a.telp);

            if (len < 10) {
                gotoxy(left+13, top+7); printf("Minimal 10 digit!");
            }
            else {
                break;
            }
        } while (1);
        clearinput(left+13, top+7, 20); // Hapus error
        gotoxy(left+13, top+6); printf("%s", a.telp); // Print hasil

        // 4. EMAIL
        do {
            clearinput(left+13, top+8, 30); gotoxy(left+13, top+8); showcurs();
            if (inputtext(buffer) == 0) return;

            if (strlen(buffer) == 0) break; // Skip

            if (cekEmail(buffer)) {
                strcpy(a.email, buffer);
                break;
            } else {
                gotoxy(left+13, top+9); printf("Email tidak valid! (gmail,yahoo,outlook)");
            }
        } while (1);
        clearinput(left+13, top+9, 45);
        gotoxy(left+13, top+8); printf("%s", a.email);

        // 5. ROLE
        do {
            clearinput(left+13, top+10, 20); gotoxy(left+13, top+10); showcurs();
            if (inputtext(buffer) == 0) return;

            if (strlen(buffer) == 0) break; // Skip

            if (cekrole(buffer)) {
                strcpy(a.role, buffer);
                break;
            } else {
                gotoxy(left+13, top+11); printf("Role: manajer/staff/kasir");
            }
        } while (1);
        clearinput(left+13, top+11, 20);
        gotoxy(left+13, top+10); printf("%s", a.role);

        // 6. ALAMAT
        clearinput(left+13, top+12, 40); gotoxy(left+13, top+12); showcurs();
        if (inputbebas(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(a.alamat, buffer);
        gotoxy(left+13, top+12); printf("%s", a.alamat);

        // 7. STATUS (Khusus ini pakai toggle kalau di-enter?)
        // Atau minta input 1/0. Kita bikin simpel: Ketik 1 atau 0. Kosong = Skip.
        gotoxy(left+13, top+15); printf("(1=Aktif, 0=Non)");
        clearinput(left+13, top+14, 20); gotoxy(left+13, top+14); showcurs();
        // Hint kecil

        if (inputtext(buffer) == 0) return;
        if (strlen(buffer) > 0) {
            if(strcmp(buffer, "1")==0) a.status = 1;
            else a.status = 0;
        }
        clearinput(left+13, top+15, 20); // Hapus hint
        gotoxy(left+13, top+14); printf("%s", (a.status == 1 ? "Aktif" : "Non-Aktif"));

        // --- KONFIRMASI SIMPAN ---
        if (popupConfirm("Simpan Perubahan Data Ini?"))
        {
            // User pilih ENTER (Ya)
            if(updateKaryawan(&a)) {
                popupAlert("Data Berhasil Diupdate!");
                return; // Keluar dari menu update
            } else {
                popupAlert("Gagal Perbarui Data!");
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
void hapusKar()
{
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
                sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
                       temp.id, temp.username, temp.password,
                       temp.telp, temp.email, temp.role,
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

        int y = 14;
        gotoxy(30, y++); printf("ID         : %s", target.id);
        gotoxy(30, y++); printf("Nama       : %s", target.username); // Pake nama asli saja biar jelas
        gotoxy(30, y++); printf("No. Telp   : %s", target.telp);
        gotoxy(30, y++); printf("Email      : %s", target.email);
        gotoxy(30, y++); printf("Alamat     : %s", target.alamat);
        gotoxy(30, y++); printf("Role       : %s", target.role);
        // Tampilkan status text
        gotoxy(30, y++); printf("Status     : %s", (target.status == 1) ? "Aktif" : "Non-Aktif");
        gotoxy(30,y++);printf("ketik sembarang untuk lanjut..."); getchar();

        // --- KONFIRMASI SIMPAN ---
        if (popupConfirm("Hapus Data Ini?"))
        {
            // User pilih ENTER (Ya)
            if(deleteKaryawan(realID)) {
                setRGBColor(202, 40, 44, 1);
                setRGBColor(251, 255, 199,0);
                gotoxy(30, 13); printf("Menghapus Data No %d (ID: %s)...", noUrut, realID);
                Sleep(500);
                popupAlert("Data berhasil dihapus!");
                return; // Keluar dari menu update
            } else {
                popupAlert("Gagal menghapus database!");
            }
        }
        else
        { clearArea(27, 9, clearW, clearH); }
    }
}
void searchKar()
{
    while(1) {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        char keyword[50];
        
        // --- 1. UI INPUT PENCARIAN ---
        clearinput(1,10,24);
        gotoxy(30, 10); printf("[ESC] Kembali");
        gotoxy(1,10); printf("PENCARIAN DATA");
        gotoxy(30,11); printf("Cari (Nama/ID/Role): ");
        
        showcurs();
        if (inputtext(keyword) == 0) return; // ESC = Kembali
        
        // Kalau kosong, ulang loop (atau bisa return)
        if (strlen(keyword) == 0) continue; 

        // --- 2. LOAD & FILTER DATA ---
        FILE *f = fopen("../FILE/karyawan.dat", "rb");
        if (!f) return;

        Karyawan list[500]; // Penampung Hasil Pencarian
        char str[512];
        int countFound = 0;

        while (fgets(str, sizeof(str), f)) {
            str[strcspn(str, "\n")] = 0;
            Karyawan temp;
            int p = sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
                   temp.id, temp.username, temp.password, temp.telp,
                   temp.email, temp.role, temp.alamat, &temp.status);
            if(p < 8) continue;

            // --- LOGIKA "UNIVERSAL SEARCH" ---
            // Cek apakah Keyword ada di Username ATAU ID ATAU Role ATAU Telp
            if (stringCek(temp.username, keyword) || 
                stringCek(temp.id, keyword) || 
                stringCek(temp.role, keyword) || 
                stringCek(temp.telp, keyword)) 
            {
                // Kalau cocok, masukkan ke list hasil
                list[countFound] = temp;
                countFound++;
            }
        }
        fclose(f);

        // --- 3. TAMPILKAN HASIL ---
        int searchPage = 1;
        int limit = 15;
        int left = 30, top = 15, right = 105, bot = 35;
        // Kita gambar tabel di bawah input
        frame(left, top, right, bot);
        
        // Header
        int yhead = top + 1;
        gotoxy(left+2, yhead);  printf("ID");
        gotoxy(left+10, yhead); printf("Username");
        gotoxy(left+27, yhead); printf("Role");
        gotoxy(left+40, yhead); printf("Status");
        for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

        gotoxy(left, top-1);
        printf(" Ditemukan %d hasil.     [ENTER] Cari Lagi  [<] Prev  [>] Next", countFound);
        CONSOLE_CURSOR_INFO info;
        info.bVisible = FALSE;
        info.dwSize = 20;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

        while(1)
        {
            // A. Hitung Max Page
            int maxPage = (countFound == 0) ? 1 : (countFound - 1) / limit + 1;

            // B. Bersihkan Area Isi Tabel (Supaya data page 1 gak numpuk sama page 2)
            // Area: y = top+2 sampai bot-1
            for(int i=0; i<limit; i++) {
                gotoxy(left+1, top+2+i);
                for(int j=0; j<right-left-1; j++) printf(" ");
            }

            // C. Tampilkan Data Sesuai Halaman
            if (countFound == 0) {
                gotoxy(left+2, top+3); printf("Tidak ada data yang cocok.");
            }
            else {
                int startIndex = (searchPage - 1) * limit;
                int printed = 0;

                for (int i = startIndex; i < countFound; i++) {
                    if (printed >= limit) break;

                    int y = top + 3 + printed;
                    gotoxy(left+2, y);  printf("%s", list[i].id);
                    gotoxy(left+10, y); printf("%-15.15s", list[i].username);
                    gotoxy(left+27, y); printf("%-10.10s", list[i].role);
                    gotoxy(left+40, y); printf("%s", (list[i].status==1?"Aktif":"Non"));

                    printed++;
                }
            }

            // D. Footer Halaman
            gotoxy(left, bot+1);
            printf("Halaman: %d / %d          ", searchPage, maxPage);

            // E. Input Key (Panah / Enter / Esc)
            unsigned char ch = _getch();

            if (ch == 224) { // Kode awal tombol panah
                ch = _getch();
                if (ch == 75) { // KIRI (Prev)
                    if (searchPage > 1) searchPage--;
                }
                else if (ch == 77) { // KANAN (Next)
                    if (searchPage < maxPage) searchPage++;
                }
            }
            else if (ch == 13) { // ENTER = Break loop dalam (Cari Lagi)
                break;
            }
            else if (ch == 27) { // ESC = Return keluar fungsi (Ke Menu Utama)
                return;
            }
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
    gotoxy(left+7, yhead); printf("Nama Karyawan");
    gotoxy(left+25, yhead); printf("No. telp");
    gotoxy(left+42, yhead); printf("Email");
    gotoxy(left+63 , yhead); printf("Alamat");
    gotoxy(left+85, yhead); printf("Posisi");
    gotoxy(left+95, yhead); printf("Status");

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
        " Data Karyawan", " Cari Karyawan", " Tambah Karyawan", " Ubah Karyawan", " Hapus Karyawan", " Keluar"
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
            searchKar();
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

int finID(int targetNo, char *destID)
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
    printf("Memulai injeksi 20 data dummy...\n");
    srand(time(NULL)); // Reset seed random

    // 1. DATA MASTER
    char *names[] = {"Andra", "Ayunda", "Dimas", "Fikri", "Hana", "Ilham", "Karin", "Lutfi", "Maya", "Nabil", "Raisa","Satria", "Tara", "Vania", "Yoga"};
    char *domain[] = {"gmail.com", "yahoo.com", "outlook.com"};
    int num_names = sizeof(names) / sizeof(names[0]);
    int num_domain = sizeof(domain) / sizeof(domain[0]);

    // 2. SETUP DISTRIBUSI ROLE (Total 20)
    // Kita buat array penampung role (Pool)
    char *rolePool[20];
    int r = 0;

    // Masukkan 2 Manajer
    for(int i=0; i<2; i++) rolePool[r++] = "manajer";
    // Masukkan 8 Staff
    for(int i=0; i<8; i++) rolePool[r++] = "staff";
    // Masukkan 10 Kasir
    for(int i=0; i<10; i++) rolePool[r++] = "kasir";

    // 3. KOCOK ROLE (SHUFFLE)
    // Biar ID awal (KY001) gak melulu Manajer.
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

        // Ambil Nama Acak + Angka biar unik
        int name_index = rand() % num_names;
        sprintf(k.username, "%s%d", names[name_index], rand() % 999);

        // Password
        sprintf(k.password, "pass%d", i + 100);

        // Telp
        sprintf(k.telp, "0812345%05d", rand() % 100000);

        // Email
        int domain_index = rand() % num_domain;
        sprintf(k.email, "%s%d@%s", names[name_index], rand() % 50, domain[domain_index]);

        // AMBIL ROLE DARI POOL (yang sudah dikocok)
        strcpy(k.role, rolePool[i]);

        // Alamat
        sprintf(k.alamat, "Jl. Dummy No. %d, Kota Test", i + 1);

        k.status = 1; // Aktif

        // --- SIMPAN (VOID VERSION) ---
        createKaryawan(k);
    }

    printf("Injeksi dummy data selesai! 20 data baru ditambahkan.\n");
    printf("Komposisi: 10 Kasir, 8 Staff, 2 Manajer (Posisi Acak).\n");
    printf("Tekan ENTER untuk melanjutkan...\n");
    getchar();
}

#endif //EATBOX_INTERFACE_H