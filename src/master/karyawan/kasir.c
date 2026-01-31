#include <stdio.h>

#include "../../../include/data.h"
#include "../../../include/function.h"
#include "../../../include/master/karyawan/kasir.h"

#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../../include/master/menu.h"
#include "../../../include/master/meja.h"
#include "../../../include/transaksi/pesanan.h"
#include "../../../include/transaksi/pembayaran.h"

char currentKasirID[10];
char currentKasir[50] = "";
int left = 28, right = 131, top = 11, bot = 34;

int getIDAkunByUsername(const char *username, char *outID)
{
    FILE *f = fopen(FILE_KARYAWAN, "rb");
    if (!f) return 0;

    Karyawan k;
    while (fread(&k, sizeof(Karyawan), 1, f)) {
        if (strcmp(k.username, username) == 0) {
            strcpy(outID, k.id);
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
    gotoxy(1,20); printf(" [↕]      Pilih Menu");
    gotoxy(1,21); printf(" [ENTER]  Lanjut");

    int currentView = 1;

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

        if (currentView == 1) {
            gotoxy(1,10); printf("DATA PESANAN");
            gotoxy(70,10); printf("(%s)", tgl);
            frame(left, top, right, bot);

            int yhead = top + 1;
            gotoxy(left+2, yhead); printf("No");
            gotoxy(left+6, yhead); printf("Nama Kasir");
            gotoxy(left+20, yhead); printf("No. Meja");
            gotoxy(left+36, yhead); printf("Total");
            gotoxy(left+50, yhead); printf("Status");
            gotoxy(left+66, yhead); printf("Waktu");

            for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

            totalPesan = lihatPesan(currentpage);
            maxPage = (totalPesan == 0) ? 1 : (totalPesan - 1) / 20 + 1;

            gotoxy(29, bot+1);
            setRGBColor(202, 40, 44, 1);
            setRGBColor(251, 255, 199, 0);
            printf("Halaman: %d / %d (Total Pesanan: %d)   [<] Prev  [>] Next", currentpage, maxPage, totalPesan);
        }

        // 4. Handle Sidebar Title (Biar balik lagi kalo abis diganti submenu)
        if(currentView == 0) { gotoxy(1,10); printf("Halo, %s", cutname(nama)); }
        else if(currentView == 1) { gotoxy(1,10); printf("DATA PESANAN"); gotoxy(70, 10); printf("(%s)", tgl); }

        // 5. Menu Select (Program Pauses Here)
        int pilih = menuSelect(1, 12, menuSup, 4);

        // 6. Logic Navigasi
        if (pilih == -1) { // Prev Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentpage > 1) currentpage--;
        }
        else if (pilih == -2) { // Next Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentpage < maxPage) currentpage++;
        }
        else if (pilih == 0) { // tambah pesanan
            tambahPesan();
            // Setelah search selesai, kembalikan tampilan
            currentView = 1; // Atau 1 terserah mau balik kemana
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
        }
        else if (pilih == 1) { // selesaikan status pesanan
            selesaiPesan(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 1; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
        }
        else if (pilih == 2)
        {
            detilPesan(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 1; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30);
            gotoxy(1,20); printf(" [↕]      Pilih Menu");
            gotoxy(1,21); printf(" [ENTER]  Lanjut");
        }
        else if (pilih == 3) { // KELUAR
            if (popupConfirm("Apakah anda yakin ingin keluar?", "Ya", "Tidak"))
                return;
        }
    }
}
void tampilkanDeskripsiPesananByNo(int noUrut)
{
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 12, clearW, clearH);

    if (noUrut < 1 || noUrut > totalPesanHariIni) {
        gotoxy(30, 36);
        printf("Nomor tidak valid!");
        return;
    }

    char idPesan[15];
    strcpy(idPesan, listPesanHariIni[noUrut - 1]);

    loadMenu();
    tampilDetailPesanan(idPesan, namaKasir, 30, 12);
}

void detilPesan()
{
    totalPesanHariIni = loadPesananHariIni();

    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    char buf[10];
    int targetNo;

    gotoxy(left, top); printf("[ESC] Batal   [ENTER] Lanjut");
    gotoxy(left, top+1);printf("No Pesanan: ");
    inputtext(buf);

    if (!onlyNum(buf)) return;
    targetNo = atoi(buf);
    if (targetNo <= 0) return;

    tampilkanDeskripsiPesananByNo(targetNo);
    getch();
}