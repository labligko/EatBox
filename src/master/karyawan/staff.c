#include <stdio.h>

#include "../../../include/data.h"
#include "../../../include/function.h"
#include "../../../include/master/karyawan/staff.h"
#include "../../../include/master/bahanBaku.h"
#include "../../../include/master/menu.h"
#include "../../../include/master/meja.h"
#include "../../../include/master/resep.h"

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
            if (popupConfirm("Apakah anda yakin ingin keluar?", "Ya", "Tidak"))
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
        gotoxy(1,20); printf(" [↕]      Pilih Menu");
        gotoxy(1,21); printf(" [ENTER]  Lanjut");

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
        gotoxy(1,20); printf(" [↕]      Pilih Menu");
        gotoxy(1,21); printf(" [ENTER]  Lanjut");

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
        gotoxy(1,20); printf(" [↕]      Pilih Menu");
        gotoxy(1,21); printf(" [ENTER]  Lanjut");

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
        m.status = (rand() % 10 < 9) ? 1 : 0; // 90% aktif

        daftarMeja[totalMeja++] = m;
    }

    saveMeja();
    printf("Dummy meja berhasil dibuat (binary)\n");
}

// ===== DUMMY MENU =====
void injectDummyMenu() {
    jumlahMenu = 30;

    strcpy(daftarMenu[0].id_menu, "MN001"); strcpy(daftarMenu[0].kategori, "Makanan"); strcpy(daftarMenu[0].nama_menu, "Nasi Goreng"); daftarMenu[0].harga = 20000; strcpy(daftarMenu[0].deskripsi, "Nasi goreng spesial dengan telur"); daftarMenu[0].status = 1;
    strcpy(daftarMenu[1].id_menu, "MN002"); strcpy(daftarMenu[1].kategori, "Makanan"); strcpy(daftarMenu[1].nama_menu, "Mie Ayam"); daftarMenu[1].harga = 18000; strcpy(daftarMenu[1].deskripsi, "Mie ayam pangsit istimewa"); daftarMenu[1].status = 1;
    strcpy(daftarMenu[2].id_menu, "MN003"); strcpy(daftarMenu[2].kategori, "Minuman"); strcpy(daftarMenu[2].nama_menu, "Es Teh Manis"); daftarMenu[2].harga = 5000; strcpy(daftarMenu[2].deskripsi, "Segelas es teh manis dingin"); daftarMenu[2].status = 1;
    strcpy(daftarMenu[3].id_menu, "MN004"); strcpy(daftarMenu[3].kategori, "Minuman"); strcpy(daftarMenu[3].nama_menu, "Jus Alpukat"); daftarMenu[3].harga = 15000; strcpy(daftarMenu[3].deskripsi, "Alpukat segar dicampur susu"); daftarMenu[3].status = 1;
    strcpy(daftarMenu[4].id_menu, "MN005"); strcpy(daftarMenu[4].kategori, "Makanan"); strcpy(daftarMenu[4].nama_menu, "Rendang"); daftarMenu[4].harga = 25000; strcpy(daftarMenu[4].deskripsi, "Daging rendang khas Minang"); daftarMenu[4].status = 1;
    strcpy(daftarMenu[5].id_menu, "MN006"); strcpy(daftarMenu[5].kategori, "Makanan"); strcpy(daftarMenu[5].nama_menu, "Sate Ayam"); daftarMenu[5].harga = 22000; strcpy(daftarMenu[5].deskripsi, "Sate ayam dengan bumbu kacang"); daftarMenu[5].status = 1;
    strcpy(daftarMenu[6].id_menu, "MN007"); strcpy(daftarMenu[6].kategori, "Makanan"); strcpy(daftarMenu[6].nama_menu, "Bakso"); daftarMenu[6].harga = 15000; strcpy(daftarMenu[6].deskripsi, "Bakso daging sapi dengan kuah panas"); daftarMenu[6].status = 1;
    strcpy(daftarMenu[7].id_menu, "MN008"); strcpy(daftarMenu[7].kategori, "Makanan"); strcpy(daftarMenu[7].nama_menu, "Capcay"); daftarMenu[7].harga = 18000; strcpy(daftarMenu[7].deskripsi, "Sayuran segar tumis ala Tionghoa"); daftarMenu[7].status = 1;
    strcpy(daftarMenu[8].id_menu, "MN009"); strcpy(daftarMenu[8].kategori, "Minuman"); strcpy(daftarMenu[8].nama_menu, "Es Jeruk"); daftarMenu[8].harga = 8000; strcpy(daftarMenu[8].deskripsi, "Segelas es jeruk segar"); daftarMenu[8].status = 1;
    strcpy(daftarMenu[9].id_menu, "MN010"); strcpy(daftarMenu[9].kategori, "Minuman"); strcpy(daftarMenu[9].nama_menu, "Kopi Tubruk"); daftarMenu[9].harga = 10000; strcpy(daftarMenu[9].deskripsi, "Kopi hitam tradisional"); daftarMenu[9].status = 1;
    strcpy(daftarMenu[10].id_menu, "MN011"); strcpy(daftarMenu[10].kategori, "Makanan"); strcpy(daftarMenu[10].nama_menu, "Ayam Goreng"); daftarMenu[10].harga = 20000; strcpy(daftarMenu[10].deskripsi, "Ayam goreng renyah"); daftarMenu[10].status = 1;
    strcpy(daftarMenu[11].id_menu, "MN012"); strcpy(daftarMenu[11].kategori, "Makanan"); strcpy(daftarMenu[11].nama_menu, "Nasi Uduk"); daftarMenu[11].harga = 17000; strcpy(daftarMenu[11].deskripsi, "Nasi uduk lengkap dengan telur dan ayam"); daftarMenu[11].status = 1;
    strcpy(daftarMenu[12].id_menu, "MN013"); strcpy(daftarMenu[12].kategori, "Minuman"); strcpy(daftarMenu[12].nama_menu, "Milkshake Coklat"); daftarMenu[12].harga = 15000; strcpy(daftarMenu[12].deskripsi, "Milkshake dingin rasa coklat"); daftarMenu[12].status = 1;
    strcpy(daftarMenu[13].id_menu, "MN014"); strcpy(daftarMenu[13].kategori, "Minuman"); strcpy(daftarMenu[13].nama_menu, "Smoothie Mangga"); daftarMenu[13].harga = 18000; strcpy(daftarMenu[13].deskripsi, "Mangga segar dicampur yogurt"); daftarMenu[13].status = 1;
    strcpy(daftarMenu[14].id_menu, "MN015"); strcpy(daftarMenu[14].kategori, "Makanan"); strcpy(daftarMenu[14].nama_menu, "Soto Ayam"); daftarMenu[14].harga = 20000; strcpy(daftarMenu[14].deskripsi, "Soto ayam dengan kuah bening sedap"); daftarMenu[14].status = 1;
    strcpy(daftarMenu[15].id_menu, "MN016"); strcpy(daftarMenu[15].kategori, "Makanan"); strcpy(daftarMenu[15].nama_menu, "Pecel Lele"); daftarMenu[15].harga = 18000; strcpy(daftarMenu[15].deskripsi, "Lele goreng dengan sambal pecel"); daftarMenu[15].status = 1;
    strcpy(daftarMenu[16].id_menu, "MN017"); strcpy(daftarMenu[16].kategori, "Makanan"); strcpy(daftarMenu[16].nama_menu, "Gado-Gado"); daftarMenu[16].harga = 17000; strcpy(daftarMenu[16].deskripsi, "Sayur rebus dengan saus kacang"); daftarMenu[16].status = 1;
    strcpy(daftarMenu[17].id_menu, "MN018"); strcpy(daftarMenu[17].kategori, "Minuman"); strcpy(daftarMenu[17].nama_menu, "Es Kopi Susu"); daftarMenu[17].harga = 12000; strcpy(daftarMenu[17].deskripsi, "Kopi susu dingin"); daftarMenu[17].status = 1;
    strcpy(daftarMenu[18].id_menu, "MN019"); strcpy(daftarMenu[18].kategori, "Minuman"); strcpy(daftarMenu[18].nama_menu, "Teh Tarik"); daftarMenu[18].harga = 10000; strcpy(daftarMenu[18].deskripsi, "Teh tarik hangat atau dingin"); daftarMenu[18].status = 1;
    strcpy(daftarMenu[19].id_menu, "MN020"); strcpy(daftarMenu[19].kategori, "Makanan"); strcpy(daftarMenu[19].nama_menu, "Martabak Manis"); daftarMenu[19].harga = 25000; strcpy(daftarMenu[19].deskripsi, "Martabak manis coklat keju"); daftarMenu[19].status = 1;
    strcpy(daftarMenu[20].id_menu, "MN021"); strcpy(daftarMenu[20].kategori, "Makanan"); strcpy(daftarMenu[20].nama_menu, "Pasta Carbonara"); daftarMenu[20].harga = 30000; strcpy(daftarMenu[20].deskripsi, "Pasta creamy dengan daging asap"); daftarMenu[20].status = 1;
    strcpy(daftarMenu[21].id_menu, "MN022"); strcpy(daftarMenu[21].kategori, "Makanan"); strcpy(daftarMenu[21].nama_menu, "Lasagna"); daftarMenu[21].harga = 35000; strcpy(daftarMenu[21].deskripsi, "Lasagna berlapis keju dan daging"); daftarMenu[21].status = 1;
    strcpy(daftarMenu[22].id_menu, "MN023"); strcpy(daftarMenu[22].kategori, "Minuman"); strcpy(daftarMenu[22].nama_menu, "Smoothie Strawberry"); daftarMenu[22].harga = 20000; strcpy(daftarMenu[22].deskripsi, "Strawberry segar dicampur yogurt"); daftarMenu[22].status = 1;
    strcpy(daftarMenu[23].id_menu, "MN024"); strcpy(daftarMenu[23].kategori, "Minuman"); strcpy(daftarMenu[23].nama_menu, "Lemonade"); daftarMenu[23].harga = 15000; strcpy(daftarMenu[23].deskripsi, "Minuman lemon segar dingin"); daftarMenu[23].status = 1;
    strcpy(daftarMenu[24].id_menu, "MN025"); strcpy(daftarMenu[24].kategori, "Makanan"); strcpy(daftarMenu[24].nama_menu, "Taco"); daftarMenu[24].harga = 25000; strcpy(daftarMenu[24].deskripsi, "Taco isi daging dan sayur"); daftarMenu[24].status = 1;
    strcpy(daftarMenu[25].id_menu, "MN026"); strcpy(daftarMenu[25].kategori, "Makanan"); strcpy(daftarMenu[25].nama_menu, "Burger"); daftarMenu[25].harga = 30000; strcpy(daftarMenu[25].deskripsi, "Burger daging sapi lengkap"); daftarMenu[25].status = 1;
    strcpy(daftarMenu[26].id_menu, "MN027"); strcpy(daftarMenu[26].kategori, "Minuman"); strcpy(daftarMenu[26].nama_menu, "Chocolate Latte"); daftarMenu[26].harga = 18000; strcpy(daftarMenu[26].deskripsi, "Kopi susu coklat panas"); daftarMenu[26].status = 1;
    strcpy(daftarMenu[27].id_menu, "MN028"); strcpy(daftarMenu[27].kategori, "Minuman"); strcpy(daftarMenu[27].nama_menu, "Green Tea Latte"); daftarMenu[27].harga = 20000; strcpy(daftarMenu[27].deskripsi, "Teh hijau susu hangat"); daftarMenu[27].status = 1;
    strcpy(daftarMenu[28].id_menu, "MN029"); strcpy(daftarMenu[28].kategori, "Makanan"); strcpy(daftarMenu[28].nama_menu, "Chicken Wings"); daftarMenu[28].harga = 28000; strcpy(daftarMenu[28].deskripsi, "Sayap ayam goreng pedas"); daftarMenu[28].status = 1;
    strcpy(daftarMenu[29].id_menu, "MN030"); strcpy(daftarMenu[29].kategori, "Makanan"); strcpy(daftarMenu[29].nama_menu, "Caesar Salad"); daftarMenu[29].harga = 22000; strcpy(daftarMenu[29].deskripsi, "Salad sayur dengan saus Caesar"); daftarMenu[29].status = 1;

    saveMenu();
}

