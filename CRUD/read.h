#ifndef EATBOX_READ_H
#define EATBOX_READ_H
#include "../data.h"

// Mengembalikan total jumlah data (int)
int dataKaryawan(int left, int startY, int page)
{
    FILE *f = fopen("../FILE/karyawan.dat","rb");
    if (!f)
    {
        gotoxy(left, startY+22);
        printf("File tidak ditemukan!");
        return 0;
    }

    Karyawan a;
    char str[255], stat[20];
    int totalData = 0; // Menghitung total data di file
    int printedCount = 0; // Menghitung data yang dicetak di halaman ini
    int limit = 20; // Batas per halaman
    int skip = (page - 1) * limit; // Jumlah data yang dilewati

    while (fgets(str,sizeof(str), f))
    {
        totalData++; // Hitung setiap baris yang ada

        // LOGIKA PAGING:
        // Jika data saat ini masih dibawah jumlah skip, lewati.
        if (totalData <= skip) continue;

        // Jika data yang dicetak sudah mencapai 20, jangan print lagi (tapi tetap loop utk hitung totalData)
        if (printedCount >= limit) continue;

        // Parsing data
        sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d",
       a.id, a.username, a.password, a.telp, a.email, a.role,
       a.alamat, &a.status, &a.poin);

        if (a.status == 1) strcpy(stat,"Aktif");
        else strcpy(stat,"Non-Aktif");

        int y = startY + printedCount;

        // FORMAT TAMPILAN (%.Ns artinya potong teks jika lebih dari N karakter)
        gotoxy(left+2, y);
        printf("%s", a.id);

        gotoxy(left+10, y);
        printf("%-15.15s", a.username); // Max 15 huruf

        gotoxy(left+27, y);
        printf("%-15.15s", a.telp);

        gotoxy(left+44, y);
        printf("%-14.14s", a.email);

        gotoxy(left+60, y);
        printf("%-18.18s", a.alamat);

        gotoxy(left+80, y);
        printf("%-8.8s", a.role);

        gotoxy(left+90, y);
        printf("%s", stat);

        printedCount++;
    }
    fclose(f);
    return totalData; // Kembalikan jumlah total data agar supadm tau max page nya
}

#endif //EATBOX_READ_H