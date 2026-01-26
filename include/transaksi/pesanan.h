#ifndef PERAPIHAN_PESANAN_H
#define PERAPIHAN_PESANAN_H

void autoIDPesan(char *out);
int findMejaByNomor(int nomor);
void setMeja(const char *id, int ket);
void resetMejaJikaBedaHari();

void showMiniMeja();
void showMiniMenu(int page);
void tambahPesan();
void selesaiPesan();
int lihatPesan(int page);
int loadPesananHariIni();

#endif //PERAPIHAN_PESANAN_H