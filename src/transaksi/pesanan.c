#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data.h"
#include "../../include/function.h"
#include "../../include/master/meja.h"
#include "../../include/master/menu.h"
#include "../../include/transaksi/pembayaran.h"
#include "../../include/transaksi/pesanan.h"

#include <conio.h>

char namaKasir[50];
char listPesanHariIni[100][15];
int totalPesanHariIni;

/* =====================================================
   UTIL
===================================================== */
void autoIDPesan(char *out) {
    FILE *f = fopen(FILE_PESANAN, "rb");
    Pesanan p;
    int last = 0;

    if (f) {
        while (fread(&p, sizeof(Pesanan), 1, f))
            sscanf(p.id_pesan, "ORD%d", &last);
        fclose(f);
    }
    sprintf(out, "ORD%03d", last + 1);
}
int findMejaByNomor(int nomor) {
    for (int i = 0; i < totalMeja; i++)
        if (daftarMeja[i].status == 1 &&
            daftarMeja[i].nomor_meja == nomor)
            return i;
    return -1;
}
void setMeja(const char *id, int ket)
{
    FILE *f = fopen(FILE_MEJA, "rb+");
    if (!f) return;

    Meja m;
    while (fread(&m, sizeof(Meja), 1, f))
    {
        if (strcmp(m.id_meja, id) == 0)
        {
            m.keterangan = ket;
            fseek(f, -sizeof(Meja), SEEK_CUR);
            fwrite(&m, sizeof(Meja), 1, f);
            fflush(f);
            break;
        }
    }

    fclose(f);
}
void resetMejaJikaBedaHari()
{
    FILE *f = fopen(FILE_PESANAN, "rb");
    if (!f) return;

    Pesanan p;
    while (fread(&p, sizeof(Pesanan), 1, f))
    {
        if (p.no_meja > 0 && !hariIni(p.tanggal))
        {
            // meja masih terikat pesanan lama
            if (strcmp(p.id_meja, "-") != 0)
                setMeja(p.id_meja, 1); // KOSONG
        }
    }
    fclose(f);
}

/* =====================================================
   UI MINI (TAB)
===================================================== */
void showMiniMeja(int page) {
    clearArea(105, top+1, 26, 34);
    loadMeja();

    int itemsPerPage = 20;
    int start = (page - 1) * itemsPerPage;
    int shown = 0;

    int y = top + 1;

    frame(105, y++, 131, 35);
    gotoxy(107, y++); printf("DAFTAR MEJA");
    gotoxy(107, y++); printf("No Meja    Status");
    gotoxy(107, 36);  printf("[<] Prev  [>] Next");

    int index = 0;
    for (int i = 0; i < totalMeja; i++)
    {
        if (!daftarMeja[i].status) continue;

        if (index < start) {
            index++;
            continue;
        }

        if (shown >= itemsPerPage) break;

        gotoxy(110, y++);
        printf("%-5d   %s",
            daftarMeja[i].nomor_meja,
            daftarMeja[i].keterangan == 1 ? "Kosong" : "Terisi"
        );

        shown++;
        index++;
    }
}
void showMiniMenu(int page) {
    clearArea(90,top+1,42,35);
    loadMenu();
    int start = (page - 1) * 20;
    int y = top + 1;

    frame(90,y++,131,35);
    gotoxy(92, y++); printf("DAFTAR MENU");
    gotoxy(92, y++); printf("No  Nama \t\t\t Harga");
    gotoxy(92, 36); printf("[<] Prev  [>] Next");

    int count = 0;
    for (int i = start; i < hitungMenuAktif() && count < 20; i++) {
        if (daftarMenu[i].status != 1) continue;

        gotoxy(92, y++);
        printf("%-3d %-24.24s Rp %6s",
            i + 1,
            daftarMenu[i].nama_menu,
            formatHarga(daftarMenu[i].harga)
        );
        count++;
    }
}

