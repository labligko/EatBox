#ifndef EATBOX_PEMBAYARAN_H
#define EATBOX_PEMBAYARAN_H

#include "../function.h"
#include "../data.h"

void autoIDBayar(char *out) {
    FILE *f = fopen("../FILE/pembayaran.dat", "rb");
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
void tampilDetailPesanan(const char *idPesan, int xLeft, int yTop)
{
    FILE *fpDetail = fopen("../FILE/detail_pesanan.dat", "rb");
    FILE *fpPesan  = fopen("../FILE/pesanan.dat", "rb");
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
    printf("DETAIL PESANAN");

    printf("-------------------------------");

    printf("ID Pesanan : %s", p.id_pesan);
    printf("Tanggal    : %02d-%02d-%04d", p.tanggal.hari, p.tanggal.bulan, p.tanggal.tahun);
    printf("Jam        : %02d:%02d", p.tanggal.jam, p.tanggal.menit);
    printf("Meja       : %d", p.no_meja);


    DetailPesanan d;

    fseek(fpDetail, 0, SEEK_SET);
    while (fread(&d, sizeof(DetailPesanan), 1, fpDetail)) {
        if (strcmp(d.id_pesan, idPesan) == 0) {
            printf("%-12s %-5d Rp%.0f",d.id_menu, d.jumlah,d.subtotal);
        }
    }
}

int pembayaran(char *id_pesan, double total) {
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);
    Pembayaran b;

    autoIDBayar(b.id_bayar);
    strcpy(b.id_pesan, id_pesan);
    strcpy(b.id_akun, currentKasirID);
    b.tanggal = now();
    b.jumlah = total;

    gotoxy(30,13);
    printf("PEMBAYARAN");
    gotoxy(30,14);
    printf("ID Bayar    : %s", b.id_bayar);
    gotoxy(30,15); printf("Metode Bayar: "); showcurs();
    inputtext(b.metode_bayar);
    strcpy(b.status, "SUCCESS");

    printf("Total Bayar : Rp%.0f", total);

    FILE *f = fopen("../FILE/pembayaran.dat", "ab");
    fwrite(&b, sizeof(Pembayaran), 1, f);
    fclose(f);

    return 1;
}


#endif //EATBOX_PEMBAYARAN_H