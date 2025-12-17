#ifndef EATBOX_STAFF_H
#define EATBOX_STAFF_H

#include "../CRUD/read.h"
#include "../CRUD/delete.h"
#include "../CRUD/update.h"
#include "../CRUD/create.h"
#include "menu.h"
#include "bahanbaku.h"
#include "meja.h"

void staff(char nama[50]);
void showBahan(char nama[50]);
void showMeja(char nama[50]);

int renderTabelMenu(int left, int top, int right, int bot) {
    gotoxy(60, 10); printf("DATA MENU MAKANAN");
    frame(left, top, right, bot);

    int yhead = top + 1;
    gotoxy(left+2, yhead);  printf("ID");
    gotoxy(left+10, yhead); printf("Nama Menu");
    gotoxy(left+27, yhead); printf("Kategori");
    gotoxy(left+44, yhead); printf("Harga");
    gotoxy(left+60, yhead); printf("Deskripsi");
    gotoxy(left+85, yhead); printf("Status");

    for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

    // Panggil Data
    return dataMenu(left, yhead + 2, currentPage);
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
        " Cari Menu",
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
        if (currentPage > maxPage) currentPage = maxPage;
        if (currentPage < 1) currentPage = 1;

        gotoxy(left+1, bot+1);

        printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentPage, maxPage, totalData);

        // --- SIDEBAR HEADER ---
        clearinput(1,10,24);clearinput(1,12,24);
        gotoxy(1,10); printf("KELOLA MENU     ");
        gotoxy(1,20); printf(" [↕] Pilih Menu");

        // --- Menu Select ---
        int pilih = menuSelect(1, 12, opsiMenu, 6);

        if (pilih == -1) { // Prev Page
            if (currentPage > 1) currentPage--;
        }
        else if (pilih == -2) { // Next Page
            if (currentPage < maxPage) currentPage++;
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
            cariMenu();
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

    int currentPage = 1;

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
        int totalData = renderTabelBahan(left, top, right, bot, currentPage);

        // PAGING LOGIC (Logic halaman otomatis)
        int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

        // Safety check biar halaman gak error
        if (currentPage > maxPage) currentPage = maxPage;
        if (currentPage < 1) currentPage = 1;

        // Footer Halaman
        gotoxy(left+1, bot+1);
        printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentPage, maxPage, totalData);

        // SIDEBAR
        clearinput(1,10,24);
        gotoxy(1,10); printf("KELOLA BAHAN    "); // Judul disesuaikan
        gotoxy(1,20); printf(" [↕] Pilih Menu");

        // MENU SELECT
        int pilih = menuSelect(1, 12, opsiMenu, 5);

        // LOGIKA NAVIGASI
        if (pilih == -1) { // Tombol Kiri (Prev Page)
            if (currentPage > 1) currentPage--;
        }
        else if (pilih == -2) { // Tombol Kanan (Next Page)
            if (currentPage < maxPage) currentPage++;
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

    int currentPage = 1;

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
        int totalData = renderTabelMeja(left, top, right, bot, currentPage);

        // PAGING
        int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;
        if (currentPage > maxPage) currentPage = maxPage;
        if (currentPage < 1) currentPage = 1;

        gotoxy(left+1, bot+1);
        printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentPage, maxPage, totalData);

        // SIDEBAR
        clearinput(1,10,24);
        gotoxy(1,10); printf("KELOLA MEJA     ");
        gotoxy(1,20); printf(" [↕] Pilih Menu");

        // MENU SELECT
        int pilih = menuSelect(1, 12, opsiMenu, 5);

        if (pilih == -1) { if (currentPage > 1) currentPage--; }
        else if (pilih == -2) { if (currentPage < maxPage) currentPage++; }
        else if (pilih == 0) { loadMeja(); }
        else if (pilih == 1) { tambahMeja(); loadMeja(); }
        else if (pilih == 2) { ubahMeja(); loadMeja(); }
        else if (pilih == 3) { hapusMeja(); loadMeja(); }
        else if (pilih == 4) { return; }
    }
}

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
        gotoxy(box1_x + 2, box_y + 3); printf("%d Item", jumlahMenu);

        int box2_x = box1_x + 35;
        frame(box2_x, box_y, box2_x + 25, box_y + 6);
        gotoxy(box2_x + 2, box_y + 1); printf("DATA STOK BAHAN BAKU");
        gotoxy(box2_x + 2, box_y + 3); printf("%d Item", totalBahan);

        int  box3_x = box2_x + 34;
        frame(box3_x, box_y, box3_x + 25, box_y + 6);
        gotoxy(box3_x + 2, box_y + 1); printf("DATA MEJA");
        gotoxy(box3_x + 2, box_y + 3); printf("%d Item", totalMeja);

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
            currentPage = 1;
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