/* =====================================================
   TAMBAH PESANAN
===================================================== */
void tambahPesan() {
    resetMejaJikaBedaHari();
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);
    char buf[20];
    int showSide = 0;
    int page = 1;

    Pesanan p;
    autoIDPesan(p.id_pesan);
    strcpy(p.id_akun, currentKasirID);
    strcpy(p.status, "BATAL");
    p.total = 0;
    p.tanggal = now();
    gotoxy(left, top); printf("[ESC] Batal   [ENTER] Lanjut");

    while (1) {
        showMiniMeja(page);
        int maxPageMeja = (hitungMejaAktif() + 20 - 1) / 20;
        clearinput(left, top + 1, 50);
        gotoxy(left, top + 1);
        printf("No Meja (0=Take Away) : ");
        showcurs();

        int res = inputField(buf);

        if (res == 0) return ;          // ESC
        if (res == -1 && page > 1) page--;
        if (res == -2 && page < maxPageMeja) page++;
        if (res == 1)
        {
            if (buf[0] == '\0') continue; // ENTER tapi kosong → ulang input

            if (!onlyNum(buf)) continue; // ada karakter tapi bukan angka

            int nomor = atoi(buf);
            if (nomor == 0) {
                p.no_meja = 0;
                strcpy(p.id_meja, "-");
                break;
            }

            int msgY = top + 2;
            int idx = findMejaByNomor(nomor);
            if (idx == -1) {
                clearinput(left, msgY, 40);
                gotoxy(left, msgY); printf("Meja tidak ditemukan!");
                continue;
            }
            if (daftarMeja[idx].keterangan != 1) {
                clearinput(left, msgY, 40);
                gotoxy(left, msgY); printf("Meja sedang terisi!");
                continue;
            }

            clearinput(left, msgY, 40);
            p.no_meja = daftarMeja[idx].nomor_meja;
            strcpy(p.id_meja, daftarMeja[idx].id_meja);
            break;
        }
    }
    clearArea(105,top+1,26,34);

    FILE *fp = fopen(FILE_PESANAN, "ab");
    fwrite(&p, sizeof(Pesanan), 1, fp);
    fclose(fp);

    if (p.no_meja > 0) {
        setMeja(p.id_meja, 2); // TERISI
        loadMeja();
    }

    /* ===== INPUT MENU ===== */
    page = 1;
    while (1) {
        clearArea(left, top+3, clearW-left, clearH);
        DetailPesanan d;
        char buf[10];
        int showSide = 0;
        int msgY = top + 4;
        int maxPage = (hitungMenuAktif() + 20 - 1) / 20;

        strcpy(d.id_pesan, p.id_pesan);

        showMiniMenu(page);
        clearinput(left, top + 3, 50);
        gotoxy(left, top + 3);
        printf("No Menu : ");
        showcurs();

        int res = inputField(buf);

        if (res == 0) return;   // ESC batal pesanan
        if (res == -1 && page > 1) page--;
        if (res == -2 && page < maxPage) page++;

        if (res == 1) {
            clearinput(left, msgY, 40);

            if (buf[0] == '\0') {
                gotoxy(left, msgY);
                printf("Menu tidak boleh kosong!");
                continue;
            }

            if (!onlyNum(buf)) {
                gotoxy(left, msgY);
                printf("Input harus angka!");
                continue;
            }

            int idx = atoi(buf) - 1 + (page - 1) * 20;
            if (idx < 0 || idx >= hitungMenuAktif()) {
                gotoxy(left, msgY);
                printf("Menu tidak ditemukan!");
                continue;
            }

            strcpy(d.id_menu, daftarMenu[idx].id_menu);

            gotoxy(left, top + 4);
            printf("Jumlah : ");
            inputtext(buf);
            if (!onlyNum(buf)) continue;

            d.jumlah = atoi(buf);
            double harga = daftarMenu[idx].harga;
            d.subtotal = d.jumlah * harga;
            p.total += d.subtotal;

            FILE *fd = fopen(FILE_DETAIL, "ab");
            fwrite(&d, sizeof(DetailPesanan), 1, fd);
            fclose(fd);

            int lanjut = popupConfirm("Apakah ingin menambah pesanan?", "Ya", "Tidak");
            if (lanjut == 1) continue;   // balik ke input No Menu

            break;      // lanjut ke pembayaran
        }
    }
    clearArea(110, top+1, 20, jumlahMeja+2);
    DetailPesanan d;

    /* UPDATE TOTAL */
    FILE *fr = fopen(FILE_PESANAN , "rb+");
    Pesanan tmp;
    while (fread(&tmp, sizeof(Pesanan), 1, fr)) {
        if (strcmp(tmp.id_pesan, p.id_pesan) == 0) {
            tmp.total = p.total;
            fseek(fr, -sizeof(Pesanan), SEEK_CUR);
            fwrite(&tmp, sizeof(Pesanan), 1, fr);
            break;
        }
    }

    fclose(fr);

    showbayar(p.id_pesan, namaKasir, p.total);
}

