#ifndef EATBOX_KASIR_H
#define EATBOX_KASIR_H

#include <stdio.h>
#include "../function.h"
#include "../data.h"
#include "../TRANSAKSI/pembayaran.h"
#include "../TRANSAKSI/pesanan.h"

void tambahPesan();
void selesaiPesan();
int lihatPesan();
void detilPesan();

char currentKasirID[10];
char currentKasir[50] = ""; //deklarasi kasir saat ini
extern char listPesanHariIni[100][15];
extern int totalPesanHariIni;

int getIDAkunByUsername(const char *username, char *outID)
{
    FILE *f = fopen("../FILE/karyawan.dat", "r");
    if (!f) return 0;

    char line[1024];
    char f_id[20], f_user[20], f_pass[50], f_nama[50];
    char f_telp[20], f_email[50], f_role[20], f_alamat[255];
    int f_stat;

    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0;

        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               f_id, f_user, f_pass, f_nama, f_telp, f_email, f_role, f_alamat, &f_stat);

        if (strcmp(username, f_user) == 0)
        {
            strcpy(outID, f_id);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

void kasir(char nama[50])
{
    if (!getIDAkunByUsername(nama, currentKasirID))
    {
        printf("Akun tidak valid!");
        getch();
        return;
    }
    system("cls");
    applyColors();appname(43, 1);
    garisx(0,8);
    garisy(25,8); // Garis Sidebar

    strcpy(currentKasir, nama); // kasir saat ini berdasarkan login

    gotoxy(1,10); printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕] Pilih Menu");

    int currentView = 0;

    char *menuSup[] = {
        " Pesanan Baru", " Selesaikan Pesanan", " Detail Pesanan", " Keluar"
    };

    while(1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        clearinput(1,10,24);

        int totalPesan = 0;
        int maxPage = 1;
        char tgl[20];
        formatTanggal(now(), tgl); // ambil tanggal

        if (currentView == 0) {
            int left = 28, right = 131, top = 11, bot = 34;
            gotoxy(60, 10); printf("DATA PESANAN"); //HARI INI
            gotoxy(80, 10); printf("(%s)", tgl);
            frame(left, top, right, bot);

            int yhead = top + 1;
            gotoxy(left+2, yhead);  printf("No");
            gotoxy(left+6, yhead);  printf("Nama Kasir");
            gotoxy(left+20, yhead); printf("No. Meja");
            gotoxy(left+36, yhead); printf("total");
            gotoxy(left+50, yhead); printf("Status");
            gotoxy(left+66, yhead); printf("Waktu");

            for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

            lihatPesan();
        }
        else if (currentView == 1) {
            totalPesan = lihatPesan(); // Render tabel & dapatkan total data
            maxPage = (totalPesan == 0) ? 1 : (totalPesan - 1) / 20 + 1;

            // Render Footer Paging
            int bot = 34;
            gotoxy(29, bot+1);
            setRGBColor(202, 40, 44, 1);
            setRGBColor(251, 255, 199,0);
            printf("Halaman: %d / %d (Total Pesanan: %d)   [<] Prev  [>] Next", currentPage, maxPage, totalPesan);
        }

        // 4. Handle Sidebar Title (Biar balik lagi kalo abis diganti submenu)
        if(currentView == 0) { gotoxy(1,10); printf("Halo, %s", cutname(nama)); }
        else if(currentView == 1) { gotoxy(1,10); printf("DATA PESANAN"); gotoxy(72, 10); printf("(%s)", tgl); }

        // 5. Menu Select (Program Pauses Here)
        int pilih = menuSelect(1, 12, menuSup, 4);

        // 6. Logic Navigasi
        if (pilih == -1) { // Prev Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentPage > 1) currentPage--;
        }
        else if (pilih == -2) { // Next Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentPage < maxPage) currentPage++;
        }
        else if (pilih == 0) { // tambah pesanan
            tambahPesan();
            // Setelah search selesai, kembalikan tampilan
            currentView = 0; // Atau 1 terserah mau balik kemana
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 1) { // selesaikan status pesanan
            selesaiPesan(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 0; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 2)
        {
            detilPesan(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 0; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 3) { // KELUAR
            exit(0);
        }
    }
}

void tampilkanDeskripsiPesananByNo(int noUrut)
{
    if (noUrut < 1 || noUrut > totalPesanHariIni) {
        gotoxy(30, 36);
        printf("Nomor tidak valid!");
        return;
    }

    char idPesan[15];
    strcpy(idPesan, listPesanHariIni[noUrut - 1]);

    tampilDetailPesanan(idPesan, namaKasir, 30, 12);
}

void detilPesan()
{
    lihatPesan();

    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    char buf[10];
    int targetNo;

    gotoxy(left, top); printf("[ESC] Batal   [ENTER] Lanjut");
    gotoxy(left, top+1);
    printf("No Pesanan: ");
    inputtext(buf);

    if (!onlyNum(buf)) return;
    targetNo = atoi(buf);
    if (targetNo <= 0) return;

    tampilkanDeskripsiPesananByNo(targetNo);
    getch();
}

#endif //EATBOX_KASIR_H