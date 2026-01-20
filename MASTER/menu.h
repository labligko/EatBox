#ifndef EATBOX_MENU_H
#define EATBOX_MENU_H

#define MAX_MENU 100
#define MAX_MENU_BAHAN 300
#define FILENAME "../FILE/menu.dat"
#define ITEMS_PER_PAGE 10
#include "bahanBaku.h"

extern Menu daftarMenu[MAX_MENU];
extern int jumlahMenu;
//relasi bahan baku
extern MenuBahan menuBahan[MAX_MENU_BAHAN];
extern int totalMenuBahan;

// DECLARATION
void tampilMenuUtama();
int cariMenuByID(char *id);
void tampilkanTabel(int page);
// void cariMenu();
void detailMenu();
void tambahMenu();
void pilihBahanMenu(Menu *m);
void lihatMenu();
void ubahMenu();
void hapusMenu();
void saveMenu();


void saveMenu() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("\n[ERROR] Gagal menyimpan data!\n");
        return;
    }

    for (int i = 0; i < jumlahMenu; i++) {
        fprintf(file, "%s|%s|%s|%.2lf|%s|%d\n",
        daftarMenu[i].id_menu,
        daftarMenu[i].kategori,
        daftarMenu[i].nama_menu,
        daftarMenu[i].harga,
        daftarMenu[i].deskripsi,
        daftarMenu[i].status);
    }

    fclose(file);
}
void generateID(char *id) {
    int maxNum = 0;
    for (int i = 0; i < jumlahMenu; i++) {
        int num;
        if (sscanf(daftarMenu[i].id_menu, "MN%d", &num) == 1) {
            if (num > maxNum) maxNum = num;
        }
    }
    sprintf(id, "MN%03d", maxNum + 1);
}
int cariMenuByID(char *id) {
    for (int i = 0; i < jumlahMenu; i++) {
        if (strcmp(daftarMenu[i].id_menu, id) == 0) {
            return i;
        }
    }
    return -1;
}

