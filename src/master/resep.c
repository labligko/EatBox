#include <stdio.h>

#include "../../include/data.h"
#include "../../include/function.h"
#include "../../include/master/resep.h"
#include "../../include/master/menu.h"
#include "../../include/master/bahanBaku.h"

#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
    int page = 1;
    int perPage = 15;
    loadResep();
    loadBahan();

    int totalAktif = 0;
    for (int i = 0; i < totalBahan; i++)
        if (daftarBahan[i].status == 1)
            totalAktif++;

    int maxPage = (totalAktif + perPage - 1) / perPage;

    while (1) {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        gotoxy(30,10); printf("KELOLA RESEP MENU [%s]", id_menu);
        gotoxy(30,11);printf("[ESC] Untuk tambah bahan baru");
        gotoxy(30,12); printf("Daftar Bahan:");

        int start = (page - 1) * perPage;
        int end = start + perPage;

        int y = 14;
        int no = 1;
        int tampil = 0;

        frame(28, y-1, 55, bot);
        gotoxy(30, bot + 1);printf("[<] Prev   Page %d/%d   [>] Next", page, maxPage);

        // cari bahan aktif ke-n
        for (int i = 0; i < totalBahan; i++) {
            if (daftarBahan[i].status != 1) continue;

            if (no - 1 < start) {
                no++;
                continue;
            }

            if (tampil >= perPage) break;

            gotoxy(30, y++);
            printf("%d. %s (%s)", no,
                   daftarBahan[i].nama_bahan,
                   daftarBahan[i].satuan);

            no++;
            tampil++;
        }

        gotoxy(80, 12);
        printf("Pilih No Bahan (0 = Tambah Bahan Baru): ");
        showcurs();
        int ret = inputField(buf);

        if (ret == 0) {
            // ESC → keluar / tambah bahan baru (sesuai UI lu)
            tambahBahan();
            loadBahan();
            continue;
        }

        if (ret == -1) {          // LEFT
            if (page > 1) page--;
            continue;
        }

        if (ret == -2) {          // RIGHT
            if (page < maxPage) page++;
            continue;
        }

        int pilih = atoi(buf);
        int idxBahan = getIndexByNoUrut(pilih);
        if (idxBahan == -1) continue;

        gotoxy(80, 13);
        printf("Jumlah pemakaian per 1 menu: ");
        inputField(buf);
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
        {
            popupAlert(1, "Resep berhasil ditambahkan!");
            Sleep(500);
        }
        return;
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
    FILE *fpDetail = fopen(FILE_DETAIL, "rb");
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

int cekStokMenu(const char *id_menu, int qty)
{
    loadResep();
    loadBahan();

    for (int i = 0; i < totalResep; i++)
    {
        if (strcmp(daftarResep[i].id_menu, id_menu) != 0)
            continue;

        int idx = cariBahanByID(daftarResep[i].id_bahan);
        if (idx == -1) return 0;

        int butuh = daftarResep[i].jumlah * qty;
        if (daftarBahan[idx].stok < butuh)
            return 0;
    }
    return 1;
}