#ifndef PERAPIHAN_PEMBAYARAN_H
#define PERAPIHAN_PEMBAYARAN_H

void autoIDBayar(char *out);
void SetMeja(const char *id, int ket);
void tampilDetailPesanan(const char *idPesan, char *kasirName, int xLeft, int yTop);

int pembayaran(char *id_pesan, double total, int xLeft, int yTop);
void showbayar(char *id_pesan, char *namaKasir, double total);

#endif //PERAPIHAN_PEMBAYARAN_H