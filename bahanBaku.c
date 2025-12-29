#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX 50
#define FILE_BAHAN "bahan.dat"


Bahan bahan[MAX];
int jumlah = 0;

void gotoxy(int x, int y);
void drawBox(int x, int y, int w, int h);

void loadData();
void saveData();

void Menu();
void Tampil();
void Tambah();
void Ubah();
void Hapus();
void Detail();

int cariIndexByID(char id[]);

int main() {
    loadData();
    Menu();
    saveData();
    return 0;
}

void gotoxy(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawBox(int x, int y, int w, int h) {
    for (int i = 0; i <= w; i++) {
        gotoxy(x + i, y);     printf("-");
        gotoxy(x + i, y + h); printf("-");
    }
    for (int i = 0; i <= h; i++) {
        gotoxy(x, y + i);     printf("|");
        gotoxy(x + w, y + i); printf("|");
    }
    gotoxy(x, y);         printf("+");
    gotoxy(x + w, y);     printf("+");
    gotoxy(x, y + h);     printf("+");
    gotoxy(x + w, y + h); printf("+");
}

void saveData() {
    FILE *fp = fopen(FILE_BAHAN, "wb");
    if (!fp) return;

    fwrite(&jumlah, sizeof(int), 1, fp);
    fwrite(bahan, sizeof(Bahan), jumlah, fp);

    fclose(fp);
}

void loadData() {
    FILE *fp = fopen(FILE_BAHAN, "rb");
    if (!fp) return;

    fread(&jumlah, sizeof(int), 1, fp);
    fread(bahan, sizeof(Bahan), jumlah, fp);

    fclose(fp);
}

int cariIndexByID(char id[]) {
    for (int i = 0; i < jumlah; i++){
        if (strcmp(bahan[i].id_bahan, id) == 0)
            return i;
    }
    return -1;
}

void Menu() {
    int pilih;
    do {
        system("cls");
        drawBox(2, 2, 40, 12);

        gotoxy(4, 3); printf("MENU BAHAN BAKU");
        gotoxy(4, 5); printf("1. Tambah Data");
        gotoxy(4, 6); printf("2. Ubah Data");
        gotoxy(4, 7); printf("3. Hapus Data");
        gotoxy(4, 8); printf("4. Tampil Data");
        gotoxy(4, 9); printf("5. Detail Data");
        gotoxy(4,10); printf("0. Keluar");

        gotoxy(4,11); printf("Pilih : ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: Tambah(); break;
            case 2: Ubah();   break;
            case 3: Hapus();  break;
            case 4: Tampil(); break;
            case 5: Detail(); break;
        }
    } while (pilih != 0);
}

void Tambah() {
    if (jumlah >= MAX) return;

    system("cls");
    drawBox(20, 4, 50, 14);

    gotoxy(32, 5); printf("TAMBAH BAHAN");

    gotoxy(22, 7); printf("ID Bahan     : ");
    scanf(" %[^\n]", bahan[jumlah].id_bahan);

    gotoxy(22, 8); printf("Nama Bahan   : ");
    scanf(" %[^\n]", bahan[jumlah].nama_bahan);

    gotoxy(22, 9); printf("Stok         : ");
    scanf("%d", &bahan[jumlah].stok);

    gotoxy(22,10); printf("Minimal Stok : ");
    scanf("%d", &bahan[jumlah].minimal_stok);

    gotoxy(22,11); printf("Satuan       : ");
    scanf(" %[^\n]", bahan[jumlah].satuan);

    jumlah++;
    saveData();

    gotoxy(22,13);
    printf("Data berhasil ditambahkan!");
    getchar(); getchar();
}

void Tampil() {
    system("cls");

    printf("NO | Nama | Stok | Minimal | Satuan | Status\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < jumlah; i++) {
        printf("%d | %s | %d | %d | %s | %s\n",
               bahan[i].id,
               bahan[i].nama_bahan,
               bahan[i].stok,
               bahan[i].minimal_stok,
               bahan[i].satuan,
               bahan[i].stok <= bahan[i].minimal_stok ? "MENIPIS" : "AMAN");
    }

    getchar(); getchar();
}

void Ubah() {
    char id[10];
    system("cls");

    printf("Masukkan No Bahan : ");
    scanf("%d", id);

    int idx = cariIndexByID(id);
    if (idx == -1) {
        printf("Data tidak ditemukan!");
        getchar(); getchar();
        return;
    }

    printf("Nama Baru    : ");
    scanf(" %[^\n]", bahan[idx].nama_bahan);
    printf("Minimal Baru : ");
    scanf("%d", &bahan[idx].minimal_stok);
    printf("Stok Baru    : ");
    scanf("%d", &bahan[idx].stok);
    printf("Satuan Baru  : ");
    scanf(" %[^\n]", bahan[idx].satuan);

    saveData();
}

void Hapus() {
    char id[10];
    system("cls");

    printf("Masukkan No Bahan : ");
    scanf(" %[^\n]", id);

    int idx = cariIndexByID(id);
    if (idx == -1) {
        printf("Data tidak ditemukan!");
        getchar(); getchar();
        return;
    }

    for (int i = idx; i < jumlah - 1; i++)
        bahan[i] = bahan[i + 1];

    jumlah--;
    saveData();

    printf("Data berhasil dihapus!");
    getchar(); getchar();
}

void Detail() {
    char id[10];
    system("cls");

    printf("Masukkan NO Bahan : ");
    scanf(" %[^\n]", id);

    int idx = cariIndexByID(id);
    if (idx == -1) {
        printf("Data tidak ditemukan!");
        getchar(); getchar();
        return;
    }

    drawBox(20, 4, 45, 12);
    gotoxy(30, 5); printf("DETAIL BAHAN BAKU");

    gotoxy(22, 7);  printf("No        : %s", bahan[idx].id_bahan);
    gotoxy(22, 8);  printf("Nama      : %s", bahan[idx].nama_bahan);
    gotoxy(22, 9);  printf("Stok      : %d", bahan[idx].stok);
    gotoxy(22,10);  printf("Minimal   : %d", bahan[idx].minimal_stok);
    gotoxy(22,11);  printf("Satuan    : %s", bahan[idx].satuan);
    gotoxy(22,12);  printf("Status    : %s",
        bahan[idx].stok <= bahan[idx].minimal_stok ? "MENIPIS" : "AMAN");

    gotoxy(22,14);
    printf("Tekan ENTER untuk kembali...");
    getchar(); getchar();
}

