#include <stdio.h>

#include "../../include/data.h"
#include "../../include/function.h"
#include "../../include/master/resep.h"
#include "../../include/master/bahanBaku.h"

#include <stdlib.h>
#include <string.h>

ResepMenu daftarResep[100];
int totalResep;

void saveResep() {
    FILE *f = fopen(FILE_RESEP, "wb");
    if (!f) { totalResep = 0; return;}
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

int cekResepAda(char *id_menu, char *id_bahan)
{
    for (int i = 0; i < totalResep; i++)
        if (strcmp(daftarResep[i].id_menu, id_menu) == 0 &&
            strcmp(daftarResep[i].id_bahan, id_bahan) == 0)
            return i;
    return -1;
}
void kelolaResepMenu(char *id_menu) {
    char buf[20];
    loadResep();
    loadBahan();

    while (1) {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        gotoxy(30,10); printf("KELOLA RESEP MENU [%s]", id_menu);
        gotoxy(30,11);printf("[ESC] Untuk tambah bahan baru");
        gotoxy(30,12); printf("Daftar Bahan:");

        int y = 14;
        int no = 1;
        for (int i = 0; i < totalBahan; i++) {
            if (daftarBahan[i].status != 1) continue;
            gotoxy(30, y++);
            printf("%d. %s (%s)", no++, daftarBahan[i].nama_bahan, daftarBahan[i].satuan);
        }

        gotoxy(100, 12);
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

        gotoxy(100, 13);
        printf("Jumlah pemakaian per 1 menu: ");
        inputtext(buf);
        if (!onlyNum(buf)) continue;

        ResepMenu r;
        strcpy(r.id_menu, id_menu);
        strcpy(r.id_bahan, daftarBahan[idxBahan].id_bahan);
        r.jumlah = atoi(buf);

        int idx = cekResepAda(id_menu, daftarBahan[idxBahan].id_bahan);
        if (idx != -1) {
            daftarResep[idx].jumlah += r.jumlah; // akumulasi
        } else {
            daftarResep[totalResep++] = r;
        }
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
void kurangiStokDariPesanan(char *id_pesan)
{
    FILE *fpDetail = fopen("../file/detail_pesanan.dat", "rb");
    if (!fpDetail) return;

    loadResep();
    loadBahan();

    DetailPesanan d;

    while (fread(&d, sizeof(DetailPesanan), 1, fpDetail))
    {
        if (strcmp(d.id_pesan, id_pesan) != 0)
            continue;

        // cari semua resep untuk menu ini
        for (int i = 0; i < totalResep; i++)
        {
            if (strcmp(daftarResep[i].id_menu, d.id_menu) == 0)
            {
                int idxBahan = cariBahanByID(daftarResep[i].id_bahan);
                if (idxBahan != -1)
                {
                    int totalPakai =
                        daftarResep[i].jumlah * d.jumlah;

                    daftarBahan[idxBahan].stok -= totalPakai;

                    if (daftarBahan[idxBahan].stok < 0)
                        daftarBahan[idxBahan].stok = 0;
                }
            }
        }
    }

    fclose(fpDetail);
    saveBahan();
}