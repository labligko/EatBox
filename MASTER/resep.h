#ifndef EATBOX_RESEP_H
#define EATBOX_RESEP_H

#include <stdio.h>

#include "bahanbaku.h"
#include "../data.h"

void saveResep() {
    FILE *f = fopen(FILE_RESEP, "wb");
    if (!f) return;
    fwrite(&totalResep, sizeof(int), 1, f);
    fwrite(daftarResep, sizeof(ResepMenu), totalResep, f);
    fclose(f);
}

void loadResep() {
    FILE *f = fopen(FILE_RESEP, "rb");
    if (!f) return;
    fread(&totalResep, sizeof(int), 1, f);
    fread(daftarResep, sizeof(ResepMenu), totalResep, f);
    fclose(f);
}

void kelolaResepMenu(char *id_menu) {
    char buf[20];

    while (1) {
        clearArea(27, 9, consoleW(), consoleH());
        gotoxy(30,10); printf("KELOLA RESEP MENU [%s]", id_menu);
        gotoxy(30,12); printf("Daftar Bahan:");

        int y = 14;
        int no = 1;
        for (int i = 0; i < totalBahan; i++) {
            if (daftarBahan[i].status != 1) continue;
            gotoxy(30, y++);
            printf("%d. %s (%s)", no++, daftarBahan[i].nama_bahan, daftarBahan[i].satuan);
        }

        gotoxy(30, y+1);
        printf("Pilih No Bahan (0 = Tambah Bahan Baru): ");
        showcurs();
        inputtext(buf);

        int pilih = atoi(buf);
        if (pilih == 0) {
            tambahBahan();
            loadBahan();
            continue;
        }

        int idxBahan = getIndexByNoUrut(pilih);
        if (idxBahan == -1) continue;

        gotoxy(30, y+3);
        printf("Jumlah pemakaian per 1 menu: ");
        inputtext(buf);
        if (!onlyNum(buf)) continue;

        ResepMenu r;
        strcpy(r.id_menu, id_menu);
        strcpy(r.id_bahan, daftarBahan[idxBahan].id_bahan);
        r.jumlah = atoi(buf);

        daftarResep[totalResep++] = r;
        saveResep();

        if (!popupConfirm("Tambah bahan lain?", "Ya", "Selesai"))
            break;
    }
}

int cariBahanByID(char *id) {
    for (int i = 0; i < totalBahan; i++) {
        if (strcmp(daftarBahan[i].id_bahan, id) == 0)
            return i;
    }
    return -1;
}

void kurangiStokBahan(char *id_menu, int qty) {
    loadResep();
    loadBahan();

    for (int i = 0; i < totalResep; i++) {
        if (strcmp(daftarResep[i].id_menu, id_menu) == 0) {
            int idx = cariBahanByID(daftarResep[i].id_bahan);
            if (idx != -1) {
                daftarBahan[idx].stok -= daftarResep[i].jumlah * qty;
                if (daftarBahan[idx].stok < 0)
                    daftarBahan[idx].stok = 0;
            }
        }
    }
    saveBahan();
}



#endif //EATBOX_RESEP_H