#ifndef PERAPIHAN_MENU_H
#define PERAPIHAN_MENU_H

#define ITEMS_PER_PAGE 10
#define MAX_MENU 100

void saveMenu();
void generateID(char *id);
int cariMenuByID(char *id);
int hitungMenuAktif();

void tambahMenu();
void ubahMenu();
void hapusMenu();

void detailMenu();
void tampilkanTabel(int page);
void lihatMenu();

void sortMenuByStatus();
void loadMenu();
int dataMenu(int left, int startY, int page);

#endif //PERAPIHAN_MENU_H