// ===== DUMMY BAHAN =====
void injectDummyBahan() {
    totalBahan = 30;

    strcpy(daftarBahan[0].id_bahan, "BB001"); strcpy(daftarBahan[0].nama_bahan, "Nasi"); daftarBahan[0].stok = 1000; daftarBahan[0].minimal_stok = 50; strcpy(daftarBahan[0].satuan, "g"); daftarBahan[0].status = 1;
    strcpy(daftarBahan[1].id_bahan, "BB002"); strcpy(daftarBahan[1].nama_bahan, "Telur"); daftarBahan[1].stok = 200; daftarBahan[1].minimal_stok = 10; strcpy(daftarBahan[1].satuan, "pcs"); daftarBahan[1].status = 1;
    strcpy(daftarBahan[2].id_bahan, "BB003"); strcpy(daftarBahan[2].nama_bahan, "Ayam"); daftarBahan[2].stok = 500; daftarBahan[2].minimal_stok = 50; strcpy(daftarBahan[2].satuan, "g"); daftarBahan[2].status = 1;
    strcpy(daftarBahan[3].id_bahan, "BB004"); strcpy(daftarBahan[3].nama_bahan, "Daging Sapi"); daftarBahan[3].stok = 500; daftarBahan[3].minimal_stok = 50; strcpy(daftarBahan[3].satuan, "g"); daftarBahan[3].status = 1;
    strcpy(daftarBahan[4].id_bahan, "BB005"); strcpy(daftarBahan[4].nama_bahan, "Lele"); daftarBahan[4].stok = 300; daftarBahan[4].minimal_stok = 30; strcpy(daftarBahan[4].satuan, "g"); daftarBahan[4].status = 1;
    strcpy(daftarBahan[5].id_bahan, "BB006"); strcpy(daftarBahan[5].nama_bahan, "Mie"); daftarBahan[5].stok = 500; daftarBahan[5].minimal_stok = 50; strcpy(daftarBahan[5].satuan, "g"); daftarBahan[5].status = 1;
    strcpy(daftarBahan[6].id_bahan, "BB007"); strcpy(daftarBahan[6].nama_bahan, "Pangsit"); daftarBahan[6].stok = 300; daftarBahan[6].minimal_stok = 20; strcpy(daftarBahan[6].satuan, "g"); daftarBahan[6].status = 1;
    strcpy(daftarBahan[7].id_bahan, "BB008"); strcpy(daftarBahan[7].nama_bahan, "Sayur"); daftarBahan[7].stok = 500; daftarBahan[7].minimal_stok = 50; strcpy(daftarBahan[7].satuan, "g"); daftarBahan[7].status = 1;
    strcpy(daftarBahan[8].id_bahan, "BB009"); strcpy(daftarBahan[8].nama_bahan, "Saus Kacang"); daftarBahan[8].stok = 200; daftarBahan[8].minimal_stok = 20; strcpy(daftarBahan[8].satuan, "ml"); daftarBahan[8].status = 1;
    strcpy(daftarBahan[9].id_bahan, "BB010"); strcpy(daftarBahan[9].nama_bahan, "Teh"); daftarBahan[9].stok = 300; daftarBahan[9].minimal_stok = 20; strcpy(daftarBahan[9].satuan, "g"); daftarBahan[9].status = 1;
    strcpy(daftarBahan[10].id_bahan, "BB011"); strcpy(daftarBahan[10].nama_bahan, "Susu"); daftarBahan[10].stok = 500; daftarBahan[10].minimal_stok = 50; strcpy(daftarBahan[10].satuan, "ml"); daftarBahan[10].status = 1;
    strcpy(daftarBahan[11].id_bahan, "BB012"); strcpy(daftarBahan[11].nama_bahan, "Gula"); daftarBahan[11].stok = 500; daftarBahan[11].minimal_stok = 50; strcpy(daftarBahan[11].satuan, "g"); daftarBahan[11].status = 1;
    strcpy(daftarBahan[12].id_bahan, "BB013"); strcpy(daftarBahan[12].nama_bahan, "Coklat"); daftarBahan[12].stok = 300; daftarBahan[12].minimal_stok = 20; strcpy(daftarBahan[12].satuan, "g"); daftarBahan[12].status = 1;
    strcpy(daftarBahan[13].id_bahan, "BB014"); strcpy(daftarBahan[13].nama_bahan, "Keju"); daftarBahan[13].stok = 200; daftarBahan[13].minimal_stok = 20; strcpy(daftarBahan[13].satuan, "g"); daftarBahan[13].status = 1;
    strcpy(daftarBahan[14].id_bahan, "BB015"); strcpy(daftarBahan[14].nama_bahan, "Alpukat"); daftarBahan[14].stok = 300; daftarBahan[14].minimal_stok = 20; strcpy(daftarBahan[14].satuan, "g"); daftarBahan[14].status = 1;
    strcpy(daftarBahan[15].id_bahan, "BB016"); strcpy(daftarBahan[15].nama_bahan, "Jeruk"); daftarBahan[15].stok = 200; daftarBahan[15].minimal_stok = 20; strcpy(daftarBahan[15].satuan, "g"); daftarBahan[15].status = 1;
    strcpy(daftarBahan[16].id_bahan, "BB017"); strcpy(daftarBahan[16].nama_bahan, "Bumbu Rendang"); daftarBahan[16].stok = 200; daftarBahan[16].minimal_stok = 20; strcpy(daftarBahan[16].satuan, "g"); daftarBahan[16].status = 1;
    strcpy(daftarBahan[17].id_bahan, "BB018"); strcpy(daftarBahan[17].nama_bahan, "Santan"); daftarBahan[17].stok = 300; daftarBahan[17].minimal_stok = 30; strcpy(daftarBahan[17].satuan, "ml"); daftarBahan[17].status = 1;
    strcpy(daftarBahan[18].id_bahan, "BB019"); strcpy(daftarBahan[18].nama_bahan, "Yogurt"); daftarBahan[18].stok = 200; daftarBahan[18].minimal_stok = 20; strcpy(daftarBahan[18].satuan, "ml"); daftarBahan[18].status = 1;
    strcpy(daftarBahan[19].id_bahan, "BB020"); strcpy(daftarBahan[19].nama_bahan, "Minyak"); daftarBahan[19].stok = 500; daftarBahan[19].minimal_stok = 50; strcpy(daftarBahan[19].satuan, "ml"); daftarBahan[19].status = 1;
    strcpy(daftarBahan[20].id_bahan, "BB021"); strcpy(daftarBahan[20].nama_bahan, "Daging Kambing"); daftarBahan[20].stok = 300; daftarBahan[20].minimal_stok = 20; strcpy(daftarBahan[20].satuan, "g"); daftarBahan[20].status = 1;
    strcpy(daftarBahan[21].id_bahan, "BB022"); strcpy(daftarBahan[21].nama_bahan, "Kentang"); daftarBahan[21].stok = 400; daftarBahan[21].minimal_stok = 30; strcpy(daftarBahan[21].satuan, "g"); daftarBahan[21].status = 1;
    strcpy(daftarBahan[22].id_bahan, "BB023"); strcpy(daftarBahan[22].nama_bahan, "Tomat"); daftarBahan[22].stok = 300; daftarBahan[22].minimal_stok = 20; strcpy(daftarBahan[22].satuan, "g"); daftarBahan[22].status = 1;
    strcpy(daftarBahan[23].id_bahan, "BB024"); strcpy(daftarBahan[23].nama_bahan, "Keju Mozzarella"); daftarBahan[23].stok = 200; daftarBahan[23].minimal_stok = 20; strcpy(daftarBahan[23].satuan, "g"); daftarBahan[23].status = 1;
    strcpy(daftarBahan[24].id_bahan, "BB025"); strcpy(daftarBahan[24].nama_bahan, "Saus Tomat"); daftarBahan[24].stok = 200; daftarBahan[24].minimal_stok = 20; strcpy(daftarBahan[24].satuan, "ml"); daftarBahan[24].status = 1;
    strcpy(daftarBahan[25].id_bahan, "BB026"); strcpy(daftarBahan[25].nama_bahan, "Bawang Putih"); daftarBahan[25].stok = 100; daftarBahan[25].minimal_stok = 10; strcpy(daftarBahan[25].satuan, "g"); daftarBahan[25].status = 1;
    strcpy(daftarBahan[26].id_bahan, "BB027"); strcpy(daftarBahan[26].nama_bahan, "Bawang Merah"); daftarBahan[26].stok = 100; daftarBahan[26].minimal_stok = 10; strcpy(daftarBahan[26].satuan, "g"); daftarBahan[26].status = 1;
    strcpy(daftarBahan[27].id_bahan, "BB028"); strcpy(daftarBahan[27].nama_bahan, "Cabe"); daftarBahan[27].stok = 100; daftarBahan[27].minimal_stok = 10; strcpy(daftarBahan[27].satuan, "g"); daftarBahan[27].status = 1;
    strcpy(daftarBahan[28].id_bahan, "BB029"); strcpy(daftarBahan[28].nama_bahan, "Jamur"); daftarBahan[28].stok = 150; daftarBahan[28].minimal_stok = 10; strcpy(daftarBahan[28].satuan, "g"); daftarBahan[28].status = 1;
    strcpy(daftarBahan[29].id_bahan, "BB030"); strcpy(daftarBahan[29].nama_bahan, "Basil"); daftarBahan[29].stok = 50; daftarBahan[29].minimal_stok = 5; strcpy(daftarBahan[29].satuan, "g"); daftarBahan[29].status = 1;

    saveBahan();
}

