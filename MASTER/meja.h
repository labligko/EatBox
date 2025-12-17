#ifndef EATBOX_MEJA_H
#define EATBOX_MEJA_H

#include "../data.h"
#include "../CRUD/read.h"
#include "../function.h"
#include <stdio.h>
#include <string.h>

Meja daftarMeja[50];
int jumlahMeja = 0;
int currentpage = 1;

void generateIDMeja(char *id);
void cariMejaByID(char *id);

void PilihanMenu();
void tambahMeja();
void lihatMeja();
void ubahMeja();
void hapusMeja();

void tambahMeja() {
    Meja m;
    char buffer[20];
    int left = 30, top = 11, right = 80, bot = 25;

    generateIDMeja(m.id_meja);
    m.status = 1;

    while(1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        frame(left, top, right, bot);

        gotoxy(1, 10); printf("TAMBAH MEJA BARU    ");
        gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Lanjut");

        int y = top + 2;
        gotoxy(left + 2, y); printf("ID Meja    : %s", m.id_meja);
        y+=2; gotoxy(left + 2, y); printf("Nomor Meja : ");
        y+=2; gotoxy(left + 2, y); printf("Kapasitas  : ");
        y+=2; gotoxy(left + 2, y); printf("Status     : Kosong (Default)");

        // INPUT NOMOR
        do {
            clearinput(left+15, top+4, 10); gotoxy(left+15, top+4); showcurs();
            if(inputtext(buffer) == 0) return;
            if(onlyNum(buffer) && strlen(buffer) > 0) {
                m.nomor_meja = atoi(buffer); break;
            }
        } while(1);

        // INPUT KAPASITAS
        do {
            clearinput(left+15, top+6, 10); gotoxy(left+15, top+6); showcurs();
            if(inputtext(buffer) == 0) return;
            if(onlyNum(buffer) && strlen(buffer) > 0) {
                m.kapasitas = atoi(buffer); break;
            }
        } while(1);

        // SIMPAN
        if(popupConfirm("Simpan Meja Ini?")) {
            daftarMeja[totalMeja] = m;
            totalMeja++;
            saveMeja();
            popupAlert("Meja Berhasil Ditambahkan!");
            return;
        }
    }
}

/* ================= READ ================= */
void lihatMeja() {
    if (jumlahMeja == 0) {
        printf("Belum ada data meja.\n");
        return;
    }

    printf("\n=== DAFTAR MEJA ===\n");
    printf("ID\tNomor\tKapasitas\tStatus\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < jumlahMeja; i++) {
        printf("%s\t%d\t%d\t\t%s\n",
               daftarMeja[i].id_meja,
               daftarMeja[i].nomor_meja,
               daftarMeja[i].kapasitas,
               daftarMeja[i].status);
    }
}

/* ================= UPDATE ================= */
void ubahMeja() {
    char idTarget[10];
    char buffer[20];
    int left = 30, top = 11, right = 80, bot = 25;

    while(1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        gotoxy(1, 10); printf("UBAH DATA MEJA      ");
        gotoxy(30, 10); printf("Masukkan ID Meja : ");
        showcurs();
        if(inputtext(idTarget) == 0) return;

        int idx = cariMejaIndex(idTarget);
        if(idx == -1) { popupAlert("ID Tidak Ditemukan!"); continue; }

        Meja *m = &daftarMeja[idx];

        while(1) {
            clearArea(27, 9, clearW, clearH);
            frame(left, top, right, bot);
            gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Skip/Lanjut");

            int y = top + 2;
            gotoxy(left + 2, y); printf("ID Meja    : %s", m->id_meja);
            y+=2; gotoxy(left + 2, y); printf("Nomor Meja : %d", m->nomor_meja);
            y+=2; gotoxy(left + 2, y); printf("Kapasitas  : %d Orang", m->kapasitas);

            char statText[20];
            if(m->status==1) strcpy(statText, "Kosong");
            else if(m->status==2) strcpy(statText, "Terisi");
            else strcpy(statText, "Rusak");
            y+=2; gotoxy(left + 2, y); printf("Status     : %s (1=Ksg, 2=Isi, 0=Rusak)", statText);

            // EDIT NOMOR
            clearinput(left+15, top+4, 10); gotoxy(left+15, top+4); showcurs();
            if(inputtext(buffer) == 0) return;
            if(strlen(buffer) > 0) m->nomor_meja = atoi(buffer);
            gotoxy(left+15, top+4); printf("%d", m->nomor_meja);

            // EDIT KAPASITAS
            clearinput(left+15, top+6, 10); gotoxy(left+15, top+6); showcurs();
            if(inputtext(buffer) == 0) return;
            if(strlen(buffer) > 0) m->kapasitas = atoi(buffer);
            gotoxy(left+15, top+6); printf("%d", m->kapasitas);

            // EDIT STATUS
            clearinput(left+15, top+8, 5); gotoxy(left+15, top+8); showcurs();
            if(inputtext(buffer) == 0) return;
            if(strlen(buffer) > 0) m->status = atoi(buffer);

            if(popupConfirm("Simpan Perubahan?")) {
                saveMeja();
                popupAlert("Data Berhasil Diubah!");
                return;
            }
        }
    }
}

/* ================= DELETE ================= */
void hapusMeja() {
    char idTarget[10];
    while(1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        gotoxy(1, 10); printf("HAPUS DATA MEJA     ");
        gotoxy(30, 10); printf("Masukkan ID Meja : ");
        showcurs();
        if(inputtext(idTarget) == 0) return;

        int idx = cariMejaIndex(idTarget);
        if(idx == -1) { gotoxy(30, 12); printf("ID Tidak Ditemukan!"); Sleep(1000); continue; }

        gotoxy(30, 12); printf("Meja No %d (Kapasitas %d)", daftarMeja[idx].nomor_meja, daftarMeja[idx].kapasitas);

        if(popupConfirm("Yakin Hapus Meja Ini?")) {
            for (int i = idx; i < totalMeja - 1; i++) {
                daftarMeja[i] = daftarMeja[i + 1];
            }
            totalMeja--;
            saveMeja();
            popupAlert("Meja Berhasil Dihapus!");
            return;
        }
    }
}





#endif //EATBOX_MEJA_H