/* =====================================================
   SELESAI PESANAN
===================================================== */
void selesaiPesan()
{
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

    if (targetNo <= 0 || targetNo > totalPesanHariIni) {
        gotoxy(left, top+2);
        printf("Nomor tidak valid!");
        getch();
        return;
    }

    // 🔥 AMBIL ID PESANAN BERDASARKAN URUTAN NEWEST
    char targetID[15];
    strcpy(targetID, listPesanHariIni[targetNo - 1]);

    FILE *f = fopen(FILE_PESANAN, "rb+");
    if (!f) return;

    Pesanan p;
    while (fread(&p, sizeof(Pesanan), 1, f))
    {
        if (strcmp(p.id_pesan, targetID) != 0) continue;

        if (strstr(p.status, "MENUNGGU PEMBAYARAN") ||
            strstr(p.status, "BATAL"))
            strcpy(p.status, "BATAL");
        else
            strcpy(p.status, "PESANAN SELESAI");

        fseek(f, -sizeof(Pesanan), SEEK_CUR);
        fwrite(&p, sizeof(Pesanan), 1, f);

        if (strcmp(p.id_meja, "-") != 0)
            setMeja(p.id_meja, 1); // KOSONG

        break;
    }

    fclose(f);
}

int lihatPesan(int page)
{
    FILE* f = fopen(FILE_PESANAN, "rb");
    if (!f) return 0;

    Pesanan list[500];
    Pesanan p;
    int total = 0;
    char jam[10];

    totalPesanHariIni = 0;

    // 1️⃣ LOAD SEMUA PESANAN HARI INI
    while (fread(&p, sizeof(Pesanan), 1, f))
    {
        if (!hariIni(p.tanggal)) continue;
        list[total++] = p;
    }
    fclose(f);

    int itemsPerPage = 20;
    int start = (page - 1) * itemsPerPage;
    int end = start + itemsPerPage;

    int y = top + 3;

    // 2️⃣ RENDER DARI BELAKANG (NEWEST)
    for (int i = total - 1 - start; i >= 0 && i >= total - end; i--)
    {
        formatJam(list[i].tanggal, jam);
        getNamaKasir(list[i].id_akun, namaKasir);

        strcpy(listPesanHariIni[totalPesanHariIni], list[i].id_pesan);
        totalPesanHariIni++;

        gotoxy(left + 2, y); printf("%d", totalPesanHariIni);
        gotoxy(left + 6, y); printf("%s", namaKasir);
        gotoxy(left + 20, y); printf("%d", list[i].no_meja);
        gotoxy(left + 36, y); printf("%.0f", list[i].total);
        gotoxy(left + 50, y); printf("%s", list[i].status);
        gotoxy(left + 66, y); printf("%s", jam);
        y++;
    }

    return total;
}

int loadPesananHariIni()
{
    FILE* f = fopen(FILE_PESANAN, "rb");
    if (!f) return 0;

    Pesanan p;
    int total = 0;

    while (fread(&p, sizeof(Pesanan), 1, f))
    {
        if (!hariIni(p.tanggal)) continue;
        strcpy(listPesanHariIni[total], p.id_pesan);
        total++;
    }

    fclose(f);
    return total;
}