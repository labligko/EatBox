#ifndef EATBOX_STAFF_H
#define EATBOX_STAFF_H

#include "../CRUD/read.h"
#include "../CRUD/delete.h"
#include "../CRUD/update.h"
#include "../CRUD/create.h"

void showMenu(char nama[50]);
void showBahan(char nama[50]);
void staff(char nama[50]);

void showMenu(char nama[50])
{
    system("cls");
    applyColors();

    appname(43, 1);
    garisx(0,8);
    garisy(25,8);

    printf("DATA MENU");

    int left = 28, right = 131, top = 11, bot = 34;

    frame(left, top, right, bot);

    for (int y = top; y < bot-1; y++) {
        gotoxy(left+8, y+1);  printf("│");
        gotoxy(left+25, y+1); printf("│");
        gotoxy(left+42, y+1); printf("│");
        gotoxy(left+58, y+1); printf("│");
        gotoxy(left+78, y+1); printf("│");
        gotoxy(left+88, y+1); printf("│");
    }
    gotoxy(left, top); printf("┌"); gotoxy(right,top); printf("┐");
    gotoxy(left, bot); printf("└"); gotoxy(right,bot); printf("┘");

    int yhead = top + 1;
    gotoxy(left+2, yhead);  printf("Id");
    gotoxy(left+10, yhead); printf("Nama Karyawan");
    gotoxy(left+27, yhead); printf("No. telp");
    gotoxy(left+44, yhead); printf("Email");
    gotoxy(left+60, yhead); printf("Alamat");
    gotoxy(left+80, yhead); printf("Posisi");
    gotoxy(left+90, yhead); printf("Status");

    for (int x = left+1; x < right; x++) {
        gotoxy(x, yhead+1); printf("─");
    }

    // Panggil fungsi read dan tampung total datanya
    int totalData = dataMenu(left, yhead + 2, currentPage);

    // Hitung Maksimal Halaman (Rumus: (Total-1) / 20 + 1)
    int maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

    // Validasi agar page tidak error saat data dihapus habis
    if (currentPage > maxPage) currentPage = maxPage;
    if (currentPage < 1) currentPage = 1;

    // Tampilkan Info Halaman di bawah tabel
    gotoxy(left+1, bot+1);
    printf("Halaman: %d / %d (Total: %d)   [<] Sebelumnya  [>] Selanjutnya", currentPage, maxPage, totalData);


    // array menu
    char *menuSup[] = {
        " Data Karyawan",
        " Tambah Karyawan",
        " Ubah Karyawan",
        " Hapus Karyawan",
        " Kembali"
    };

    // Tampilan Kiri
    gotoxy(1,10); printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕] Pilih Menu");

    // Panggil menuSelect dengan jumlah index yang dinamis
    int pilih = menuSelect(1,12, menuSup, 5);

    if (pilih == -1)
    {
        if (currentPage > 1)
        {
            currentPage--;
        }
        supadm(nama);
    }
    else if (pilih == -2)
    {
        if (currentPage < maxPage)
        {
            currentPage++;
        }
        supadm(nama);
    }
    else if (pilih == 0)
    {
        currentPage = 1;
        staff(nama);
    }
    else if (pilih == 1) showMenu(nama);
    else if (pilih == 2) showBahan(nama);
}
void showBahan(char nama[50])
{

}

void staff(char nama[50])
{
    while(1) {
        system("cls");
        applyColors();

        appname(43, 1);
        garisx(0,8);
        garisy(25,8);

        int left = 28, right = 131, top = 11, bot = 34;
        frame(left, top, right, bot);

        gotoxy(left + 5, top + 2);
        printf("DASHBOARD STAFF");
        gotoxy(left + 5, top + 3);
        for(int i=0; i<95; i++) printf("─");

        int centerX = left + (right - left) / 2;
        gotoxy(centerX - 15, top + 6);
        printf("Selamat Datang, %s!", cutname(nama));
        gotoxy(centerX - 20, top + 7);
        printf("Silakan pilih menu di samping untuk bekerja.");

        int box1_x = left + 15;
        int box_y = top + 10;
        frame(box1_x, box_y, box1_x + 30, box_y + 6); // Gambar kotak kecil
        gotoxy(box1_x + 2, box_y + 1); printf("STATISTIK MENU");
        gotoxy(box1_x + 2, box_y + 3); printf("Total Menu Tersedia");

        int box2_x = box1_x + 40;
        frame(box2_x, box_y, box2_x + 30, box_y + 6); // Gambar kotak kecil
        gotoxy(box2_x + 2, box_y + 1); printf("STATUS GUDANG");
        gotoxy(box2_x + 2, box_y + 3); printf("Stok Bahan Baku");

        gotoxy(left + 2, bot - 2);printf(" Role: Staff");

        char *menuSup[] = {
            " Kelola Menu",
            " Kelola Bahan",
            " Keluar"
        };

        gotoxy(1,10); printf("Halo, %s", cutname(nama));
        gotoxy(1,20); printf(" [↕] Pilih Menu");

        int pilih = menuSelect(1,12, menuSup, 3);

        if (pilih == 0) {
            showMenu(nama);
        }
        else if (pilih == 1) {
            showBahan(nama);
        }
        else if (pilih == 2) {
            return;
        }
    }
}

#endif //EATBOX_STAFF_H