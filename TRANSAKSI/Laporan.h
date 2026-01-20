#ifndef LAPORAN_H
#define LAPORAN_H

#include "pesanan.h"
#include "../function.h"
#include "../data.h"
#include "../MASTER/meja.h"

void mainLaporan() {
    int fBulan = 0, fTahun = 0;
    char cariStatus[50] = "";
    int modeUrut = 0;

    while (1) {
        clearArea(27, 9, consoleW() - 27, consoleH() - 9);

        Pesanan list[500];
        int count = 0;
        double grandTotal = 0;

        FILE *f = fopen("../FILE/pesanan.dat", "rb");
        if (f) {
            Pesanan p;
            while (fread(&p, sizeof(Pesanan), 1, f)) {

                if (fBulan && p.tanggal.bulan != fBulan) continue;
                if (fTahun && p.tanggal.tahun != fTahun) continue;

                if (cariStatus[0]) {
                    char idTmp[50], cariTmp[50];
                    strcpy(idTmp, p.id_pesan);
                    strcpy(cariTmp, cariStatus);
                    if (!strstr(strupr(idTmp), strupr(cariTmp)))
                        continue;
                }

                list[count++] = p;
            }
            fclose(f);
        }

        if (modeUrut)
            urutkanData(list, count, modeUrut);

        gotoxy(left, top - 1);
        printf("=== LAPORAN TRANSAKSI ===");

        gotoxy(left, top);
        printf("Cari: [%s] | Filter: [%02d/%d] | Urutan: [%s]",
               cariStatus[0] ? cariStatus : "SEMUA",
               fBulan, fTahun,
               modeUrut == 0 ? "DEFAULT" :
               modeUrut == 1 ? "TERLAMA" : "TERBARU");

        int y = top + 2;
        gotoxy(left, y++);
        printf("| No | Meja | Total | Status | Tanggal |");

        gotoxy(left, y++);
        printf("----------------------------------------");

        for (int i = 0; i < count; i++, y++) {
            gotoxy(left, y);
            printf("| %-2d | %-4d | %-7.0f | %-6s | %02d/%02d/%d |",
                   i + 1,
                   list[i].no_meja,
                   list[i].total,
                   list[i].status,
                   list[i].tanggal.tanggal,
                   list[i].tanggal.bulan,
                   list[i].tanggal.tahun);

            grandTotal += list[i].total;
        }

        gotoxy(left, y + 1);
        printf("----------------------------------------");

        gotoxy(left, y + 2);
        printf("TOTAL OMSET: Rp %.0f", grandTotal);

        if (getch() == 27)
            break;
    }
}

#endif
