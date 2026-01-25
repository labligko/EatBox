#include <stdio.h>

#include "../../../include/data.h"
#include "../../../include/function.h"
#include "../../../include/master/karyawan/staff.h"
#include "../../../include/master/bahanBaku.h"
#include "../../../include/master/menu.h"
#include "../../../include/master/meja.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

BahanBaku daftarBahan[100];
int totalBahan;

void staff(char nama[50])
{
    loadBahan();loadMenu();loadMeja();
    while(1) {
        system("cls");
        applyColors();

        appname(43, 1);
        garisx(0,8);
        garisy(25,8);

        int left = 28, right = 131, top = 11, bot = 34;
        frame(left, top, right, bot);

        gotoxy(left + 5, top + 2);
        printf("DASHBOARD STAFF");
        gotoxy(left + 5, top + 3);
        for(int i=0; i<95; i++) printf("─");

        int centerX = left + (right - left) / 2;
        gotoxy(centerX - 15, top + 6);
        printf("Selamat Datang, %s!", cutname(nama));
        gotoxy(centerX - 18, top + 7);
        printf("Silakan pilih menu di samping.");

        int box1_x = left + 5, box_y = top + 10;
        frame(box1_x, box_y, box1_x + 25, box_y + 6);
        gotoxy(box1_x + 2, box_y + 1); printf("DATA MENU");
        gotoxy(box1_x + 2, box_y + 3); printf("%d Item", hitungMenuAktif());

        int box2_x = box1_x + 35;
        frame(box2_x, box_y, box2_x + 25, box_y + 6);
        gotoxy(box2_x + 2, box_y + 1); printf("DATA STOK BAHAN BAKU");
        gotoxy(box2_x + 2, box_y + 3); printf("%d Item", hitungBahanAktif());

        int  box3_x = box2_x + 34;
        frame(box3_x, box_y, box3_x + 25, box_y + 6);
        gotoxy(box3_x + 2, box_y + 1); printf("DATA MEJA");
        gotoxy(box3_x + 2, box_y + 3); printf("%d Item", hitungMejaAktif());

        gotoxy(left + 2, bot - 2);printf(" Role: Staff");

        char *menuSup[] = {
            " Kelola Menu",
            " Kelola Bahan",
            " Kelola Meja",
            " Keluar"
        };

        gotoxy(1,10); printf("Halo, %s", cutname(nama));
        gotoxy(1,12); printf("Menu Utama");

        int pilih = menuSelect(1,13, menuSup, 4);

        if (pilih == 0) {
            currentpage = 1;
            showMenu(nama); // Masuk ke UI Tabel Menu
        }
        else if (pilih == 1) {
            showBahan(nama);
        }
        else if (pilih == 2)
        {
            showMeja(nama);
        }
        else if (pilih == 3) {
            return;
        }
    }
}

