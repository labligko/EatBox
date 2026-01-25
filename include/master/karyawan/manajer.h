#ifndef PERAPIHAN_MANAJER_H
#define PERAPIHAN_MANAJER_H

int getKaryawanByID(const char *id, Karyawan *out);
int getPesananByID(const char *id, Pesanan *out);
int cmpKasir(const void *a, const void *b);
int cmpTotal(const void *a, const void *b);
int cmpTanggal(const void *a, const void *b);

int cocokSearch(Pembayaran b);
void judulLaporan();

int cocokFilterBayar(Pembayaran b);
int lihatPesanan();

void bulanan();
void tahunan();
void menuUrutkan();
void menuCari();

void headerLaporan();
void manajer(char nama[50]);

#endif //PERAPIHAN_MANAJER_H