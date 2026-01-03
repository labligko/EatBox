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
        int parsed = sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               list[totalData].id, list[totalData].username, list[totalData].password,
               list[totalData].nama, list[totalData].telp, list[totalData].email,
               list[totalData].role, list[totalData].alamat, &list[totalData].status);
        if (parsed < 9) continue;
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
        gotoxy(left+6, y);  printf("%-18.18s", cutname(list[i].username));//siapin 18 kolom, maksimal cek 18
        gotoxy(left+20, y); printf("%-15.15s", cutname(list[i].nama));
        gotoxy(left+36, y); printf("%-13.13s", list[i].telp);
        gotoxy(left+50, y); printf("%-15.15s", list[i].email);
        gotoxy(left+66, y); printf("%-17.17s", list[i].alamat);
        gotoxy(left+84, y); printf("%-8.8s", list[i].role);
        gotoxy(left+93, y); printf("%s", stat);

        resetColor(); // Balikin warna normal jika tadi diubah
        printedCount++;
    }
    return totalData; // Kembalikan jumlah total data agar supadm tau max page nya
}

//MEJA
extern Meja daftarMeja[50];
extern int totalMeja = 0;
void loadMeja() {
    FILE *f = fopen("../FILE/meja.dat", "rb");
    if (!f) return;

    totalMeja = 0;
    char buffer[255];
    while(fgets(buffer, sizeof(buffer), f)) {
        if(totalMeja >= 50) break;

        // Parsing sesuai format kamu
        if(sscanf(buffer, "%[^|]|%d|%d|%d|%d",
           daftarMeja[totalMeja].id_meja,
           &daftarMeja[totalMeja].nomor_meja,
           &daftarMeja[totalMeja].kapasitas,
           &daftarMeja[totalMeja].keterangan,
           &daftarMeja[totalMeja].status) == 5) // Pastikan return 5
        {
            totalMeja++;
        }
    }
    fclose(f);
}
void saveMeja() {
    FILE *f = fopen("../FILE/meja.dat", "wb");
    if (!f) return;

    for(int i=0; i<totalMeja; i++) {
        fprintf(f, "%s|%d|%d|%d|%d\n",
            daftarMeja[i].id_meja,
            daftarMeja[i].nomor_meja,
            daftarMeja[i].kapasitas,
            daftarMeja[i].keterangan,
            daftarMeja[i].status);
    }
    fclose(f);
}
void generateIDMeja(char *id) {
    int max = 0, num;
    for (int i = 0; i < totalMeja; i++) {
        if (sscanf(daftarMeja[i].id_meja, "MJ%d", &num) == 1) {
            if (num > max) max = num;
        }
    }
    sprintf(id, "MJ%03d", max + 1);
}
int cariMejaNorut(int noUrut) {
    int idx = noUrut - 1;
    if (idx < 0 || idx >= totalMeja) return -1;
    return idx;
}


//Bagian MENU
#define MAX_MENU 100
#define FILENAME "../FILE/menu.dat"
Menu daftarMenu[MAX_MENU];
int jumlahMenu = 0;

//membaca data menu ke file
void loadMenu() {
    FILE *file = fopen(FILENAME, "rb");

    if (file == NULL) {
        gotoxy(30, 14); printf("Belum terdia, membuat file baru.\n");
        return;
    }

    jumlahMenu = 0;
    char buffer[512];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%9[^|]|%19[^|]|%99[^|]|%lf|%199[^|]|%d",
           daftarMenu[jumlahMenu].id_menu,
           daftarMenu[jumlahMenu].kategori,
           daftarMenu[jumlahMenu].nama_menu,
           &daftarMenu[jumlahMenu].harga,
           daftarMenu[jumlahMenu].deskripsi,
           &daftarMenu[jumlahMenu].status) == 6)
        {
            jumlahMenu++;
            if (jumlahMenu >= MAX_MENU) break;
        }
    }

    fclose(file);
}
//tambahan buat penyesuaian
int dataMenu(int left, int startY, int page)
{
    if (jumlahMenu == 0) loadMenu();

    int limit = 20; // maksimal yang di tampilkan
    int startIndex = (page - 1) * limit;
    int printedCount = 0;

    for (int i = startIndex; i < jumlahMenu; i++)
    {
        if (printedCount >= limit) break;

        // Potong deskripsi biar gak kepanjangan
        char desc_short[24];
        if (strlen(daftarMenu[i].deskripsi) > 23) {
            strncpy(desc_short, daftarMenu[i].deskripsi, 20);
            strcat(desc_short, "...");
        } else {
            strcpy(desc_short, daftarMenu[i].deskripsi);
        }

        int y = startY + printedCount;

        // Cetak pakai gotoxy (Sesuaikan koordinat X dengan showMenu kamu)
        gotoxy(left+2, y);  printf("%s", daftarMenu[i].id_menu);
        gotoxy(left+10, y); printf("%-15.15s", daftarMenu[i].nama_menu); // Nama Menu
        gotoxy(left+27, y); printf("%-15.15s", daftarMenu[i].kategori);  // Kategori
        gotoxy(left+44, y); printf("Rp %-10.0lf", daftarMenu[i].harga);   // Harga
        gotoxy(left+60, y); printf("%-20.20s", desc_short);              // Deskripsi
        gotoxy(left+85, y); printf("%s", (daftarMenu[i].status == 1 ? "Tersedia" : "Habis")); // Status

        printedCount++;
    }
    return jumlahMenu; // Kembalikan total data untuk hitung paging
}
#endif //EATBOX_READ_H
