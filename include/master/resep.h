#ifndef PERAPIHAN_RESEP_H
#define PERAPIHAN_RESEP_H

void saveResep();
void loadResep();

int cekResepAda(char *id_menu, char *id_bahan);
void kelolaResepMenu(char *id_menu);

int cariBahanByID(char *id);
void kurangiStokDariPesanan(char *id_pesan);
int cekStokMenu(const char *id_menu, int qty);

#endif //PERAPIHAN_RESEP_H