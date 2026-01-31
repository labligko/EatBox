#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "../../include/data.h"
#include "../../include/function.h"
#include "../../include/master/resep.h"
#include "../../include/master/menu.h"
#include "../../include/transaksi/pembayaran.h"

void autoIDBayar(char *out) {
    FILE *f = fopen(FILE_PEMBAYARAN, "rb");
    Pembayaran b;
    int last = 0;

    if (f) {
        while (fread(&b, sizeof(Pembayaran), 1, f)) {
            sscanf(b.id_bayar, "PAY%d", &last);
        }
        fclose(f);
    }
    sprintf(out, "PAY%03d", last + 1);
}
void SetMeja(const char *id, int ket)
{
    FILE *f = fopen(FILE_MEJA, "rb+");
    if (!f) return;

    Meja m;
    while (fread(&m, sizeof(Meja), 1, f))
    {
        if (strcmp(m.id_meja, id) == 0)
        {
            m.keterangan = ket;
            fseek(f, -sizeof(Meja), SEEK_CUR);
            fwrite(&m, sizeof(Meja), 1, f);
            fflush(f);
            break;
        }
    }

    fclose(f);
}
void tampilDetailPesanan(const char *idPesan, char *kasirName, int xLeft, int yTop)
{
    loadMenu();
    FILE *fpDetail = fopen(FILE_DETAIL, "rb");
    FILE *fpPesan  = fopen(FILE_PESANAN, "rb");
    if (!fpDetail || !fpPesan) return;

    Pesanan p;
    int found = 0;

    while (fread(&p, sizeof(Pesanan), 1, fpPesan)) {
        if (strcmp(p.id_pesan, idPesan) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        gotoxy(xLeft, yTop); printf("Pesanan tidak ditemukan!");
        fclose(fpDetail); fclose(fpPesan);
        return;
    }

    // Header tabel
    int headY = yTop;

    gotoxy(xLeft, headY++); printf("------------------------------------------------------");
    gotoxy(xLeft, headY++); printf("ID Pesanan : %s", p.id_pesan);
    gotoxy(xLeft, headY++); printf("Kasir      : %s", kasirName);
    gotoxy(xLeft, headY++); printf(
        "Waktu      : %02d-%02d-%04d, %02d:%02d",
        p.tanggal.hari, p.tanggal.bulan, p.tanggal.tahun,
        p.tanggal.jam, p.tanggal.menit
    );
    gotoxy(xLeft, headY++); printf("Meja       : %d", p.no_meja);

    /* HEADER DETAIL */
    headY++; // KASIH JEDA 1 BARIS
    gotoxy(xLeft, headY++); printf("-----------------------------------------------------");
    gotoxy(xLeft, headY++); printf("Nama Menu   \t   Harga      Qty   Subtotal");
    gotoxy(xLeft, headY++); printf("-----------------------------------------------------");

    /* DETAIL START DI SINI */
    int detilY = headY;
    DetailPesanan d;
    Menu m;

    fseek(fpDetail, 0, SEEK_SET);
    while (fread(&d, sizeof(DetailPesanan), 1, fpDetail)) {
        if (strcmp(d.id_pesan, idPesan) != 0)
            continue;

        if (!getMenuByID(d.id_menu, &m)) {
            gotoxy(xLeft, detilY++);
            printf("[MENU %s TIDAK ADA]", d.id_menu);
            continue;
        }

        char hargaStr[30], subStr[30];

        formatHarga(m.harga, hargaStr);
        formatHarga(d.subtotal, subStr);

        gotoxy(xLeft, detilY++);
        printf("%-20.20s Rp %6s   %-4d Rp %8s", m.nama_menu, hargaStr, d.jumlah, subStr);
    }
    fclose(fpDetail);
    fclose(fpPesan);
}

int pembayaran(char *id_pesan, double total, int xLeft, int yTop) {
    Pembayaran b;
    memset(&b, 0, sizeof(Pembayaran)); // Mengisi buffer dengan 0 (membersihkan)
    int metode;   // 1 = TUNAI, 2 = NON-TUNAI
    double kembali;
    char totbayar[30];

    autoIDBayar(b.id_bayar);
    strcpy(b.id_pesan, id_pesan);
    strcpy(b.id_akun, currentKasirID);
    b.tanggal = now();
    b.jumlah = total;

    formatHarga(total, totbayar);

    int hY=yTop;
    gotoxy(xLeft-1,hY++); printf("--------------------------------");
    gotoxy(xLeft,hY++); printf("PEMBAYARAN");
    gotoxy(xLeft,hY++); printf("ID Bayar    : %s", b.id_bayar);
    gotoxy(xLeft,hY++); printf("Total       : RP %8s", totbayar);
    for (int i = yTop+1; i < bot; i++){
        gotoxy(xLeft-2, i); printf("|");
    }

    metode = 0;
    char buf[5];

    while (1) {
        gotoxy(xLeft, hY++); printf("Metode Bayar:");
        gotoxy(xLeft, hY++); printf("1. Tunai");
        gotoxy(xLeft, hY++); printf("2. Non-Tunai");
        gotoxy(xLeft, hY++); printf("Pilih (1/2): ");
        showcurs();

        if (inputField(buf) == 0)
        {
            FILE *f = fopen(FILE_PESANAN, "rb+");
            Pesanan p;

            while (fread(&p, sizeof(Pesanan), 1, f)) {
                if (strcmp(p.id_pesan, id_pesan) == 0) {
                    strcpy(p.status, "BATAL");
                    fseek(f, -sizeof(Pesanan), SEEK_CUR);
                    fwrite(&p, sizeof(Pesanan), 1, f);

                    if (strcmp(p.id_meja, "-") != 0)
                        SetMeja(p.id_meja, 1); // KOSONG
                    break;
                }
            }
            fclose(f);
            return 0;
        }

        metode = atoi(buf);
        if (metode == 1 || metode == 2) break;
    }
    b.metode_bayar = metode;

    if (b.metode_bayar == 1) { // TUNAI
        while (1) {
            clearinput(xLeft+10,hY,20);
            gotoxy(xLeft, hY); printf("Bayar (Rp): ");
            if (inputField(buf) == 0) return 0;

            b.bayar = atof(buf);
            if (b.bayar < total) {
                gotoxy(xLeft, hY+1); printf("Uang kurang!");
                continue;
            }

            kembali = b.bayar - total;
            break;
        }
        clearinput(xLeft, hY+1,20);
        gotoxy(xLeft, hY+1); printf("Kembalian : Rp%.0f", kembali); Sleep(1000);
        popupAlert(1, "Pebayaran berhasil");
    }
    if (b.metode_bayar == 2) { // NON-TUNAI
        gotoxy(xLeft, hY++); printf("[ QR CODE PEMBAYARAN ]");
        gotoxy(xLeft, hY++); printf("Scan menggunakan aplikasi e-wallet");
        gotoxy(xLeft, hY++); printf("Kode: %s", b.id_bayar);

        hY++; // jeda
        gotoxy(xLeft, hY++);
        printf("Menunggu pembayaran...");
        Sleep(5000);

        gotoxy(xLeft, hY++);
        printf("Pembayaran berhasil!");

        b.bayar = total;
        kembali = 0;

        popupAlert(1, "Pembayaran berhasil");
    }
    strcpy(b.status, "LUNAS");

    //update data pesanan
    FILE *fp = fopen(FILE_PESANAN, "rb+");
    Pesanan p;

    while (fread(&p, sizeof(Pesanan), 1, fp)) {
        if (strcmp(p.id_pesan, id_pesan) == 0) {
            strcpy(p.status, "LUNAS");
            fseek(fp, -sizeof(Pesanan), SEEK_CUR);
            fwrite(&p, sizeof(Pesanan), 1, fp);

            kurangiStokDariPesanan(id_pesan);

            break;
        }
    }
    fclose(fp);

    //update data pembayaran
    FILE *f = fopen(FILE_PEMBAYARAN, "ab");
    fwrite(&b, sizeof(Pembayaran), 1, f);
    fclose(f);

    return 1;
}
void showbayar(char *id_pesan, char *namaKasir, double total)
{
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    tampilDetailPesanan(id_pesan, namaKasir, 30, 10);
    pembayaran(id_pesan, total, 85, 10);
}