int renderTabelMenu(int left, int top, int right, int bot) {
    gotoxy(60, 10); printf("DATA MENU MAKANAN");
    frame(left, top, right, bot);

    int yhead = top + 1;
    gotoxy(left+2, yhead);  printf("No");
    gotoxy(left+10, yhead); printf("Nama Menu");
    gotoxy(left+27, yhead); printf("Kategori");
    gotoxy(left+44, yhead); printf("Harga");
    gotoxy(left+60, yhead); printf("Deskripsi");
    gotoxy(left+85, yhead); printf("Keterangan");

    for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

    // Panggil Data
    return dataMenu(left, yhead + 2, currentpage);
}
void showMenu(char nama[50])
{
    // Load data awal
    loadMenu();

    // Menu Sidebar
    char *opsiMenu[] = {
        " Refresh Data",
        " Tambah Menu",
        " Ubah Menu",
        " Hapus Menu",
        " Detail Menu",
        " Kembali"
    };

    // Setup Static UI
    system("cls");
    applyColors(); // Warna awal
    appname(43, 1);
    garisx(0,8);
    garisy(25,8);

    while(1) {
        // --- BERSIHKAN AREA KONTEN ---
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        // --- RENDER TABEL ---
        int left = 28, right = 131, top = 11, bot = 34;
        int totalData = renderTabelMenu(left, top, right, bot);

        // --- FOOTER PAGING ---
        int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;
        if (currentpage > maxPage) currentpage = maxPage;
        if (currentpage < 1) currentpage = 1;

        gotoxy(left+1, bot+1);

        printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentpage, maxPage, totalData);

        // --- SIDEBAR HEADER ---
        clearinput(1,10,24);clearinput(1,12,24);
        gotoxy(1,10); printf("KELOLA MENU     ");
        gotoxy(1,20); printf(" [↕] Pilih Menu");

        // --- Menu Select ---
        int pilih = menuSelect(1, 12, opsiMenu, 6);

        if (pilih == -1) { // Prev Page
            if (currentpage > 1) currentpage--;
        }
        else if (pilih == -2) { // Next Page
            if (currentpage < maxPage) currentpage++;
        }
        else if (pilih == 0) { // Refresh
            loadMenu();
        }
        else if (pilih == 1) { // Tambah
            tambahMenu();
            loadMenu(); // Reload biar tabel update
        }
        else if (pilih == 2) { // Ubah
            ubahMenu();
            loadMenu();
        }
        else if (pilih == 3) { // Hapus
            hapusMenu();
            loadMenu();
        }
        else if (pilih == 4) { // Cari
            detailMenu();
        }
        else if (pilih == 5) { // Kembali
            return;
        }
    }
}
void showBahan(char nama[50])
{
    loadBahan(); // Pastikan fungsi ini ada (untuk reload array dari file)

    char *opsiMenu[] = {
        " Refresh Data",
        " Tambah Bahan",
        " Ubah Bahan",
        " Hapus Bahan",
        " Kembali"
    };

    int currentpage = 1;

    // UI Setup Awal (Sama persis biar transisi mulus)
    system("cls");
    applyColors();
    appname(43, 1);
    garisx(0,8); garisy(25,8);

    while(1) {
        // Clear area konten (tengah)
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        // RENDER TABEL BAHAN
        // Asumsinya kamu punya fungsi 'renderTabelBahan' yang parameternya sama kayak Meja
        int left = 28, right = 131, top = 11, bot = 34;
        int totalData = renderTabelBahan(left, top, right, bot, currentpage);

        // PAGING LOGIC (Logic halaman otomatis)
        int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

        // Safety check biar halaman gak error
        if (currentpage > maxPage) currentpage = maxPage;
        if (currentpage < 1) currentpage = 1;

        // Footer Halaman
        gotoxy(left+1, bot+1);
        printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentpage, maxPage, totalData);

        // SIDEBAR
        clearinput(1,10,24);
        gotoxy(1,10); printf("KELOLA BAHAN    "); // Judul disesuaikan
        gotoxy(1,20); printf(" [↕] Pilih Menu");

        // MENU SELECT
        int pilih = menuSelect(1, 12, opsiMenu, 5);

        // LOGIKA NAVIGASI
        if (pilih == -1) { // Tombol Kiri (Prev Page)
            if (currentpage > 1) currentpage--;
        }
        else if (pilih == -2) { // Tombol Kanan (Next Page)
            if (currentpage < maxPage) currentpage++;
        }
        else if (pilih == 0) { // Refresh
            loadBahan();
        }
        else if (pilih == 1) { // Tambah
            tambahBahan();
            loadBahan(); // Reload biar data baru muncul
        }
        else if (pilih == 2) { // Ubah
            ubahBahan();
            loadBahan();
        }
        else if (pilih == 3) { // Hapus
            hapusBahan();
            loadBahan();
        }
        else if (pilih == 4) { // Kembali ke menu utama
            return;
        }
    }
}
void showMeja(char nama[50])
{
    loadMeja();
    char *opsiMenu[] = {
        " Refresh Data",
        " Tambah Meja",
        " Ubah Meja",
        " Hapus Meja",
        " Kembali"
    };

    int currentpage = 1;

    // UI Setup Awal
    system("cls");
    applyColors();
    appname(43, 1);
    garisx(0,8); garisy(25,8);

    while(1) {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        // RENDER TABEL (Logicnya udah di read_meja.h)
        int left = 28, right = 131, top = 11, bot = 34;
        int totalData = renderTabelMeja(left, top, right, bot, currentpage);

        // PAGING
        int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;
        if (currentpage > maxPage) currentpage = maxPage;
        if (currentpage < 1) currentpage = 1;

        gotoxy(left+1, bot+1);
        printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentpage, maxPage, totalData);

        // SIDEBAR
        clearinput(1,10,24);
        gotoxy(1,10); printf("KELOLA MEJA     ");
        gotoxy(1,20); printf(" [↕] Pilih Menu");

        // MENU SELECT
        int pilih = menuSelect(1, 12, opsiMenu, 5);

        if (pilih == -1) { if (currentpage > 1) currentpage--; }
        else if (pilih == -2) { if (currentpage < maxPage) currentpage++; }
        else if (pilih == 0) { loadMeja(); }
        else if (pilih == 1) { tambahMeja(); loadMeja(); }
        else if (pilih == 2) { ubahMeja(); loadMeja(); }
        else if (pilih == 3) { hapusMeja(); loadMeja(); }
        else if (pilih == 4) { return; }
    }
}

void injectDummyMeja() {
    srand(time(NULL));

    totalMeja = 0; // RESET BIAR GAK DOBEL, INI PENTING

    for (int i = 0; i < 20; i++)
    {
        Meja m;

        sprintf(m.id_meja, "MJ%03d", i + 1);
        m.nomor_meja = i + 1;
        m.kapasitas = (rand() % 4 + 1) * 2; // 2,4,6,8
        m.keterangan = (rand() % 2) + 1;    // 1=Kosong, 2=Terisi
        m.status = (rand() % 10 < 8) ? 1 : 0; // 80% aktif

        daftarMeja[totalMeja++] = m;
    }

    saveMeja();
    printf("Dummy meja berhasil dibuat (binary)\n");
}