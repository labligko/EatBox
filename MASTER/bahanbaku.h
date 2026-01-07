#ifndef EATBOX_BAHANBAKU_H
#define EATBOX_BAHANBAKU_H

#include "../data.h"
#define FILE_BAHAN "../FILE/bahan.dat"
void drawBox(int x, int y, int w, int h);

void loadBahan();
void saveData();

void Bahan();
void Tampil();
void Tambah();
void Ubah();
void Hapus();

// ================= FILE HANDLING =================
void saveBahan() {
    FILE *f = fopen(FILE_BAHAN, "wb");
    if (!f) return;

    fwrite(&totalBahan, sizeof(int), 1, f);
    fwrite(daftarBahan, sizeof(BahanBaku), totalBahan, f);
    fclose(f);
}
void loadBahan() {
    FILE *fp; fopen_s(&fp,FILE_BAHAN,"rb");
    if (!fp) return;

    fread(&totalBahan,sizeof(int),1,fp);
    fread(daftarBahan,sizeof(BahanBaku),totalBahan,fp);
    fclose(fp);
}

//TAMBAHAN
void generateIDBahan(char *output) {
    int max = 0, num;
    for (int i = 0; i < totalBahan; i++) {
        if (sscanf(daftarBahan[i].id_bahan, "BB%d", &num) == 1) {
            if (num > max) max = num;
        }
    }
    sprintf(output, "BB%03d", max + 1);
}
int getIndexByNoUrut(int no) {
    int count = 0;
    for (int i = 0; i < totalBahan; i++) {
        if (daftarBahan[i].status == 1) {
            count++;
            if (count == no) return i;
        }
    }
    return -1;
}

// ================= TABEL =================
int renderTabelBahan(int left, int top, int right, int bot, int page) {
    int limit = 20; //max per page
    int start = (page - 1) * limit; //awal tiap page

    // Header Tabel
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);
    frame(left, top, right, bot);

    gotoxy(left + 2, top + 1);
    printf("%-4s %-25s %-8s %-8s %-8s %-10s",
       "No", "Nama Bahan", "Stok", "Min", "Satuan", "Status");;

    // Garis
    gotoxy(left + 1, top + 2);
    for (int k = left + 1; k < right; k++) printf("─");

    // Loop Data (Paging Logic)
    int y = top + 3;
    int shown = 0;
    int no = 0;

    // === AKTIF DULU ===
    for (int i = 0; i < totalBahan; i++) {
        if (daftarBahan[i].status != 1) continue;
        no++;
        if (no <= start) continue;
        if (shown >= limit) break;

        char status[10];
        strcpy(status,
            daftarBahan[i].stok <= daftarBahan[i].minimal_stok
            ? "MENIPIS" : "AMAN");

        gotoxy(left + 2, y++);
        printf("%-4d %-25.25s %-8d %-8d %-8s %-10s",
            no,
            daftarBahan[i].nama_bahan,
            daftarBahan[i].stok,
            daftarBahan[i].minimal_stok,
            daftarBahan[i].satuan,
            status);

        shown++;
    }

    // === HABIS DI BAWAH ===
    for (int i = 0; i < totalBahan && shown < limit; i++) {
        if (daftarBahan[i].status != 0) continue;
        no++;
        if (no <= start) continue;

        setRGBColor(210, 212, 200, 0);
        gotoxy(left + 2, y++);
        printf("%-4d %-25.25s %-8d %-8d %-8s %-10s",
            no,
            daftarBahan[i].nama_bahan,
            daftarBahan[i].stok,
            daftarBahan[i].minimal_stok,
            daftarBahan[i].satuan,
            "HABIS");

        shown++;
    }
    return totalBahan;
}


//UDAH G PAKE GINIAN LAGI

// void drawBox(int x,int y, int w, int h) {
//     for (int i=0;i<= w;i++) {
//         gotoxy(x + i,y); printf("-");
//         gotoxy(x + i,y + h); printf("-");
//     }
//     for (int i=0;i<=w;i++) {
//         gotoxy(x ,+ i);       printf("|");
//         gotoxy(x + w,y + i);    printf("|");
//     }
//     gotoxy(x, y); printf("+");
//     gotoxy(x, y);         printf("+");
//     gotoxy(x + w, y);     printf("+");
//     gotoxy(x, y + h);     printf("+");
//     gotoxy(x + w, y + h); printf("+");
// }
// void Bahan() {
//     int pilih;
//
//     do {
//         system("cls");
//         drawBox(2,2,30,15);
//         drawBox(2,2,60,15);
//
//
//         gotoxy(4,4); printf("MENU BAHAN BAKU");
//         gotoxy(4,6); printf("1. Tambah Data");
//         gotoxy(4,7); printf("2. ubah Data");
//         gotoxy(4,8); printf("3. Hapus Data");
//         gotoxy(4,9); printf("4. Keluar");
//
//         switch(pilih) {
//
//             gotoxy(4,12); printf("Pilih Menu");
//             scanf("%d",&pilih);
//
//             case 1: Tambah(); break;
//                 case 2: Ubah(); break;
//                 case 3: Hapus(); break;
//                 case 4: Tampil(); break;
//         }
//     }while (pilih != 0);
// }

