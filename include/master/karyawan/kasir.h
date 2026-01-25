#ifndef PERAPIHAN_KASIR_H
#define PERAPIHAN_KASIR_H

int getIDAkunByUsername(const char *username, char *outID);
void kasir(char nama[50]);
void tampilkanDeskripsiPesananByNo(int noUrut);
void detilPesan();

extern char currentKasir[50]; //deklarasi kasir saat ini
extern char listPesanHariIni[100][15];
extern int totalPesanHariIni;

#endif //PERAPIHAN_KASIR_H