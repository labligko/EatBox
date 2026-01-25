#ifndef PERAPIHAN_MEJA_H
#define PERAPIHAN_MEJA_H

void generateIDMeja(char *id);
int cariMejaNorut(int noUrut);
int cariMeja(int noMeja);
void loadMeja();
void saveMeja();

void tambahMeja();
int renderTabelMeja(int left, int top, int right, int bot, int page);
int hitungMejaAktif();
void ubahMeja();
void hapusMeja();

#endif //PERAPIHAN_MEJA_H