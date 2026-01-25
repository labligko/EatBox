#ifndef PERAPIHAN_BAHANBAKU_H
#define PERAPIHAN_BAHANBAKU_H

void saveBahan();
void loadBahan();

void generateIDBahan(char *output);
int getIndexByNoUrut(int no);
int hitungBahanAktif();

int renderTabelBahan(int left, int top, int right, int bot, int page);

void tambahBahan();
void ubahBahan();
void hapusBahan();

#endif //PERAPIHAN_BAHANBAKU_H