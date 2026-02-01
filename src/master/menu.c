#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data.h"
#include "../../include/function.h"
#include "../../include/master/menu.h"

#include "../../include/master/bahanBaku.h"
#include "../../include/master/resep.h"

Menu daftarMenu[MAX_MENU];
int jumlahMenu;

void saveMenu() {
    FILE *f = fopen(FILE_MENU, "wb");
    if (!f) return;

    fwrite(&jumlahMenu, sizeof(int), 1, f);
    fwrite(daftarMenu, sizeof(Menu), jumlahMenu, f);

    fclose(f);
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
int hitungMenuAktif()
{
    int count = 0;
    for (int i = 0; i < jumlahMenu; i++)
    {
        if (daftarMenu[i].status == 1)
            count++;
    }
    return count;
}

void tambahMenu() {
    Menu m;
    char buffer[50]; // Buffer sementara untuk validasi angka
    left = 30, top = 11, right = 105, bot = 35;

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
            if (inputbebas(m.nama_menu) == 0) return;
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
            if (inputbebas(m.deskripsi) == 0) return;
            if (strlen(m.deskripsi) > 0) break;
        } while (1);

        // --- 3. KONFIRMASI SIMPAN ---
        if (popupConfirm("Simpan Menu Ini?", "Ya", "Batal")) {
            daftarMenu[jumlahMenu++] = m;
            saveMenu();
            popupAlert(1,"Menu Berhasil Ditambahkan!");
            kelolaResepMenu(m.id_menu);
            // return; // Keluar setelah simpan
        }
    }
}
void ubahMenu() {
    int noMenu;
    char buffer[100];
    left = 30, top = 11, right = 105, bot = 35;

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

        char hargaMenu[30];
        formatHarga(m->harga, hargaMenu);

        //data lama
        int y = top + 6;
        gotoxy(left + 2, y);     printf("No Menu   : %d", noMenu + 1);
        y += 2; gotoxy(left + 2, y); printf("Kategori  : %s", m->kategori);
        y += 2; gotoxy(left + 2, y); printf("Nama Menu : %s", m->nama_menu);
        y += 2; gotoxy(left + 2, y); printf("Harga     : Rp %6s", hargaMenu);
        y += 2; gotoxy(left + 2, y); printf("Deskripsi : %s", m->deskripsi);
        y += 2; gotoxy(left + 2, y); printf("Status    : %s",
                m->status == 1 ? "1 (Tersedia)" : "0 (Habis)");

        //mengedit harga
        do {
            clearinput(left + 17, top + 12, 40);
            gotoxy(left + 17, top + 12); showcurs();if (inputtext(buffer) == 0) return; //harga lama
            if (strlen(buffer) == 0) break;if (onlyNum(buffer)) {
                m->harga = atof(buffer);
                break;
            }
        } while (1);
        gotoxy(left+17, top+12); printf("%6s", hargaMenu);

        //mengubah deskripsi
        clearinput(left + 14, top + 14, 50);
        gotoxy(left + 14, top + 14); showcurs();if (inputbebas(buffer) == 0) return;
        if (strlen(buffer) > 0) strcpy(m->deskripsi, buffer);
        gotoxy(left+14, top+14); printf("%s", m->deskripsi);

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

            char hargaMenu[30];
            formatHarga(daftarMenu[noMenu].harga, hargaMenu);

            //mereview data
            gotoxy(30, 13); printf("Menu   : %s", daftarMenu[noMenu].nama_menu);
            gotoxy(30, 14); printf("Harga  : Rp %6s", hargaMenu);
            gotoxy(30, 15); printf("Status : %s", daftarMenu[noMenu].status ? "Tersedia" : "Habis");
            gotoxy(30, 16);printf("tekan ENTER untuk lanjut..."); getchar();

            //melakukan konfirmasi
            if (popupConfirm("Apakah ingin menghapus menu ini?",    "Ya", "Batal")) {
                daftarMenu[noMenu].status = 0;

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
    loadResep();
    loadBahan();

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
    left = 30, top = 13, right = 100, bot = 32;
    frame(left, top, right, bot);

    char hargaMenu[30];
    formatHarga(m.harga, hargaMenu);

    gotoxy(left + 2, top + 1); printf("DETAIL MENU TERPILIH");

    int y = top + 3;
    gotoxy(left + 2, y);     printf("No Menu   : %d", pilihan + 1);
    y += 2; gotoxy(left + 2, y); printf("Kategori  : %s", m.kategori);
    y += 2; gotoxy(left + 2, y); printf("Nama Menu : %s", m.nama_menu);
    y += 2; gotoxy(left + 2, y); printf("Harga     : Rp %6s", hargaMenu);
    y += 2; gotoxy(left + 2, y); printf("Deskripsi : %s", m.deskripsi);
    y += 2; gotoxy(left + 2, y); printf("Status    : %s", m.status ? "Tersedia" : "Habis");

    frame(right + 1,top, right+25, bot);
    int yres = top +2;
    gotoxy(right + 3, top+1); printf("RESEP MENU");
    yres++;

    int adaResep = 0;

    for (int i = 0; i < totalResep; i++) {
        if (strcmp(daftarResep[i].id_menu, m.id_menu) == 0) {
            int idxBahan = cariBahanByID(daftarResep[i].id_bahan);
            if (idxBahan != -1) {
                gotoxy(right + 3, yres);
                printf("- %s : %d %s",
                    daftarBahan[idxBahan].nama_bahan,
                    daftarResep[i].jumlah,
                    daftarBahan[idxBahan].satuan
                );
                yres++;
                adaResep = 1;
            }
        }
    }

    if (!adaResep) {
        gotoxy(right + 3, yres);
        printf("(Belum ada resep)");
    }

    gotoxy(left + 2, bot - 2);
    printf("Tekan tombol apa saja untuk kembali...");
    getch();
}
void tampilkanTabel(int page) {
    currentpage = 1;

        applyColors();

        int maxPage = (jumlahMenu == 0) ? 1 : ((jumlahMenu - 1) / ITEMS_PER_PAGE) + 1;

        if (page > maxPage) page = maxPage;
        if (page < 1) page = 1;
        currentpage = page;

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

            char hargaMenu[30];
            formatHarga(daftarMenu[i].harga, hargaMenu);

            printf("| %-4s | %-16s | %-22s | %6s | %-23s | %-10s |\n",
                   i+1,
                   daftarMenu[i].kategori,
                   daftarMenu[i].nama_menu,
                   hargaMenu,
                   desc_short,
                   statusTxt);
        }

        printf("|======|==================|========================|==========|=========================|============|\n");
        printf("Halaman: %d / %d  (Total Menu: %d)\n", currentpage, maxPage, jumlahMenu);
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
        tampilkanTabel(currentpage);

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

        if (pilihan == 1 && currentpage > 1) {
            currentpage--;
        } else if (pilihan == 2 && currentpage < maxPage) {
            currentpage++;
        }

    } while (pilihan != 0);

    currentpage = 1;
}

