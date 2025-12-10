#ifndef EATBOX_MENU_READ_H
#define EATBOX_MENU_READ_H

#include "data.h"
#include "function.h"

//variabel untuk read
extern Menu listMenu[MAX_MENU];
extern int jumlahMenu;
extern int currentPage;

// membaca data menu ke file
void loadMenu();

//menampilkan menu
void lihatMenu();
void tampilkanTabel(int page);

#endif
