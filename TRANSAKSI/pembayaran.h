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

int pembayaran(char *id_pesan, double total) {
    Pembayaran b;

    autoIDBayar(b.id_bayar);
    strcpy(b.id_pesan, id_pesan);
    strcpy(b.id_akun, currentKasirID);
    b.tanggal = now();
    b.jumlah = total;

    gotoxy(30,15); printf("Metode Bayar: ");
    inputtext(b.metode_bayar);

    strcpy(b.status, "SUCCESS");

    FILE *f = fopen("../FILE/pembayaran.dat", "ab");
    fwrite(&b, sizeof(Pembayaran), 1, f);
    fclose(f);

    return 1;
}


#endif //EATBOX_PEMBAYARAN_H