// ===== DUMMY RESEP =====
void injectDummyResep() {
    totalResep = 85; // lebih dari 2 bahan per menu jika perlu

    // MN001 - Nasi Goreng
    strcpy(daftarResep[0].id_menu, "MN001"); strcpy(daftarResep[0].id_bahan, "BB001"); daftarResep[0].jumlah = 150;
    strcpy(daftarResep[1].id_menu, "MN001"); strcpy(daftarResep[1].id_bahan, "BB002"); daftarResep[1].jumlah = 2;
    strcpy(daftarResep[2].id_menu, "MN001"); strcpy(daftarResep[2].id_bahan, "BB020"); daftarResep[2].jumlah = 10; // Minyak

    // MN002 - Mie Ayam
    strcpy(daftarResep[3].id_menu, "MN002"); strcpy(daftarResep[3].id_bahan, "BB006"); daftarResep[3].jumlah = 100;
    strcpy(daftarResep[4].id_menu, "MN002"); strcpy(daftarResep[4].id_bahan, "BB003"); daftarResep[4].jumlah = 80;
    strcpy(daftarResep[5].id_menu, "MN002"); strcpy(daftarResep[5].id_bahan, "BB007"); daftarResep[5].jumlah = 50; // Pangsit

    // MN003 - Es Teh Manis
    strcpy(daftarResep[6].id_menu, "MN003"); strcpy(daftarResep[6].id_bahan, "BB010"); daftarResep[6].jumlah = 10;
    strcpy(daftarResep[7].id_menu, "MN003"); strcpy(daftarResep[7].id_bahan, "BB012"); daftarResep[7].jumlah = 10;
    strcpy(daftarResep[8].id_menu, "MN003"); strcpy(daftarResep[8].id_bahan, "BB011"); daftarResep[8].jumlah = 50;

    // MN004 - Jus Alpukat
    strcpy(daftarResep[9].id_menu, "MN004"); strcpy(daftarResep[9].id_bahan, "BB015"); daftarResep[9].jumlah = 150;
    strcpy(daftarResep[10].id_menu, "MN004"); strcpy(daftarResep[10].id_bahan, "BB011"); daftarResep[10].jumlah = 50;

    // MN005 - Rendang
    strcpy(daftarResep[11].id_menu, "MN005"); strcpy(daftarResep[11].id_bahan, "BB004"); daftarResep[11].jumlah = 200;
    strcpy(daftarResep[12].id_menu, "MN005"); strcpy(daftarResep[12].id_bahan, "BB017"); daftarResep[12].jumlah = 50;
    strcpy(daftarResep[13].id_menu, "MN005"); strcpy(daftarResep[13].id_bahan, "BB018"); daftarResep[13].jumlah = 50;

    // MN006 - Sate Ayam
    strcpy(daftarResep[14].id_menu, "MN006"); strcpy(daftarResep[14].id_bahan, "BB003"); daftarResep[14].jumlah = 100;
    strcpy(daftarResep[15].id_menu, "MN006"); strcpy(daftarResep[15].id_bahan, "BB009"); daftarResep[15].jumlah = 20;

    // MN007 - Bakso
    strcpy(daftarResep[16].id_menu, "MN007"); strcpy(daftarResep[16].id_bahan, "BB004"); daftarResep[16].jumlah = 120;
    strcpy(daftarResep[17].id_menu, "MN007"); strcpy(daftarResep[17].id_bahan, "BB007"); daftarResep[17].jumlah = 50;

    // MN008 - Capcay
    strcpy(daftarResep[18].id_menu, "MN008"); strcpy(daftarResep[18].id_bahan, "BB007"); daftarResep[18].jumlah = 50;
    strcpy(daftarResep[19].id_menu, "MN008"); strcpy(daftarResep[19].id_bahan, "BB008"); daftarResep[19].jumlah = 150;
    strcpy(daftarResep[20].id_menu, "MN008"); strcpy(daftarResep[20].id_bahan, "BB003"); daftarResep[20].jumlah = 50;

    // MN009 - Es Jeruk
    strcpy(daftarResep[21].id_menu, "MN009"); strcpy(daftarResep[21].id_bahan, "BB016"); daftarResep[21].jumlah = 100;
    strcpy(daftarResep[22].id_menu, "MN009"); strcpy(daftarResep[22].id_bahan, "BB012"); daftarResep[22].jumlah = 10;

    // MN010 - Kopi Tubruk
    strcpy(daftarResep[23].id_menu, "MN010"); strcpy(daftarResep[23].id_bahan, "BB012"); daftarResep[23].jumlah = 10;
    strcpy(daftarResep[24].id_menu, "MN010"); strcpy(daftarResep[24].id_bahan, "BB011"); daftarResep[24].jumlah = 50;

    // MN011 - Ayam Goreng
    strcpy(daftarResep[25].id_menu, "MN011"); strcpy(daftarResep[25].id_bahan, "BB003"); daftarResep[25].jumlah = 150;
    strcpy(daftarResep[26].id_menu, "MN011"); strcpy(daftarResep[26].id_bahan, "BB020"); daftarResep[26].jumlah = 15; // Minyak

    // MN012 - Nasi Uduk
    strcpy(daftarResep[27].id_menu, "MN012"); strcpy(daftarResep[27].id_bahan, "BB001"); daftarResep[27].jumlah = 150;
    strcpy(daftarResep[28].id_menu, "MN012"); strcpy(daftarResep[28].id_bahan, "BB003"); daftarResep[28].jumlah = 50;
    strcpy(daftarResep[29].id_menu, "MN012"); strcpy(daftarResep[29].id_bahan, "BB002"); daftarResep[29].jumlah = 1;

    // MN013 - Milkshake Coklat
    strcpy(daftarResep[30].id_menu, "MN013"); strcpy(daftarResep[30].id_bahan, "BB012"); daftarResep[30].jumlah = 20; // Gula
    strcpy(daftarResep[31].id_menu, "MN013"); strcpy(daftarResep[31].id_bahan, "BB011"); daftarResep[31].jumlah = 100; // Susu
    strcpy(daftarResep[32].id_menu, "MN013"); strcpy(daftarResep[32].id_bahan, "BB013"); daftarResep[32].jumlah = 30; // Coklat

    // MN014 - Smoothie Mangga
    strcpy(daftarResep[33].id_menu, "MN014"); strcpy(daftarResep[33].id_bahan, "BB018"); daftarResep[33].jumlah = 20; // Santan
    strcpy(daftarResep[34].id_menu, "MN014"); strcpy(daftarResep[34].id_bahan, "BB015"); daftarResep[34].jumlah = 150; // Alpukat (bisa diganti mangga)
    strcpy(daftarResep[35].id_menu, "MN014"); strcpy(daftarResep[35].id_bahan, "BB019"); daftarResep[35].jumlah = 50; // Yogurt

    // MN015 - Soto Ayam
    strcpy(daftarResep[36].id_menu, "MN015"); strcpy(daftarResep[36].id_bahan, "BB003"); daftarResep[36].jumlah = 100;
    strcpy(daftarResep[37].id_menu, "MN015"); strcpy(daftarResep[37].id_bahan, "BB001"); daftarResep[37].jumlah = 50; // Nasi sebagai pelengkap
    strcpy(daftarResep[38].id_menu, "MN015"); strcpy(daftarResep[38].id_bahan, "BB020"); daftarResep[38].jumlah = 10; // Minyak

    // MN016 - Pecel Lele
    strcpy(daftarResep[39].id_menu, "MN016"); strcpy(daftarResep[39].id_bahan, "BB005"); daftarResep[39].jumlah = 120; // Lele
    strcpy(daftarResep[40].id_menu, "MN016"); strcpy(daftarResep[40].id_bahan, "BB008"); daftarResep[40].jumlah = 50; // Sayur
    strcpy(daftarResep[41].id_menu, "MN016"); strcpy(daftarResep[41].id_bahan, "BB008"); daftarResep[41].jumlah = 30; // Bumbu pecel (bisa dari saus kacang)

    // MN017 - Gado-Gado
    strcpy(daftarResep[42].id_menu, "MN017"); strcpy(daftarResep[42].id_bahan, "BB008"); daftarResep[42].jumlah = 100; // Sayur
    strcpy(daftarResep[43].id_menu, "MN017"); strcpy(daftarResep[43].id_bahan, "BB008"); daftarResep[43].jumlah = 50; // Tambahan sayur
    strcpy(daftarResep[44].id_menu, "MN017"); strcpy(daftarResep[44].id_bahan, "BB009"); daftarResep[44].jumlah = 20; // Saus kacang

    // MN018 - Es Kopi Susu
    strcpy(daftarResep[45].id_menu, "MN018"); strcpy(daftarResep[45].id_bahan, "BB012"); daftarResep[45].jumlah = 10; // Gula
    strcpy(daftarResep[46].id_menu, "MN018"); strcpy(daftarResep[46].id_bahan, "BB011"); daftarResep[46].jumlah = 50; // Susu
    strcpy(daftarResep[47].id_menu, "MN018"); strcpy(daftarResep[47].id_bahan, "BB012"); daftarResep[47].jumlah = 5; // Kopi bubuk (pakai gula untuk logika)

    // MN019 - Teh Tarik
    strcpy(daftarResep[48].id_menu, "MN019"); strcpy(daftarResep[48].id_bahan, "BB010"); daftarResep[48].jumlah = 10; // Teh
    strcpy(daftarResep[49].id_menu, "MN019"); strcpy(daftarResep[49].id_bahan, "BB011"); daftarResep[49].jumlah = 50; // Susu
    strcpy(daftarResep[50].id_menu, "MN019"); strcpy(daftarResep[50].id_bahan, "BB012"); daftarResep[50].jumlah = 10; // Gula

    // MN020 - Martabak Manis
    strcpy(daftarResep[51].id_menu, "MN020"); strcpy(daftarResep[51].id_bahan, "BB001"); daftarResep[51].jumlah = 150; // Tepung/Nasi bisa diganti
    strcpy(daftarResep[52].id_menu, "MN020"); strcpy(daftarResep[52].id_bahan, "BB013"); daftarResep[52].jumlah = 50; // Coklat
    strcpy(daftarResep[53].id_menu, "MN020"); strcpy(daftarResep[53].id_bahan, "BB014"); daftarResep[53].jumlah = 30; // Keju
    strcpy(daftarResep[54].id_menu, "MN020"); strcpy(daftarResep[54].id_bahan, "BB011"); daftarResep[54].jumlah = 50; // Susu

    // MN021 – Pasta Carbonara
    strcpy(daftarResep[55].id_menu, "MN021"); strcpy(daftarResep[55].id_bahan, "BB006"); daftarResep[55].jumlah = 100; // Mie
    strcpy(daftarResep[56].id_menu, "MN021"); strcpy(daftarResep[56].id_bahan, "BB003"); daftarResep[56].jumlah = 50; // Ayam
    strcpy(daftarResep[57].id_menu, "MN021"); strcpy(daftarResep[57].id_bahan, "BB014"); daftarResep[57].jumlah = 20; // Keju

    // MN022 – Lasagna
    strcpy(daftarResep[58].id_menu, "MN022"); strcpy(daftarResep[58].id_bahan, "BB022"); daftarResep[58].jumlah = 100; // Kentang/alternatif
    strcpy(daftarResep[59].id_menu, "MN022"); strcpy(daftarResep[59].id_bahan, "BB023"); daftarResep[59].jumlah = 50; // Tomat
    strcpy(daftarResep[60].id_menu, "MN022"); strcpy(daftarResep[60].id_bahan, "BB024"); daftarResep[60].jumlah = 30; // Keju Mozzarella

    // MN023 – Smoothie Strawberry
    strcpy(daftarResep[61].id_menu, "MN023"); strcpy(daftarResep[61].id_bahan, "BB019"); daftarResep[61].jumlah = 50; // Yogurt
    strcpy(daftarResep[62].id_menu, "MN023"); strcpy(daftarResep[62].id_bahan, "BB012"); daftarResep[62].jumlah = 10; // Gula
    strcpy(daftarResep[63].id_menu, "MN023"); strcpy(daftarResep[63].id_bahan, "BB023"); daftarResep[63].jumlah = 20; // Tomat (as strawberry substitute)

    // MN024 – Lemonade
    strcpy(daftarResep[64].id_menu, "MN024"); strcpy(daftarResep[64].id_bahan, "BB016"); daftarResep[64].jumlah = 50; // Jeruk
    strcpy(daftarResep[65].id_menu, "MN024"); strcpy(daftarResep[65].id_bahan, "BB012"); daftarResep[65].jumlah = 10; // Gula

    // MN025 – Taco
    strcpy(daftarResep[66].id_menu, "MN025"); strcpy(daftarResep[66].id_bahan, "BB003"); daftarResep[66].jumlah = 50; // Ayam
    strcpy(daftarResep[67].id_menu, "MN025"); strcpy(daftarResep[67].id_bahan, "BB008"); daftarResep[67].jumlah = 30; // Sayur
    strcpy(daftarResep[68].id_menu, "MN025"); strcpy(daftarResep[68].id_bahan, "BB025"); daftarResep[68].jumlah = 10; // Saus Tomat

    // MN026 – Burger
    strcpy(daftarResep[69].id_menu, "MN026"); strcpy(daftarResep[69].id_bahan, "BB003"); daftarResep[69].jumlah = 80; // Daging
    strcpy(daftarResep[70].id_menu, "MN026"); strcpy(daftarResep[70].id_bahan, "BB024"); daftarResep[70].jumlah = 20; // Keju Mozzarella
    strcpy(daftarResep[71].id_menu, "MN026"); strcpy(daftarResep[71].id_bahan, "BB023"); daftarResep[71].jumlah = 15; // Tomat

    // MN027 – Chocolate Latte
    strcpy(daftarResep[72].id_menu, "MN027"); strcpy(daftarResep[72].id_bahan, "BB011"); daftarResep[72].jumlah = 50; // Susu
    strcpy(daftarResep[73].id_menu, "MN027"); strcpy(daftarResep[73].id_bahan, "BB013"); daftarResep[73].jumlah = 20; // Coklat
    strcpy(daftarResep[74].id_menu, "MN027"); strcpy(daftarResep[74].id_bahan, "BB012"); daftarResep[74].jumlah = 5;  // Gula

    // MN028 – Green Tea Latte
    strcpy(daftarResep[75].id_menu, "MN028"); strcpy(daftarResep[75].id_bahan, "BB011"); daftarResep[75].jumlah = 50; // Susu
    strcpy(daftarResep[76].id_menu, "MN028"); strcpy(daftarResep[76].id_bahan, "BB010"); daftarResep[76].jumlah = 10; // Teh
    strcpy(daftarResep[77].id_menu, "MN028"); strcpy(daftarResep[77].id_bahan, "BB012"); daftarResep[77].jumlah = 5;  // Gula

    // MN029 – Chicken Wings
    strcpy(daftarResep[78].id_menu, "MN029"); strcpy(daftarResep[78].id_bahan, "BB003"); daftarResep[78].jumlah = 100; // Ayam
    strcpy(daftarResep[79].id_menu, "MN029"); strcpy(daftarResep[79].id_bahan, "BB028"); daftarResep[79].jumlah = 10;  // Cabe
    strcpy(daftarResep[80].id_menu, "MN029"); strcpy(daftarResep[80].id_bahan, "BB020"); daftarResep[80].jumlah = 10;  // Minyak

    // MN030 – Caesar Salad
    strcpy(daftarResep[81].id_menu, "MN030"); strcpy(daftarResep[81].id_bahan, "BB008"); daftarResep[81].jumlah = 100; // Sayur
    strcpy(daftarResep[82].id_menu, "MN030"); strcpy(daftarResep[82].id_bahan, "BB024"); daftarResep[82].jumlah = 20;  // Keju Mozzarella
    strcpy(daftarResep[83].id_menu, "MN030"); strcpy(daftarResep[83].id_bahan, "BB025"); daftarResep[83].jumlah = 10;  // Saus Tomat

    saveResep();
}