// void Tampil() {
//     int y = 5;
//
//
//     gotoxy(37,3);
//     printf("DATA BAHAN");
//
//     for (int i = 0; i  < jumlah;i++) {
//         gotoxy(31,y); printf("%-8s", bahan[i].id_bahan);
//         gotoxy(41,y); printf("%-18s", bahan[i].nama_bahan);
//         gotoxy(61,y); printf("%-6d", bahan[i].minimal_stok);
//         gotoxy(69,y); printf("%-6d", bahan[i].stok);
//         gotoxy(77,y); printf("%-8s", bahan[i].satuan);
//
//         gotoxy(88,y);
//         if (bahan[i].stok <= bahan[i].minimal_stok)
//             printf("MENIPIS");
//         else
//             printf("AMAN");
//
//         y++;
//     }
// }
//  void Tambah() {
//     system("cls");
//     drawBox(35,5,55,12);
//
//     gotoxy(37,5); printf("TAMBAH BAHAN BAKU");
//
//     gotoxy(37,8); printf("ID Bahan :");
//     gotoxy(37,9); printf("Nama  :");
//     gotoxy(37,10); printf("Minimal  :");
//     gotoxy(37,11); printf("Stok :");
//     gotoxy(37,12); printf("Satuan :");
//
//     gotoxy(50,8);  scanf(" %[^\n]", bahan[jumlah].id_bahan);
//     gotoxy(50,9);  scanf(" %[^\n]", bahan[jumlah].nama_bahan);
//     gotoxy(50,11); scanf("%d", &bahan[jumlah].stok);
//     gotoxy(50,12); scanf(" %[^\n]", bahan[jumlah].satuan);
//     gotoxy(50,10); scanf("%d", &bahan[jumlah].minimal_stok);
//
//     jumlah++;
// }
void tambahBahan() {
    BahanBaku b;
    char buffer[50];
    int left = 30, top = 11, right = 90, bot = 28;
    int inputX = left + 18;

    generateIDBahan(b.id_bahan);
    b.status = 1;

    while(1) {
        // UI Setup
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        frame(left, top, right, bot);

        gotoxy(left + 20, top - 2);
        printf("\033[41m\033[93m INPUT BAHAN BAKU BARU \033[0m");
        setRGBColor(202, 40, 44, 1);
        setRGBColor(251, 255, 199,0);
        gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Lanjut");

        // Label
        int y = top + 2;
        gotoxy(left+3, y);   printf("ID Bahan     : %s", b.id_bahan);
        y+=2; gotoxy(left+3, y); printf("Nama Bahan   : ");
        y+=2; gotoxy(left+3, y); printf("Stok Awal    : ");
        y+=2; gotoxy(left+3, y); printf("Satuan       : ");
        y+=2; gotoxy(left+3, y); printf("Min. Stok    : ");

        // --- INPUT SEQUENTIAL ---

        // 1. Nama Bahan
        do {
            clearinput(inputX, top+4, 30); gotoxy(inputX, top+4); showcurs();
            if(inputtext(b.nama_bahan) == 0) return;
            if(strlen(b.nama_bahan) > 0) break;
        } while(1);

        // 2. Stok (Angka)
        do {
            clearinput(inputX, top+6, 10); gotoxy(inputX, top+6); showcurs();
            if(inputtext(buffer) == 0) return;
            if(onlyNum(buffer) && strlen(buffer) > 0) {
                b.stok = atoi(buffer); break;
            }
        } while(1);

        // 3. Satuan (Kg, Gram, Pcs, dll)
        do {
            clearinput(inputX, top+8, 15); gotoxy(inputX, top+8); showcurs();
            if(inputtext(b.satuan) == 0) return;
            if(strlen(b.satuan) > 0) break;
        } while(1);

        // 4. Minimal Stok (Alert limit)
        do {
            clearinput(inputX, top+10, 10); gotoxy(inputX, top+10); showcurs();
            if(inputtext(buffer) == 0) return;
            if(onlyNum(buffer) && strlen(buffer) > 0) {
                b.minimal_stok = atoi(buffer); break;
            }
        } while(1);

        // Simpan
        if(popupConfirm("Simpan Bahan Ini?", "Ya", "Batal")) {
            daftarBahan[totalBahan++] = b;
            saveBahan();
            popupAlert(1,"Bahan Berhasil Ditambahkan!");
            return;
        }
    }
}
// void Ubah() {
//         char id[10];
//         system("cls");
//
//         printf("Masukkan ID Bahan: ");
//         scanf("%s", id);
//
//         int idx = cariIndexByID(id);
//         if (idx == -1) {
//             printf("Data tidak ditemukan!");
//             getchar(); getchar();
//             return;
//         }
//
//         printf("Nama Baru    : ");
//         scanf(" %[^\n]", bahan[idx].nama_bahan);
//         printf("Minimal Baru : ");
//         scanf("%d", &bahan[idx].minimal_stok);
//         printf("Stok Baru    : ");
//         scanf("%d", &bahan[idx].stok);
//         printf("Satuan Baru  : ");
//         scanf(" %[^\n]", bahan[idx].satuan);
//     }
void ubahBahan() {
    // char idTarget[20];  g pake ini
    int no;
    char buffer[50];
    int left = 30, top = 11, right = 90, bot = 28;
    int inputX = left + 18;

    while(1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        gotoxy(1, 10); printf("UBAH DATA BAHAN");
        gotoxy(left, 10); printf("Masukkan No Bahan : ");
        showcurs();

        if(inputtext(buffer) == 0) return;
        no = atoi(buffer);

        int idx = getIndexByNoUrut(no);
        if(idx == -1) { popupAlert(0, "No Tidak Ditemukan!"); continue; }

        BahanBaku *b = &daftarBahan[idx];

        // UI Edit Form
        clearArea(27, 9, clearW, clearH);
        frame(left, top, right, bot);
        gotoxy(left + 20, top - 2); printf("\033[41m\033[93m UBAH DATA BAHAN \033[0m");
        setRGBColor(202, 40, 44, 1);
        setRGBColor(251, 255, 199,0);
        gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Lewati/Tetap");

        int y = top + 2;
        // Tampilkan Data Lama
        gotoxy(left+3, y);   printf("ID Bahan     : %s", b->id_bahan);
        y+=2; gotoxy(left+3, y); printf("Nama Bahan   : %s", b->nama_bahan);
        y+=2; gotoxy(left+3, y); printf("Stok Saat Ini: %d", b->stok);
        y+=2; gotoxy(left+3, y); printf("Satuan       : %s", b->satuan);
        y+=2; gotoxy(left+3, y); printf("Min. Stok    : %d", b->minimal_stok);

        // EDIT NAMA
        clearinput(inputX, top+4, 30); gotoxy(inputX, top+4);
        if(inputtext(buffer) == 0) return;
        if(strlen(buffer) > 0) strcpy(b->nama_bahan, buffer);
        gotoxy(inputX, top+4); printf("%-30s", b->nama_bahan);

        // EDIT STOK
        do {
            clearinput(inputX, top+6, 10); gotoxy(inputX, top+6);
            if(inputtext(buffer) == 0) return;
            if(strlen(buffer) == 0) break; // Skip
            if(onlyNum(buffer)) { b->stok = atoi(buffer); break; }
        } while(1);
        gotoxy(inputX, top+6); printf("%-10d", b->stok);

        // EDIT SATUAN
        clearinput(inputX, top+8, 15); gotoxy(inputX, top+8);
        if(inputtext(buffer) == 0) return;
        if(strlen(buffer) > 0) strcpy(b->satuan, buffer);
        gotoxy(inputX, top+8); printf("%-15s", b->satuan);

        // EDIT MINIMAL STOK
        do {
            clearinput(inputX, top+10, 10); gotoxy(inputX, top+10);
            if(inputtext(buffer) == 0) return;
            if(strlen(buffer) == 0) break;
            if(onlyNum(buffer)) { b->minimal_stok = atoi(buffer); break; }
        } while(1);

        if(popupConfirm("Simpan Perubahan?", "Ya", "Batal")) {
            saveBahan();
            popupAlert(1,"Data Bahan Diperbarui!");
            return;
        }
    }
}

