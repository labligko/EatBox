#ifndef EATBOX_MANAJER_H
#define EATBOX_MANAJER_H

int currentPages = 1;

#define VIEW_ALL 0
#define VIEW_BULANAN 1
#define VIEW_TAHUNAN 2

int viewMode = VIEW_ALL;
int filterBulan = 0;
int filterTahun = 0;

int cocokFilter(Pesanan p)
{
    if (viewMode == VIEW_ALL)
        return 1;

    if (viewMode == VIEW_BULANAN)
        return p.tanggal.bulan == filterBulan &&
               p.tanggal.tahun == filterTahun;

    if (viewMode == VIEW_TAHUNAN)
        return p.tanggal.tahun == filterTahun;

    return 0;
}

int lihatPesanan()
{
    FILE *f = fopen("FILE/pesanan.dat", "rb");
    if (!f) return 0;

    Pesanan p;
    int total = 0;
    int shown = 0;
    int start = (currentPage - 1) * 20;

    int left = 28;
    int top  = 11;
    int y = top + 3;

    while (fread(&p, sizeof(Pesanan), 1, f))
    {
        if (!cocokFilter(p)) continue;

        if (total >= start && shown < 20)
        {
            char jam[6];
            formatJam(p.tanggal, jam);

            gotoxy(left+2, y);  printf("%-3d", total+1);
            gotoxy(left+6, y);  printf("%-12s", p.id_akun);
            gotoxy(left+20, y); printf("%-5d", p.no_meja);
            gotoxy(left+36, y); printf("Rp%.0f", p.total);
            gotoxy(left+50, y); printf("%-10s", p.status);
            gotoxy(left+66, y); printf("%s", jam);

            y++;
            shown++;
        }
        total++;
    }

    fclose(f);
    return total; // penting buat paging
}

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

void headerLaporan()
{
    int left = 28, right = 131, top = 11, bot = 34;
    frame(left, top, right, bot);

    gotoxy(left+2, top+1);  printf("No");
    gotoxy(left+6, top+1);  printf("Kasir");
    gotoxy(left+20, top+1); printf("Meja");
    gotoxy(left+36, top+1); printf("Total");
    gotoxy(left+50, top+1); printf("Status");
    gotoxy(left+66, top+1); printf("Waktu");

    for (int x = left+1; x < right; x++)
        gotoxy(x, top+2), printf("─");
}

void manajer(char nama[50])
{
    system("cls");
    applyColors(); appname(43,1);

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

        char tgl[20];
        formatTanggal(now(), tgl);

        // JUDUL
        if (viewMode == VIEW_ALL)
            gotoxy(60,10), printf("SEMUA DATA PENJUALAN");
        else if (viewMode == VIEW_BULANAN)
            gotoxy(55,10), printf("LAPORAN BULAN %02d/%d", filterBulan, filterTahun);
        else
            gotoxy(60,10), printf("LAPORAN TAHUN %d", filterTahun);

        headerLaporan();

        int totalPesan = lihatPesan();
        int maxPage = (totalPesan == 0) ? 1 : (totalPesan - 1) / 20 + 1;

        gotoxy(29,35);
        printf("Halaman %d / %d | Total: %d   [<] Prev  [>] Next",
               currentPage, maxPage, totalPesan);

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

#endif //EATBOX_MANAJER_H