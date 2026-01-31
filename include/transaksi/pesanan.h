#ifndef PERAPIHAN_PESANAN_H
#define PERAPIHAN_PESANAN_H

void autoIDPesan(char *out);
int findMejaByNomor(int nomor);
void setMeja(const char *id, int ket);
int sudahResetHariIni();
void simpanResetHariIni();
void resetMejaJikaBedaHari();

void showMiniMeja(int page);
void showMiniMenu(int page);
void tambahPesan();
void selesaiPesan();
int lihatPesan(int page);
int loadPesananHariIni();

#endif //PERAPIHAN_PESANAN_H