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
// int getKaryawanByID(const char *id, Karyawan *out)
// {
//     FILE *f = fopen("../FILE/karyawan.dat", "rb");
//     if (!f) return 0;
//
//     while (fread(out, sizeof(Karyawan), 1, f))
//     {
//         if (strcmp(out->id, id) == 0 && out->status == 1)
//         {
//             fclose(f);
//             return 1;
//         }
//     }
//     fclose(f);
//     return 0;
// }

int getKaryawanByID(const char *id, Karyawan *out)
{
    FILE *f = fopen("../FILE/karyawan.dat", "r");
    if (!f) return 0;

    char line[1024];
    char f_id[20], f_user[20], f_pass[50], f_nama[50];
    char f_telp[20], f_email[50], f_role[20], f_alamat[255];
    int f_stat;

    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0;

        sscanf(line,
            "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
            f_id, f_user, f_pass, f_nama,
            f_telp, f_email, f_role, f_alamat, &f_stat
        );

        if (strcmp(f_id, id) == 0 && f_stat == 1)
        {
            strcpy(out->id, f_id);
            strcpy(out->username, f_user);
            strcpy(out->password, f_pass);
            strcpy(out->nama, f_nama);
            strcpy(out->telp, f_telp);
            strcpy(out->email, f_email);
            strcpy(out->role, f_role);
            strcpy(out->alamat, f_alamat);
            out->status = f_stat;

            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
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
    FILE *f = fopen("../FILE/pembayaran.dat", "rb");
    if (!f) return 0;

    Pembayaran b;
    Karyawan k;

    int total = 0, shown = 0;
    int start = (currentPage - 1) * 20;

    int left = 28;
    int y = 14;

    while (fread(&b, sizeof(Pembayaran), 1, f))
    {
        if (!cocokFilterBayar(b)) continue;

        if (total >= start && shown < 20)
        {
            char tgl[25];
            char namaKasir[50] = "-";

            formatTanggalJam(b.tanggal, tgl);

            if (getKaryawanByID(b.id_akun, &k))
                strcpy(namaKasir, k.nama);

            gotoxy(left+2,  y); printf("%-3d", total + 1);
            gotoxy(left+7,  y); printf("%-20s", tgl);
            gotoxy(left+30, y); printf("%-20s", namaKasir);
            gotoxy(left+55, y); printf("Rp%.0f", b.jumlah);
            gotoxy(left+72, y); printf("%s",
                b.metode_bayar == 1 ? "TUNAI" : "NON-TUNAI");

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
    currentPage = 1;
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
    currentPage = 1;
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