// void hapus() {
//     char id[10];
//     system("cls");
//
//     printf("Masukkan ID Bahan : ");
//     scanf("%s", id);
//
//     int idx = cariIndexByID(id);
//     if (idx == -1) {
//         printf("Data tidak ditemukan!");
//         getchar(); getchar();
//         return;
//     }
//
//     for (int i = idx; i < jumlah - 1; i++)
//         bahan[i] = bahan[i + 1];
//
//     jumlah--;
// }
void hapusBahan() {
    // char idTarget[20]; g pake ini
    char buf[20];
    int no;
    while(1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        gotoxy(1, 10); printf("HAPUS DATA BAHAN");
        gotoxy(30, 10); printf("Masukkan No Bahan : ");
        showcurs();

        if(inputtext(buf) == 0) return;
        no = atoi(buf);

        int idx = getIndexByNoUrut(no);
        if(idx == -1) { popupAlert(0,"No Tidak Ditemukan!"); continue; }

        // Preview
        gotoxy(30, 12); printf("Bahan  : %s", daftarBahan[idx].nama_bahan);
        gotoxy(30, 13); printf("Stok   : %d %s", daftarBahan[idx].stok, daftarBahan[idx].satuan);
        gotoxy(30,14);printf("tekan ENTER untuk lanjut..."); getchar();

        if(popupConfirm("Yakin Hapus Bahan Ini?", "Ya", "Batal")) {
            daftarBahan[idx].status = 0;
            saveBahan();
            popupAlert(1,"Bahan Berhasil Dihapus!");
            return;
        }
    }
}

#endif //EATBOX_BAHANBAKU_H