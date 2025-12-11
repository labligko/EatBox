#include <stdio.h>
#include <string.h>
#include "meja.h"

#define FILE_NAME "meja.dat"

// Tambah meja
void tambahMeja() {
    FILE *fp = fopen(FILE_NAME, "ab"); // append binary
    if (!fp) {
        printf("Gagal membuka file!\n");
        return;
    }

    Meja m;
    printf("ID Meja: "); scanf("%s", m.id_meja);
    printf("Nomor Meja: "); scanf("%d", &m.nomor_meja);
    printf("Kapasitas: "); scanf("%d", &m.kapasitas);
    printf("Status: "); scanf("%s", m.status);

    fwrite(&m, sizeof(Meja), 1, fp);
    fclose(fp);
    printf("Meja berhasil ditambahkan!\n");
}

// Tampilkan semua meja
void tampilkanMeja() {
    FILE *fp = fopen(FILE_NAME, "rb"); // read binary
    if (!fp) {
        printf("Belum ada data meja.\n");
        return;
    }

    Meja m;
    printf("ID\tNomor\tKapasitas\tStatus\n");
    while(fread(&m, sizeof(Meja), 1, fp)) {
        printf("%s\t%d\t%d\t\t%s\n", m.id_meja, m.nomor_meja, m.kapasitas, m.status);
    }
    fclose(fp);
}

// Update meja berdasarkan ID
void updateMeja() {
    FILE *fp = fopen(FILE_NAME, "rb+"); // read+write binary
    if (!fp) {
        printf("Belum ada data meja.\n");
        return;
    }

    char id[10];
    printf("Masukkan ID meja yang ingin diupdate: "); scanf("%s", id);
    Meja m;
    int found = 0;

    while(fread(&m, sizeof(Meja), 1, fp)) {
        if (strcmp(m.id_meja, id) == 0) {
            printf("Nomor Meja baru: "); scanf("%d", &m.nomor_meja);
            printf("Kapasitas baru: "); scanf("%d", &m.kapasitas);
            printf("Status baru: "); scanf("%s", m.status);

            fseek(fp, -sizeof(Meja), SEEK_CUR);
            fwrite(&m, sizeof(Meja), 1, fp);
            found = 1;
            printf("Meja berhasil diupdate!\n");
            break;
        }
    }

    if (!found) printf("Meja dengan ID %s tidak ditemukan!\n", id);
    fclose(fp);
}

// Hapus meja berdasarkan ID
void hapusMeja() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Gagal membuka file.\n");
        return;
    }

    char id[10];
    printf("Masukkan ID meja yang ingin dihapus: "); scanf("%s", id);
    Meja m;
    int found = 0;

    while(fread(&m, sizeof(Meja), 1, fp)) {
        if (strcmp(m.id_meja, id) != 0) {
            fwrite(&m, sizeof(Meja), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Meja berhasil dihapus.\n");
    else
        printf("Meja dengan ID %s tidak ditemukan.\n", id);
}
