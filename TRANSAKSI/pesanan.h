#ifndef EATBOX_PESANAN_H
#define EATBOX_PESANAN_H

#include "../function.h"
#include "../data.h"
#include "../MASTER/meja.h"

int left = 30, top = 11;

extern Meja daftarMeja[50];
extern int totalMeja;
extern Menu daftarMenu[100];
extern int jumlahMenu;
char namaKasir[50];

/* =====================================================
   UTIL
===================================================== */
void autoIDPesan(char *out) {
    FILE *f = fopen("../FILE/pesanan.dat", "rb");
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
    FILE *f = fopen("../FILE/meja.dat", "r");
    FILE *tmp = fopen("../FILE/meja.tmp", "w");

    Meja m;
    char line[255];

    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%[^|]|%d|%d|%d|%d",
            m.id_meja,
            &m.nomor_meja,
            &m.kapasitas,
            &m.keterangan,
            &m.status
        );

        if (strcmp(m.id_meja, id) == 0) {
            m.keterangan = ket;
        }

        fprintf(tmp, "%s|%d|%d|%d|%d\n",
            m.id_meja,
            m.nomor_meja,
            m.kapasitas,
            m.keterangan,
            m.status
        );
    }

    fclose(f);
    fclose(tmp);

    remove("../FILE/meja.dat");
    rename("../FILE/meja.tmp", "../FILE/meja.dat");
}

/* =====================================================
   UI MINI (TAB)
===================================================== */
void showMiniMeja() {
    loadMeja();
    int y = top + 1;
    gotoxy(110, y++); printf("DAFTAR MEJA");
    gotoxy(110, y++); printf("No  Meja  Status");

    for (int i = 0; i < totalMeja; i++) {
        if (!daftarMeja[i].status) continue;
        gotoxy(110, y++);
        printf("%-3d %-4d %s",
            i + 1,
            daftarMeja[i].nomor_meja,
            daftarMeja[i].keterangan == 1 ? "Kosong" : "Terisi"
        );
    }
}

void showMiniMenu(int page) {
    loadMenu();
    int start = (page - 1) * 10;
    int y = top + 1;

    gotoxy(110, y++); printf("DAFTAR MENU");
    gotoxy(110, y++); printf("No  Nama        Harga");

    for (int i = start; i < start + 10 && i < jumlahMenu; i++)
    {
        gotoxy(110, y++);
        printf("%-3d %-10.10s %.0f",
            i + 1,
            daftarMenu[i].nama_menu,
            daftarMenu[i].harga
        );
    }
}

/* =====================================================
   TAMBAH PESANAN
===================================================== */
void tambahPesan() {
    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);
    char buf[20];
    int showSide = 0;
    int page = 1;

    Pesanan p;
    autoIDPesan(p.id_pesan);
    strcpy(p.id_akun, currentKasirID);
    strcpy(p.status, "MENUNGGU PEMBAYARAN");
    p.total = 0;
    p.tanggal = now();
    gotoxy(left, top); printf("[ESC] Batal   [ENTER] Lanjut");

    while (1) {
        showMiniMeja();
        clearinput(left, top + 1, 50);
        gotoxy(left, top + 1);
        printf("No Meja (0=Take Away) : ");
        showcurs();

        int res = inputField(buf);

        if (res == 0) return ;          // ESC
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
    clearArea(110, top+1, 20, totalMeja+2);

    FILE *fp = fopen("../FILE/pesanan.dat", "ab");
    fwrite(&p, sizeof(Pesanan), 1, fp);
    fclose(fp);

    if (p.no_meja > 0) {
        setMeja(p.id_meja, 2); // TERISI
        loadMeja();
    }

    /* ===== INPUT MENU ===== */
    page = 1;
    while (1) {
        clearArea(left, top+3, 70, clearH);
        DetailPesanan d;
        char buf[10];
        int showSide = 0;
        int msgY = top + 4;

        strcpy(d.id_pesan, p.id_pesan);

        showMiniMenu(page);
        clearinput(left, top + 3, 50);
        gotoxy(left, top + 3);
        printf("No Menu : ");
        showcurs();

        int res = inputField(buf);

        if (res == 0) return;   // ESC batal pesanan

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

            int idx = atoi(buf) - 1 + (page - 1) * 10;
            if (idx < 0 || idx >= jumlahMenu) {
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

            FILE *fd = fopen("../FILE/detail_pesanan.dat", "ab");
            fwrite(&d, sizeof(DetailPesanan), 1, fd);
            fclose(fd);

            int lanjut = popupConfirm("Apakah ingin menambah pesanan?", "Ya", "Tidak");
            if (lanjut == 1) continue;   // balik ke input No Menu

            break;      // lanjut ke pembayaran
        }
    }
    clearArea(110, top+1, 20, jumlahMeja+2);

    /* UPDATE TOTAL */
    FILE *fr = fopen("../FILE/pesanan.dat", "rb+");
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

    gotoxy(left, top);
    printf("No Pesanan: ");
    inputtext(buf);

    if (!onlyNum(buf)) return;
    targetNo = atoi(buf);
    if (targetNo <= 0) return;

    FILE *f = fopen("../FILE/pesanan.dat", "rb+");
    if (!f) return;

    Pesanan p;
    int counter = 0;

    while (fread(&p, sizeof(Pesanan), 1, f) == 1)
    {
        if (!hariIni(p.tanggal)) continue;

        counter++;

        if (counter != targetNo) continue;

        if (strstr(p.status, "MENUNGGU PEMBAYARAN") != NULL)
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

int lihatPesan()
{
    FILE* f = fopen("../FILE/pesanan.dat", "rb");
    if (!f) return 0;
    Pesanan p;
    int total = 0;
    int left = 28, top = 11;
    char jam[10];
    int x = left;
    int y = top + 3;
    while (fread(&p, sizeof(Pesanan), 1, f))
    {
        if (!hariIni(p.tanggal)) continue;
        formatJam(p.tanggal, jam); //mengambil data jam
        getNamaKasir(p.id_akun, namaKasir); //mengambil nama kasir
        gotoxy(x+2, y);
        printf("%d", total + 1);
        gotoxy(x + 6, y);
        printf("%s", namaKasir);
        gotoxy(x + 20, y);
        printf("%d", p.no_meja);
        gotoxy(x + 36, y);
        printf("%.0f", p.total);
        gotoxy(x + 50, y);
        printf("%s", p.status);
        gotoxy(x + 66, y);
        printf("%s", jam);
        total++;
        y++;
    }
    fclose(f);
    return total;
}

#endif