void tambahMenu() {
    Menu m;
    char buffer[50]; // Buffer sementara untuk validasi angka
    int pointer = 0;
    int maxField = 5;
    int left = 30, top = 11, right = 105, bot = 35;

    strcpy(m.kategori, "");
    strcpy(m.nama_menu, "");
    m.harga = 0;
    strcpy(m.deskripsi, "");
    // m.status = 0;   // <-- PERBAIKAN (bukan strcpy)
    m.status = 1; // biar default nya tersedia
    generateID(m.id_menu);

    while (1) {
        //ini pengganti cls biar g keapus semua
        int clearW = consoleW() - 27; int clearH = consoleH() - 9; //deklarasi kordinat yang jadi lokasi isi nya
        clearArea(27, 9, clearW, clearH); //hapus isi sebelum nya
        frame(left, top, right, bot); // buat garis tabel

        clearinput(1,10,24); gotoxy(1, 10); printf("TAMBAH MENU BARU");
        gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Lanjut");

        //header
        gotoxy(left + 25, top + 2);
        printf("\033[41m\033[93m EATBOX - INPUT MENU BARU \033[0m");

        //form
        int y = top + 4;
        int inputX = left + 18; //buat posisi input

        setRGBColor(202, 40, 44, 1);
        setRGBColor(251, 255, 199,0);
        // printf("\033[41m"); // background merah   JANGAN DIRUSAK BASE COLOR KITA
        gotoxy(left + 3, y); printf("ID Menu      : %s", m.id_menu);
        y += 2; gotoxy(left + 3, y); printf("Kategori     : ");
        y += 2; gotoxy(left + 3, y); printf("Nama Menu    : ");
        y += 2; gotoxy(left + 3, y); printf("Harga        : ");
        y += 2; gotoxy(left + 3, y); printf("Deskripsi    : ");
        y += 2; gotoxy(left + 3, y); printf("Status       : Tersedia (Default)");
        // printf("\033[0m"); // reset warna      JANGAN DIRUSAK BASE COLOR KITA

        // Input Kategori
        do {
            clearinput(inputX, top + 6, 40); gotoxy(inputX, top + 6); showcurs();
            // inputtext harus return 0 jika ditekan ESC
            if (inputtext(m.kategori) == 0) return;
            if (strlen(m.kategori) > 0) break; // Validasi tidak boleh kosong
        } while (1);

        // Input Nama Menu
        do {
            clearinput(inputX, top + 8, 40); gotoxy(inputX, top + 8); showcurs();
            if (inputtext(m.nama_menu) == 0) return;
            if (strlen(m.nama_menu) > 0) break;
        } while (1);

        // Input Harga
        do {
            clearinput(inputX, top + 10, 20); gotoxy(inputX, top + 10); showcurs();
            if (inputtext(buffer) == 0) return;
            // Cek apakah angka valid
            if (onlyNum(buffer) && strlen(buffer) > 0) {
                m.harga = atof(buffer); // Convert string ke double
                break;
            }
            gotoxy(inputX, top+11); printf("Masukan angka!");
        } while (1);
        clearinput(inputX, top+11, 25);

        // Input Deskripsi
        do {
            clearinput(inputX, top + 12, 50); gotoxy(inputX, top + 12); showcurs();
            if (inputtext(m.deskripsi) == 0) return;
            if (strlen(m.deskripsi) > 0) break;
        } while (1);

        // --- 3. KONFIRMASI SIMPAN ---
        if (popupConfirm("Simpan Menu Ini?", "Ya", "Batal")) {
            daftarMenu[jumlahMenu++] = m;
            saveMenu();
            popupAlert(1,"Menu Berhasil Ditambahkan!");
            return; // Keluar setelah simpan
        }
    }
}
void pilihBahanMenu(Menu *m) {
    int pilihan;
    char buffer[20];
    int left = 30, top = 11, right = 105, bot = 35;

    while (1) {
        clearArea(27, 9, consoleW() - 27, consoleH() - 9);
        frame(left, top, right, bot);

        gotoxy(left + 3, top + 1);
        printf("PILIH BAHAN UNTUK MENU");

        tampilBahan();   //perlu tersedia di bahanbaku

        gotoxy(left + 3, top + 1);
        printf("PILIH BAHAN UNTUK MENU");

        int y = bot - 6;
        gotoxy(left + 3, y);
        printf("[0] Selesai");

        if (pilihan == 0) break;
        if (pilihan == 1) {
            tambahBahan();
            continue;
        }

        if (pilihan < 1 || pilihan > totalBahan) {
            popupAlert(0, "Pilihan Tidak Valid!");
            continue;
        }

        //menyimpan relasi
        strcpy(menuBahan[totalMenuBahan].id_menu, m->id_menu);
        strcpy(menuBahan[totalMenuBahan].id_bahan,
               daftarBahan[pilihan - 1].id_bahan);

        gotoxy(left + 3, y + 5);
        printf("Jumlah Pemakaian : ");
        scanf("%s", buffer);

        menuBahan[totalMenuBahan].jumlah = buffer;
        totalMenuBahan++;
    }
}