void generateDummyData() {
    // --- 1. RESET DATA (Supaya bersih dari 0) ---
    jumlahMenu = 0;
    totalMeja = 0;
    totalBahan = 0;

    // --- 2. DATA DUMMY MEJA (20 Meja) ---
    // Logika: Meja 1-10 (2 Orang), Meja 11-16 (4 Orang), Meja 17-20 (6 Orang)
    for (int i = 0; i < 20; i++) {
        sprintf(daftarMeja[i].id_meja, "MJ%03d", i + 1);
        daftarMeja[i].nomor_meja = i + 1;

        if (i < 10) daftarMeja[i].kapasitas = 2;
        else if (i < 16) daftarMeja[i].kapasitas = 4;
        else daftarMeja[i].kapasitas = 6;

        daftarMeja[i].status = 1; // Kosong
        totalMeja++;
    }
    saveMeja(); // Simpan ke file

    // --- 3. DATA DUMMY BAHAN BAKU (20 Bahan) ---
    // Bahan ini disiapkan untuk mendukung menu di bawah
    char *namaBahan[] = {
        "Beras Premium", "Telur Ayam", "Daging Ayam Fillet", "Daging Sapi Giling", "Bawang Merah",
        "Bawang Putih", "Cabai Rawit", "Minyak Goreng", "Garam Halus", "Gula Pasir",
        "Teh Celup", "Kopi Bubuk Robusta", "Susu UHT Full Cream", "Tepung Terigu", "Kentang Beku",
        "Roti Burger", "Keju Slice", "Saus Tomat", "Kecap Manis", "Air Galon"
    };
    char *satuanBahan[] = {
        "Kg", "Butir", "Kg", "Kg", "Kg",
        "Kg", "Kg", "Liter", "Bungkus", "Kg",
        "Kotak", "Kg", "Liter", "Kg", "Kg",
        "Pcs", "Lembar", "Botol", "Botol", "Galon"
    };
    int stokAwal[] = {
        50, 100, 20, 10, 5,
        5, 3, 20, 10, 25,
        50, 10, 24, 15, 30,
        40, 50, 20, 20, 10
    };

    for (int i = 0; i < 20; i++) {
        sprintf(daftarBahan[i].id_bahan, "BB%03d", i + 1);
        strcpy(daftarBahan[i].nama_bahan, namaBahan[i]);
        daftarBahan[i].stok = stokAwal[i];
        strcpy(daftarBahan[i].satuan, satuanBahan[i]);
        daftarBahan[i].minimal_stok = 5; // Default minimal stok
        totalBahan++;
    }
    saveBahan();

    // --- 4. DATA DUMMY MENU (20 Menu) ---
    // Menu Makanan, Minuman, Snack
    char *katMenu[] = {
        "Makanan Utama", "Makanan Utama", "Makanan Utama", "Makanan Utama", "Makanan Utama",
        "Makanan Utama", "Makanan Utama", "Makanan Utama", "Makanan Utama", "Western Food",
        "Western Food", "Snack", "Snack", "Snack", "Minuman",
        "Minuman", "Minuman", "Minuman", "Minuman", "Minuman"
    };
    char *nmMenu[] = {
        "Nasi Goreng Spesial", "Mie Goreng Jawa", "Ayam Bakar Madu", "Sate Ayam Lontong", "Soto Ayam Lamongan",
        "Nasi Uduk Komplit", "Gado-Gado Betawi", "Rendang Sapi", "Nasi Putih", "Burger Sapi Keju",
        "Spaghetti Bolognese", "Kentang Goreng", "Roti Bakar Coklat", "Pisang Keju", "Es Teh Manis",
        "Es Jeruk Peras", "Kopi Hitam Panas", "Es Kopi Susu", "Jus Alpukat", "Air Mineral"
    };
    double hrgMenu[] = {
        25000, 22000, 28000, 30000, 20000,
        18000, 18000, 35000, 5000, 35000,
        30000, 15000, 12000, 12000, 5000,
        8000, 10000, 18000, 15000, 4000
    };
    char *deskMenu[] = {
        "Nasi goreng dengan telur dan ayam suwir", "Mie goreng bumbu desa pedas manis", "Ayam bakar bumbu madu + lalapan", "Sate ayam 10 tusuk dengan bumbu kacang", "Soto ayam kuah kuning segar",
        "Nasi uduk dengan bihun dan tempe orek", "Sayuran rebus dengan bumbu kacang", "Daging sapi masak bumbu rempah padang", "Nasi putih pulen", "Burger daging sapi asli dengan keju",
        "Pasta spaghetti saus daging tomat", "Kentang goreng renyah asin gurih", "Roti tawar bakar isi coklat lumer", "Pisang bakar tabur keju susu", "Teh manis dingin segar",
        "Perasan jeruk murni dingin", "Kopi hitam robusta asli", "Kopi susu gula aren kekinian", "Jus alpukat kental dengan susu coklat", "Air mineral botol 600ml"
    };

    for (int i = 0; i < 20; i++) {
        sprintf(daftarMenu[i].id_menu, "MN%03d", i + 1);
        strcpy(daftarMenu[i].kategori, katMenu[i]);
        strcpy(daftarMenu[i].nama_menu, nmMenu[i]);
        daftarMenu[i].harga = hrgMenu[i];
        strcpy(daftarMenu[i].deskripsi, deskMenu[i]);
        daftarMenu[i].status = 1; // Tersedia
        jumlahMenu++;
    }
    saveMenu();

    // Notifikasi Selesai
    popupAlert("Dummy Data Berhasil Dibuat!");
}
void injectbahan()
{
    totalBahan = 0;

    // --- 3. DATA DUMMY BAHAN BAKU (20 Bahan) ---
    // Bahan ini disiapkan untuk mendukung menu di bawah
    char *namaBahan[] = {
        "Beras Premium", "Telur Ayam", "Daging Ayam Fillet", "Daging Sapi Giling", "Bawang Merah",
        "Bawang Putih", "Cabai Rawit", "Minyak Goreng", "Garam Halus", "Gula Pasir",
        "Teh Celup", "Kopi Bubuk Robusta", "Susu UHT Full Cream", "Tepung Terigu", "Kentang Beku",
        "Roti Burger", "Keju Slice", "Saus Tomat", "Kecap Manis", "Air Galon"
    };
    char *satuanBahan[] = {
        "Kg", "Butir", "Kg", "Kg", "Kg",
        "Kg", "Kg", "Liter", "Bungkus", "Kg",
        "Kotak", "Kg", "Liter", "Kg", "Kg",
        "Pcs", "Lembar", "Botol", "Botol", "Galon"
    };
    int stokAwal[] = {
        50, 100, 20, 10, 5,
        5, 3, 20, 10, 25,
        50, 10, 24, 15, 30,
        40, 50, 20, 20, 10
    };

    for (int i = 0; i < 20; i++) {
        sprintf(daftarBahan[i].id_bahan, "BB%03d", i + 1);
        strcpy(daftarBahan[i].nama_bahan, namaBahan[i]);
        daftarBahan[i].stok = stokAwal[i];
        strcpy(daftarBahan[i].satuan, satuanBahan[i]);
        daftarBahan[i].minimal_stok = 5; // Default minimal stok
        totalBahan++;
    }
    saveBahan();
}
#endif //EATBOX_STAFF_H