#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/data.h"
#include "../../../include/function.h"
#include "../../../include/master/karyawan/manajer.h"

#define VIEW_ALL 0
#define VIEW_BULANAN 1
#define VIEW_TAHUNAN 2
#define SORT_NONE 0
#define SORT_KASIR 1
#define SORT_TOTAL 2
#define SORT_TANGGAL 3

int sortMode = SORT_NONE;
int viewMode = VIEW_ALL;
int filterBulan = 0;
int filterTahun = 0;

char keyword[50] = "";
int searchMode = 0;  // 1 = kasir, 2 = metode

/* =====================================================
   UTIL JOIN PESANAN
===================================================== */
int getKaryawanByID(const char *id, Karyawan *out)
{
    FILE *f = fopen(FILE_KARYAWAN, "rb");
    if (!f) return 0;

    Karyawan k;
    while (fread(&k, sizeof(Karyawan), 1, f)) {
        if (strcmp(k.id, id) == 0 && k.status == 1) {
            *out = k; // copy struct langsung
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
int getPesananByID(const char *id, Pesanan *out)
{
    FILE *f = fopen(FILE_PESANAN, "rb");
    if (!f) return 0;

    while (fread(out, sizeof(Pesanan), 1, f))
    {
        if (strcmp(out->id_pesan, id) == 0)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int cmpKasir(const void *a, const void *b) {
    Pembayaran *x = (Pembayaran*)a;
    Pembayaran *y = (Pembayaran*)b;

    Karyawan kx = {0}, ky = {0};
    getKaryawanByID(x->id_akun, &kx);
    getKaryawanByID(y->id_akun, &ky);

    return strcmp(kx.nama, ky.nama);
}
int cmpTotal(const void *a, const void *b) {
    Pembayaran *x = (Pembayaran*)a;
    Pembayaran *y = (Pembayaran*)b;

    if (x->jumlah > y->jumlah) return -1;
    if (x->jumlah < y->jumlah) return 1;
    return 0;
}
int cmpTanggal(const void *a, const void *b) {
    Pembayaran *x = (Pembayaran*)a;
    Pembayaran *y = (Pembayaran*)b;

    if (x->tanggal.tahun != y->tanggal.tahun)
        return y->tanggal.tahun - x->tanggal.tahun;
    if (x->tanggal.bulan != y->tanggal.bulan)
        return y->tanggal.bulan - x->tanggal.bulan;
    return y->tanggal.hari - x->tanggal.hari;
}

int cocokSearch(Pembayaran b) {
    if (searchMode == 0) return 1;

    if (searchMode == 1) {
        Karyawan k;
        if (getKaryawanByID(b.id_akun, &k))
            return strstr(k.nama, keyword) != NULL;
    }

    if (searchMode == 2) {
        return (strcmp(keyword, "TUNAI") == 0 && b.metode_bayar == 1) ||
               (strcmp(keyword, "NON") == 0 && b.metode_bayar == 2);
    }

    return 0;
}

void judulLaporan()
{
    char info[100] = "";
    int x;

    // VIEW MODE
    if (viewMode == VIEW_ALL){
        x = 65; strcpy(info, "SEMUA DATA PENJUALAN");
    }
    else if (viewMode == VIEW_BULANAN){
        x = 55; sprintf(info, "LAPORAN BULAN %02d/%d", filterBulan, filterTahun);
    }
    else if (viewMode == VIEW_TAHUNAN){
        x = 60; sprintf(info, "LAPORAN TAHUN %d", filterTahun);
    }

    // SEARCH MODE
    if (searchMode == 1){
        x = 40; sprintf(info + strlen(info), " | HASIL PENCARIAN KASIR \"%s\"", keyword);
    }
    else if (searchMode == 2){
        x = 45; sprintf(info + strlen(info), " | METODE %s", (strcmp(keyword, "1") == 0 ? "TUNAI" : "NON-TUNAI"));
    }

    // SORT MODE
    if (sortMode == SORT_KASIR)
        strcat(info, " | DIURUTKAN KASIR");
    else if (sortMode == SORT_TOTAL)
        strcat(info, " | DIURUTKAN TOTAL");
    else if (sortMode == SORT_TANGGAL)
        strcat(info, " | DIURUTKAN TANGGAL");

    gotoxy(x, 10);
    printf("%s", info);
}

/* =====================================================
   FILTER PEMBAYARAN
===================================================== */
int cocokFilterBayar(Pembayaran b)
{
    if (strcmp(b.status, "LUNAS") != 0)
        return 0;

    if (viewMode == VIEW_ALL)
        return 1;

    if (viewMode == VIEW_BULANAN)
        return b.tanggal.bulan == filterBulan &&
               b.tanggal.tahun == filterTahun;

    if (viewMode == VIEW_TAHUNAN)
        return b.tanggal.tahun == filterTahun;

    return 0;
}

/* =====================================================
   VIEW DATA (PAGING)
===================================================== */
int lihatPesanan()
{
    FILE *f = fopen(FILE_PEMBAYARAN, "rb");
    if (!f) return 0;

    Pembayaran list[1000];
    int n = 0;

    while (fread(&list[n], sizeof(Pembayaran), 1, f))
    {
        if (!cocokFilterBayar(list[n])) continue;
        if (!cocokSearch(list[n])) continue;
        n++;
    }
    fclose(f);

    if (sortMode == SORT_KASIR)
        qsort(list, n, sizeof(Pembayaran), cmpKasir);
    else if (sortMode == SORT_TOTAL)
        qsort(list, n, sizeof(Pembayaran), cmpTotal);
    else if (sortMode == SORT_TANGGAL)
        qsort(list, n, sizeof(Pembayaran), cmpTanggal);

    int start = (currentpage - 1) * 20;
    int end = start + 20;
    if (end > n) end = n;

    int y = 14;
    int left = 28;

    for (int i = start; i < end; i++)
    {
        char tgl[25];
        char namaKasir[50] = "-";
        Karyawan k;

        formatTanggalJam(list[i].tanggal, tgl);
        if (getKaryawanByID(list[i].id_akun, &k))
            strcpy(namaKasir, k.nama);

        gotoxy(left+2,  y); printf("%-3d", i + 1);
        gotoxy(left+7,  y); printf("%-20s", tgl);
        gotoxy(left+30, y); printf("%-20s", namaKasir);
        gotoxy(left+55, y); printf("Rp%.0f", list[i].jumlah);
        gotoxy(left+72, y); printf("%s",
            list[i].metode_bayar == 1 ? "TUNAI" : "NON-TUNAI");

        y++;
    }

    return n;
}

/* =====================================================
   FILTER INPUT
===================================================== */
void bulanan()
{
    char bufBulan[5], bufTahun[6];
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    gotoxy(30, 11); printf("[ESC] Batal   [ENTER] Lanjut");
    gotoxy(30,12); printf("INPUT BULAN (1-12): ");
    showcurs();
    int r = inputField(bufBulan);
    if (r == 0) { // ESC
        return;
    }

    int bulan = atoi(bufBulan);
    if (bulan < 1 || bulan > 12) {
        gotoxy(30,14); printf("Bulan tidak valid!");
        _getch();
        return;
    }

    // INPUT TAHUN
    gotoxy(30,13); printf("INPUT TAHUN       : ");
    showcurs();
    r = inputField(bufTahun);
    if (r == 0) {
        return;
    }

    int tahun = atoi(bufTahun);
    if (tahun < 2000 || tahun > 2100) {
        gotoxy(30,14); printf("Tahun tidak valid!");
        _getch();
        return;
    }

    filterBulan = bulan;
    filterTahun = tahun;
    viewMode = VIEW_BULANAN;
    currentpage = 1;
}
void tahunan()
{
    char bufTahun[6];
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    gotoxy(30, 11); printf("[ESC] Batal   [ENTER] Lanjut");
    gotoxy(30,12); printf("INPUT TAHUN: ");
    showcurs();

    int r = inputField(bufTahun);
    if (r == 0) {
        return;
    }

    int tahun = atoi(bufTahun);
    if (tahun < 2000 || tahun > 2100) {
        gotoxy(30,14); printf("Tahun tidak valid!");
        _getch();
        return;
    }

    filterTahun = tahun;
    viewMode = VIEW_TAHUNAN;
    currentpage = 1;
}
void menuUrutkan()
{
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    char *opsi[] = {
        " Tidak Diurutkan",
        " Berdasarkan Kasir",
        " Berdasarkan Total Terbesar",
        " Berdasarkan Tanggal Terbaru"
    };

    int p = menuSelect(30, 12, opsi, 4);
    if (p >= 0) {
        sortMode = p;
        currentpage = 1;
    }
}
void menuCari()
{
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    char *opsi[] = {
        " Nama Kasir",
        " Metode Bayar",
        " Reset Pencarian"
    };

    int p = menuSelect(30, 12, opsi, 3);
    if (p < 0) return;

    clearArea(27, 9, clearW, clearH);
    showcurs();

    if (p == 0) {
        gotoxy(30, 12);
        printf("Cari Nama Kasir: ");
        inputtext(keyword);
        searchMode = 1;
    }
    else if (p == 1) {
        gotoxy(30, 12);
        printf("Metode (1 = TUNAI / 2 = NON-TUNAI): ");
        inputField(keyword);
        strupr(keyword);   // <-- penting
        searchMode = 2;
    }
    else {
        searchMode = 0;
        keyword[0] = 0;
    }

    currentpage = 1;
}

/* =====================================================
   HEADER UI (KEEP)
===================================================== */
void headerLaporan()
{
    int left = 28, right = 131, top = 11, bot = 34;
    frame(left, top, right, bot);

    gotoxy(left+2,  top+1); printf("No");
    gotoxy(left+7,  top+1); printf("Tanggal");
    gotoxy(left+30, top+1); printf("Kasir");
    gotoxy(left+55, top+1); printf("Total");
    gotoxy(left+72, top+1); printf("Metode");

    for (int x = left+1; x < right; x++)
        gotoxy(x, top+2), printf("─");
}

/* =====================================================
   MENU MANAJER
===================================================== */
void manajer(char nama[50])
{
    system("cls");
    applyColors();
    appname(43,1);

    garisx(0,8);
    garisy(25,8);

    strcpy(currentKasirID, nama);

    char *menuSup[] = {
        " Semua Data", " Bulanan", " Tahunan", " Urutkan", " Cari", " Keluar"
    };

    while (1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        judulLaporan();
        headerLaporan();

        int totalData = lihatPesanan();
        int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

        gotoxy(29,35);
        printf("Halaman %d / %d | Total Transaksi: %d   [<] Prev  [>] Next",
               currentpage, maxPage, totalData);

        gotoxy(1,10); printf("Halo, %s", cutname(nama));
        gotoxy(1,20); printf(" [↕]      Pilih Menu");
        gotoxy(1,21); printf(" [ENTER]  Lanjut");

        int pilih = menuSelect(1,12, menuSup, 6);

        if (pilih == -1 && currentpage > 1)
            currentpage--;
        else if (pilih == -2 && currentpage < maxPage)
            currentpage++;
        else if (pilih == 0)
            viewMode = VIEW_ALL;
        else if (pilih == 1)
            bulanan();
        else if (pilih == 2)
            tahunan();
        else if (pilih == 3)
            menuUrutkan();
        else if (pilih == 4)
            menuCari();
        else if (pilih == 5)
            if (popupConfirm("Apakah anda yakin ingin keluar?", "Ya", "Tidak"))
                return;
    }
}