void ubahMenu() {
    // char idTarget[20]; ganti jadi no urut
    int noMenu;
    char buffer[100];
    int left = 30, top = 11, right = 105, bot = 35;

    //masukkan no urut menu
    while (1) {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        gotoxy(1, 10);  printf("UBAH DATA MENU");
        gotoxy(30, 10); printf("[ESC] Batal   [ENTER] Lanjut");
        gotoxy(30, 11); printf("Masukkan No Menu : ");
        showcurs();

        if (inputtext(buffer) == 0)return;
        noMenu = atoi(buffer) - 1; //← konversi No → index array

        // validasi index
        if (noMenu < 0 || noMenu >= jumlahMenu) {
            popupAlert(0, "No Menu Tidak Valid!");
            continue;
        }

        Menu *m = &daftarMenu[noMenu];

        //edit menu
        clearArea(27, 9, clearW, clearH);
        frame(left, top, right, bot);

        //header
        gotoxy(left + 2, top + 1); printf("=======================================");
        gotoxy(left + 2, top + 2); printf("              UBAH MENU               ");
        gotoxy(left + 2, top + 3); printf("=======================================");

        gotoxy(left, top - 1);
        printf("[ENTER] Lewati   [ESC] Batal");

        //data lama
        int y = top + 6;
        gotoxy(left + 2, y);     printf("No Menu   : %d", noMenu + 1);
        y += 2; gotoxy(left + 2, y); printf("Kategori  : %s", m->kategori);
        y += 2; gotoxy(left + 2, y); printf("Nama Menu : %s", m->nama_menu);
        y += 2; gotoxy(left + 2, y); printf("Harga     : Rp %.0lf", m->harga);
        y += 2; gotoxy(left + 2, y); printf("Deskripsi : %s", m->deskripsi);
        y += 2; gotoxy(left + 2, y); printf("Status    : %s",
                m->status == 1 ? "1 (Tersedia)" : "0 (Habis)");

        //mengedit kategori
        clearinput(left + 14, top + 8, 40);
        gotoxy(left + 14, top + 8); showcurs();
        if (inputtext(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(m->kategori, buffer);
        gotoxy(left+14, top+8); printf("%s", m->kategori);

        //mengedit nama
        clearinput(left + 14, top + 10, 40);
        gotoxy(left + 14, top + 10); showcurs();
        if (inputtext(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(m->nama_menu, buffer);
        gotoxy(left+14, top+10); printf("%s", m->nama_menu);

        //mengedit harga
        do {
            clearinput(left + 17, top + 12, 40);
            gotoxy(left + 17, top + 12); showcurs();if (inputtext(buffer) == 0) return; //harga lama
            if (strlen(buffer) == 0) break;if (onlyNum(buffer)) {
                m->harga = atof(buffer);
                break;
            }
        } while (1);
        gotoxy(left+17, top+12); printf("%.0lf", m->harga);

        //mengubah deskripsi
        clearinput(left + 14, top + 14, 50);
        gotoxy(left + 14, top + 14); showcurs();if (inputtext(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(m->deskripsi, buffer);
        gotoxy(left+14, top+14); printf("%s", m->deskripsi);

        //mengubah status
        clearinput(left + 14, top + 16, 40);
        gotoxy(left + 14, top + 16); showcurs();if (inputtext(buffer) == 0) return;
        if (strlen(buffer) > 0)
        {m->status = (strcmp(buffer, "1") == 0) ? 1 : 0;}

        //simpan data
        if (popupConfirm("Simpan Perubahan Menu?", "Ya", "Batal")) {
            saveMenu();
            popupAlert(1,"Data Menu Berhasil Diubah!");
            return;
        }
    }
}
void hapusMenu() {
    // char idTarget[20]; ganti by norut
    char buffer[10];
    int noMenu;

        while (1) {
            int clearW = consoleW() - 27;
            int clearH = consoleH() - 9;
            clearArea(27, 9, clearW, clearH);

            //judul serta input data
            gotoxy(1, 10);  printf("HAPUS DATA MENU");
            gotoxy(30, 10); printf("[ESC] Batal   [ENTER] Lanjut");
            gotoxy(30, 11); printf("Masukkan No Menu : ");
            showcurs();

            if (inputtext(buffer) == 0) return;
            noMenu = atoi(buffer) - 1; // ← No → index

            // validasi
            if (noMenu < 0 || noMenu >= jumlahMenu) {
                popupAlert(0, "No Menu Tidak Valid!");
                continue;
            }

            //mereview data
            gotoxy(30, 13); printf("Menu   : %s", daftarMenu[noMenu].nama_menu);
            gotoxy(30, 14); printf("Harga  : Rp %.0lf", daftarMenu[noMenu].harga);
            gotoxy(30, 15); printf("Status : %s", daftarMenu[noMenu].status ? "Tersedia" : "Habis");
            gotoxy(30, 16);printf("tekan ENTER untuk lanjut..."); getchar();

            //melakukan konfirmasi
            if (popupConfirm("Apakah ingin menghapus menu ini?", "Ya", "Batal")) {

                //menggeser array
                for (int i = noMenu; i < jumlahMenu - 1; i++) {
                    daftarMenu[i] = daftarMenu[i + 1];
                }
                jumlahMenu--;

                saveMenu();
                popupAlert(1,"Menu Berhasil Dihapus!");
                return;
            }
        }
    }

void detailMenu()
{
    char buffer[10];
    int pilihan;

    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    gotoxy(1, 10);  printf("DETAIL MENU");
    gotoxy(30, 10); printf("[ESC] Batal   [ENTER] Lanjut");
    gotoxy(30, 11); printf("Masukkan No Menu : ");
    showcurs();

    if (inputtext(buffer) == 0) return;

    pilihan = atoi(buffer) - 1; // ← konversi No → index array

    // validasi index
    if (pilihan < 0 || pilihan >= jumlahMenu) {
        popupAlert(0, "No Menu Tidak Valid!");
        return;
    }

    Menu m = daftarMenu[pilihan];

    // frame detail
    int left = 30, top = 13, right = 100, bot = 32;
    frame(left, top, right, bot);

    gotoxy(left + 2, top + 1); printf("DETAIL MENU TERPILIH");

    int y = top + 3;
    gotoxy(left + 2, y);     printf("No Menu   : %d", pilihan + 1);
    y += 2; gotoxy(left + 2, y); printf("Kategori  : %s", m.kategori);
    y += 2; gotoxy(left + 2, y); printf("Nama Menu : %s", m.nama_menu);
    y += 2; gotoxy(left + 2, y); printf("Harga     : Rp %.0lf", m.harga);
    y += 2; gotoxy(left + 2, y); printf("Deskripsi : %s", m.deskripsi);
    y += 2; gotoxy(left + 2, y); printf("Status    : %s", m.status ? "Tersedia" : "Habis");

    gotoxy(left + 2, bot - 2);
    printf("Tekan tombol apa saja untuk kembali...");
    getch();
}

void tampilkanTabel(int page) {
        applyColors();

        int maxPage = (jumlahMenu == 0) ? 1 : ((jumlahMenu - 1) / ITEMS_PER_PAGE) + 1;

        if (page > maxPage) page = maxPage;
        if (page < 1) page = 1;
        currentPage = page;

        int start = (page - 1) * ITEMS_PER_PAGE;
        int end = start + ITEMS_PER_PAGE;
        if (end > jumlahMenu) end = jumlahMenu;

        printf("\n");
        printf("|======|==================|========================|==========|=========================|============|\n");
        printf("| %-4s | %-16s | %-22s | %-8s | %-23s | %-10s |\n",
               "No", "Kategori", "Nama Menu", "Harga", "Deskripsi", "Status");
        printf("|======|==================|========================|==========|=========================|============|\n");

        for (int i = start; i < end; i++) {
            char statusTxt[12];
            strcpy(statusTxt, (daftarMenu[i].status == 1) ? "Tersedia" : "Habis");

            char desc_short[24];
            if (strlen(daftarMenu[i].deskripsi) > 23) {
                strncpy(desc_short, daftarMenu[i].deskripsi, 20);
                desc_short[20] = '.';
                desc_short[21] = '.';
                desc_short[22] = '.';
                desc_short[23] = '\0';
            } else {
                strcpy(desc_short, daftarMenu[i].deskripsi);
            }

            printf("| %-4s | %-16s | %-22s | %8.0lf | %-23s | %-10s |\n",
                   i+1,
                   daftarMenu[i].kategori,
                   daftarMenu[i].nama_menu,
                   daftarMenu[i].harga,
                   desc_short,
                   statusTxt);
        }

        printf("|======|==================|========================|==========|=========================|============|\n");
        printf("Halaman: %d / %d  (Total Menu: %d)\n", currentPage, maxPage, jumlahMenu);
    }
void lihatMenu() {
    applyColors();
    if (jumlahMenu == 0) {
        system("cls");
        printf("\n[INFO] Belum ada menu yang tersedia.\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }
    int pilihan;
    int maxPage = ((jumlahMenu - 1) / ITEMS_PER_PAGE) + 1;

    do {
        system("cls");

        //header
        gotoxy(5, 2);printf("|=======================================|");
        gotoxy(5, 3);printf("|           DAFTAR MENU                  |");
        gotoxy(5, 4);printf("|=======================================|");

        //tabel
        tampilkanTabel(currentPage);

        //navigasi
        gotoxy(5, 22);
        printf("[1] Halaman Sebelumnya   [2] Halaman Selanjutnya   [0] Kembali");

        gotoxy(5, 24);
        printf("Pilihan: ");

        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n'); // ← bukan sebagai tampilan
            continue;
        }
        while (getchar() != '\n');

        if (pilihan == 1 && currentPage > 1) {
            currentPage--;
        } else if (pilihan == 2 && currentPage < maxPage) {
            currentPage++;
        }

    } while (pilihan != 0);

    currentPage = 1;
}
#endif //EATBOX_MENU_H