int getMenuNumber(const char *id) {
    int num = 0;
    sscanf(id, "MN%d", &num);
    return num;
}

void sortMenuByStatus() {
    Menu temp;
    for (int i = 0; i < jumlahMenu - 1; i++) {
        for (int j = 0; j < jumlahMenu - i - 1; j++) {

            int statusA = daftarMenu[j].status;
            int statusB = daftarMenu[j + 1].status;

            int idA = getMenuNumber(daftarMenu[j].id_menu);
            int idB = getMenuNumber(daftarMenu[j + 1].id_menu);

            // 1️⃣ status aktif dulu
            if (statusA < statusB) {
                temp = daftarMenu[j];
                daftarMenu[j] = daftarMenu[j + 1];
                daftarMenu[j + 1] = temp;
            }
            // 2️⃣ status sama → ID lebih besar (newest) dulu
            else if (statusA == statusB && idA < idB) {
                temp = daftarMenu[j];
                daftarMenu[j] = daftarMenu[j + 1];
                daftarMenu[j + 1] = temp;
            }
        }
    }
}

//membaca data menu ke file
void loadMenu() {
    FILE *f = fopen(FILE_MENU, "rb");
    if (!f) {
        jumlahMenu = 0;
        return;
    }

    fread(&jumlahMenu, sizeof(int), 1, f);
    fread(daftarMenu, sizeof(Menu), jumlahMenu, f);

    fclose(f);
    sortMenuByStatus();
}
//tambahan buat penyesuaian
int dataMenu(int left, int startY, int page)
{
    if (jumlahMenu == 0)    loadMenu();

    int limit = 20; // maksimal yang di tampilkan
    int startIndex = (page - 1) * limit;
    int printedCount = 0;

    for (int i = startIndex; i < jumlahMenu; i++)
    {
        if (printedCount >= limit) break;

        // Potong deskripsi biar gak kepanjangan
        char desc_short[24];
        if (strlen(daftarMenu[i].deskripsi) > 23) {
            strncpy(desc_short, daftarMenu[i].deskripsi, 20);
            strcat(desc_short, "...");
        } else {
            strcpy(desc_short, daftarMenu[i].deskripsi);
        }

        if (daftarMenu[i].status != 1) setRGBColor(210, 212, 200, 0);

        int y = startY + printedCount;
        char hargaMenu[30];
        formatHarga(daftarMenu[i].harga, hargaMenu);

        // Cetak pakai gotoxy (Sesuaikan koordinat X dengan showMenu kamu)
        gotoxy(left+2, y);  printf("%d", i+1);
        gotoxy(left+10, y); printf("%-15.15s", daftarMenu[i].nama_menu); // Nama Menu
        gotoxy(left+27, y); printf("%-15.15s", daftarMenu[i].kategori);  // Kategori
        gotoxy(left+44, y); printf("Rp %6s", hargaMenu);   // Harga
        gotoxy(left+60, y); printf("%-20.20s", desc_short);              // Deskripsi
        gotoxy(left+85, y); printf("%s", (daftarMenu[i].status == 1 ? "Tersedia" : "Habis")); // Status

        printedCount++;
    }
    return jumlahMenu; // Kembalikan total data untuk hitung paging
}