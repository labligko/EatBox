#ifndef EATBOX_MANAJER_H
#define EATBOX_MANAJER_H

#include "../function.h"
#include "../data.h"

extern int currentPage;

#define VIEW_ALL 0
#define VIEW_BULANAN 1
#define VIEW_TAHUNAN 2

int viewMode = VIEW_ALL;
int filterBulan = 0;
int filterTahun = 0;

/* =====================================================
   UTIL JOIN PESANAN
===================================================== */
int getPesananByID(const char *id, Pesanan *out)
{
    FILE *f = fopen("../FILE/pesanan.dat", "rb");
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
    FILE *f = fopen("../FILE/pembayaran.dat", "rb"); // FIX PATH
    if (!f) return 0;

    Pembayaran b;
    Pesanan p;

    int total = 0;
    int shown = 0;
    int start = (currentPage - 1) * 20;

    int left = 28;
    int top  = 11;
    int y = top + 3;

    while (fread(&b, sizeof(Pembayaran), 1, f))
    {
        if (!cocokFilterBayar(b)) continue;

        if (total >= start && shown < 20)
        {
            char jam[6];
            formatJam(b.tanggal, jam);

            int noMeja = 0;
            if (getPesananByID(b.id_pesan, &p))
                noMeja = p.no_meja;

            gotoxy(left+2, y);  printf("%-3d", total + 1);
            gotoxy(left+6, y);  printf("%-12s", b.id_akun);
            gotoxy(left+20, y); printf("%-5d", noMeja);
            gotoxy(left+36, y); printf("Rp%.0f", b.jumlah);
            gotoxy(left+50, y); printf("%-10s",
                b.metode_bayar == 1 ? "TUNAI" : "NON");
            gotoxy(left+66, y); printf("%s", jam);

            y++;
            shown++;
        }
        total++;
    }

    fclose(f);
    return total;
}

/* =====================================================
   FILTER INPUT
===================================================== */
void bulanan()
{
    clearArea(27, 9, consoleW(), consoleH());

    gotoxy(30,12); printf("INPUT BULAN (1-12): ");
    scanf("%d", &filterBulan);

    gotoxy(30,13); printf("INPUT TAHUN: ");
    scanf("%d", &filterTahun);

    viewMode = VIEW_BULANAN;
    currentPage = 1;
}

void tahunan()
{
    clearArea(27, 9, consoleW(), consoleH());

    gotoxy(30,12); printf("INPUT TAHUN: ");
    scanf("%d", &filterTahun);

    viewMode = VIEW_TAHUNAN;
    currentPage = 1;
}

/* =====================================================
   HEADER UI (KEEP)
===================================================== */
void headerLaporan()
{
    int left = 28, right = 131, top = 11, bot = 34;
    frame(left, top, right, bot);

    gotoxy(left+2, top+1);  printf("No");
    gotoxy(left+6, top+1);  printf("Kasir");
    gotoxy(left+20, top+1); printf("Meja");
    gotoxy(left+36, top+1); printf("Total");
    gotoxy(left+50, top+1); printf("Metode");
    gotoxy(left+66, top+1); printf("Waktu");

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
        " Bulanan", " Tahunan", " Keluar"
    };

    while (1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        if (viewMode == VIEW_ALL)
            gotoxy(60,10), printf("SEMUA DATA PENJUALAN");
        else if (viewMode == VIEW_BULANAN)
            gotoxy(55,10), printf("LAPORAN BULAN %02d/%d", filterBulan, filterTahun);
        else
            gotoxy(60,10), printf("LAPORAN TAHUN %d", filterTahun);

        headerLaporan();

        int totalData = lihatPesanan();
        int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

        gotoxy(29,35);
        printf("Halaman %d / %d | Total Transaksi: %d   [<] Prev  [>] Next",
               currentPage, maxPage, totalData);

        gotoxy(1,10); printf("Halo, %s", cutname(nama));
        gotoxy(1,20); printf("[↕] Pilih Menu");

        int pilih = menuSelect(1,12, menuSup, 3);

        if (pilih == -1 && currentPage > 1)
            currentPage--;
        else if (pilih == -2 && currentPage < maxPage)
            currentPage++;
        else if (pilih == 0)
            bulanan();
        else if (pilih == 1)
            tahunan();
        else if (pilih == 2)
            exit(0);
    }
}

#endif // EATBOX_MANAJER_H
