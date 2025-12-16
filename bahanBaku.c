#include <string.h>
#include <stdio.h>
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
void ubah();
void Hapus();

int cariIndexByID(char id[]);

int main() {
    loadData();
    Menu();
    return 0;
}

void gotoxy(int x, int y) {
    COORD C = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawBox(int x,int y, int w, int h) {
    for (int i=0;i<= w;i++) {
        gotoxy(x + i,y); printf("-");
        gotoxy(x + i,y + h); printf("-");
    }
    for (int i=0;i<=w;i++) {
        gotoxy(x ,+ i);       printf("|");
        gotoxy(x + w,y + i);    printf("|");
    }
    gotoxy(x, y); printf("+");
    gotoxy(x, y);         printf("+");
    gotoxy(x + w, y);     printf("+");
    gotoxy(x, y + h);     printf("+");
    gotoxy(x + w, y + h); printf("+");
}

void saveData() {
    FILE *fp; fopen_s(&fp,FILE_BAHAN,"w");
    if (!fp) return;

    fwrite(&jumlah,sizeof(jumlah),1,fp);
    fwrite(&jumlah,sizeof(jumlah),1,fp);

    fclose(fp);
}

void loadData() {
    FILE *fp; fopen_s(&fp,FILE_BAHAN,"rb");
    if (!fp) return;

    fread(&jumlah,sizeof(jumlah),1,fp);
    fread(&jumlah,sizeof(Bahan),1,fp);
    fclose(fp);
}


void Menu() {
    int pilih;

    do {
        system("cls");
        drawBox(2,2,30,15);
        drawBox(2,2,60,15);


        gotoxy(4,4); printf("MENU BAHAN BAKU");
        gotoxy(4,6); printf("1. Tambah Data");
        gotoxy(4,7); printf("2. ubah Data");
        gotoxy(4,8); printf("3. Hapus Data");
        gotoxy(4,9); printf("4. Keluar");

        switch(pilih) {

            gotoxy(4,12); printf("Pilih Menu");
            scanf("%d",&pilih);

            case 1: Tambah(); break;
                case 2: Ubah(); break;
                case 3: Hapus(); break;
                case 4: Tampil(); break;
        }
    }while (pilih != 0);
}

void Tampil() {
    int y = 5;


    gotoxy(37,3);
    printf("DATA BAHAN");

    for (int i = 0; i  < jumlah;i++) {
        gotoxy(31,y); printf("%-8s", bahan[i].id_bahan);
        gotoxy(41,y); printf("%-18s", bahan[i].nama_bahan);
        gotoxy(61,y); printf("%-6d", bahan[i].minimal_stok);
        gotoxy(69,y); printf("%-6d", bahan[i].stok);
        gotoxy(77,y); printf("%-8s", bahan[i].satuan);

        gotoxy(88,y);
        if (bahan[i].stok <= bahan[i].minimal_stok)
            printf("MENIPIS");
        else
            printf("AMAN");

        y++;
    }
}
 void Tambah() {
    system("cls");
    drawBox(35,5,55,12);

    gotoxy(37,5); printf("TAMBAH BAHAN BAKU");

    gotoxy(37,8); printf("ID Bahan :");
    gotoxy(37,9); printf("Nama  :");
    gotoxy(37,10); printf("Minimal  :");
    gotoxy(37,11); printf("Stok :");
    gotoxy(37,12); printf("Satuan :");

    gotoxy(50,8);  scanf(" %[^\n]", bahan[jumlah].id_bahan);
    gotoxy(50,9);  scanf(" %[^\n]", bahan[jumlah].nama_bahan);
    gotoxy(50,11); scanf("%d", &bahan[jumlah].stok);
    gotoxy(50,12); scanf(" %[^\n]", bahan[jumlah].satuan);
    gotoxy(50,10); scanf("%d", &bahan[jumlah].minimal_stok);

    jumlah++;
}


void ubah() {
        char id[10];
        system("cls");

        printf("Masukkan ID Bahan: ");
        scanf("%s", id);

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
    }

void hapus() {
    char id[10];
    system("cls");

    printf("Masukkan ID Bahan : ");
    scanf("%s", id);

    int idx = cariIndexByID(id);
    if (idx == -1) {
        printf("Data tidak ditemukan!");
        getchar(); getchar();
        return;
    }

    for (int i = idx; i < jumlah - 1; i++)
        bahan[i] = bahan[i + 1];

    jumlah--;
}

int cariIndexByID(char id[]) {
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(bahan[i].id_bahan, id) == 0)
            return i;
    }
    return -1;
}
