#ifndef EATBOX_READ_H
#define EATBOX_READ_H
#include "../data.h"

// Mengembalikan total jumlah data (int)
int dataKaryawan(int left, int startY, int page)
{
    FILE *f = fopen("../FILE/karyawan.dat","rb");
    if (!f){ gotoxy(left, startY+22); printf("File tidak ditemukan!"); return 0; }

    Karyawan list[500], temp;
    char str[512], stat[20];
    int totalData = 0; // Menghitung total data di file

    // --- 1. LOAD SEMUA DATA KE ARRAY ---
    while (fgets(str, sizeof(str), f))
    {
        str[strcspn(str, "\n")] = 0;
        // Baca ke dalam index array 'totalData'
        int parsed = sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               list[totalData].id, list[totalData].username, list[totalData].password,
               list[totalData].telp, list[totalData].email, list[totalData].role,
               list[totalData].alamat, &list[totalData].status);
        if (parsed < 8) continue;
        totalData++; // Data valid bertambah
    }
    fclose(f);

    // --- 2. SORTING (AKTIF DI ATAS) ---
    // Logika: Jika status 0 ketemu status 1, tukar posisi biar 1 naik ke atas.
    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            // Jika data sekarang (0/Nonaktif) LEBIH KECIL dari data depan (1/Aktif)
            // Maka tukar posisi (Swap)
            if (list[j].status < list[j+1].status) {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }

    // --- 3. PRINT SESUAI HALAMAN ---
    int limit = 20;
    int startIndex = (page - 1) * limit; // Index awal halaman ini
    int printedCount = 0;

    for (int i = startIndex; i < totalData; i++)
    {
        if (printedCount >= limit) break; // Stop jika sudah 20 baris

        if (list[i].status == 1) {
            setRGBColor(251, 255, 199,0);
            strcpy(stat, "Aktif");
        } else {
            setRGBColor(210, 212, 200, 0);
            strcpy(stat, "Non-Aktif");
        }

        int y = startY + printedCount;
        int displayNo = i + 1;

        setRGBColor(202, 40, 44, 1);
        gotoxy(left+2, y);  printf("%-4d", displayNo);
        gotoxy(left+10, y); printf("%-15.15s", list[i].username);
        gotoxy(left+27, y); printf("%-15.15s", list[i].telp);
        gotoxy(left+44, y); printf("%-14.14s", list[i].email);
        gotoxy(left+60, y); printf("%-18.18s", list[i].alamat);
        gotoxy(left+80, y); printf("%-8.8s", list[i].role);
        gotoxy(left+90, y); printf("%s", stat);

        resetColor(); // Balikin warna normal jika tadi diubah
        printedCount++;
    }
    //
    // int printedCount = 0; // Menghitung data yang dicetak di halaman ini
    // int limit = 20; // Batas per halaman
    // int skip = (page - 1) * limit; // Jumlah data yang dilewati
    //
    // while (fgets(str,sizeof(str), f))
    // {
    //     totalData++; // Hitung setiap baris yang ada
    //
    //     // LOGIKA PAGING:
    //     // Jika data saat ini masih dibawah jumlah skip, lewati.
    //     if (totalData <= skip) continue;
    //
    //     // Jika data yang dicetak sudah mencapai 20, jangan print lagi (tapi tetap loop utk hitung totalData)
    //     if (printedCount >= limit) continue;
    //
    //     str[strcspn(str, "\n")] = 0;
    //
    //     // Cek apakah parsing berhasil membaca 9 data?
    //     int parsed = sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
    //            a.id, a.username, a.password, a.telp, a.email, a.role,
    //            a.alamat, &a.status);
    //
    //     // Jika jumlah data yang terbaca kurang dari 9 (misal cuma 7 kayak data lama), skip baris ini
    //     if (parsed < 8) {
    //         continue;
    //     }
    //
    //     if (a.status == 1) strcpy(stat,"Aktif");
    //     else strcpy(stat,"Non-Aktif");
    //
    //     int y = startY + printedCount;
    //
    //     // FORMAT TAMPILAN (%.Ns artinya potong teks jika lebih dari N karakter)
    //     gotoxy(left+2, y);
    //     printf("%s", a.id);
    //
    //     gotoxy(left+10, y);
    //     printf("%-15.15s", a.username); // Max 15 huruf
    //
    //     gotoxy(left+27, y);
    //     printf("%-15.15s", a.telp);
    //
    //     gotoxy(left+44, y);
    //     printf("%-14.14s", a.email);
    //
    //     gotoxy(left+60, y);
    //     printf("%-18.18s", a.alamat);
    //
    //     gotoxy(left+80, y);
    //     printf("%-8.8s", a.role);
    //
    //     gotoxy(left+90, y);
    //     printf("%s", stat);
    //
    //     printedCount++;
    // }
    // fclose(f);
    return totalData; // Kembalikan jumlah total data agar supadm tau max page nya
}

int dataMenu(int left, int startY, int page){}

#endif //EATBOX_READ_H