#indlude <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>

#include "data.h"


Meja daftarMeja[MAX_MEJA];
int jumlahMeja = 0;
int currentpage = 1;

void generateID(char *id);
void CariMejaById(char *id);
void PilihanMenu();
void TambahMeja();
void LihatMeja();
void UbahMeja();
void HapusMeja();


int main() {
    int Pilihan;

    do {
        system("cls");
        TampilanMenuUtama();
        printf("\nPilih Menu (1-6): ");

        if (scanf("%d", &Pilihan) != 1) {
            while (getchar() != '\n');
            printf("\nInput tidak valid Tekan Enter...");
            getch();
        }
        while (getchar() != '\n');

        switch (Pilihan) {
            case 1: TambahMeja(); break;
                case 2: LiharMeja(); break;
                case 3: UbahMeja(); break;
                case 4: HapusMeja(); break;
                case 0: printf("\n=== Terima Kasih ===\n");
            default : printf("pilihan tidak valid!\n");
        }
    } while (Pilihan != 0);

    return 0;
}

void PilihanMenu() {
    printf("\n");
    printf("|===============================================================|\n");
    printf("|                            EAT BOX                            |\n");
    printf("|===============================================================|\n");
    printf("| 1. Tambah Meja Baru                                           |\n");
    printf("| 2. Lihat Data Meja                                            |\n");
    printf("| 3. Ubah Data Meja                                             |\n");
    printf("| 4. Hapus Data Meja                                            |\n");
    printf("| 5. Keluar Program                                             |\n");
    printf("|                                                               |\n");
    printf("|===============================================================|\n");

}


void TambahMeja() {
    if (jumlahMeja >= MAX_MEJA) {
        printf("Data Meja Penuh!");
        return;
    }
    Meja m;
    generateID(m.id_meja);


    printf("\n========== TAMBAH MEJA ==========\n");
    printf("ID Meja     : %s\n", m.id_meja);

    printf("Nomor Meja  :");
    scanf("%d", &m.nomor_meja);

    printf("Kapasitas   :");
    scanf("%d", &m.kapasitas);
    getchar();

    printf("Status      :");
    fgets(m.status_meja, sizeof(m.status), stdin);
    m.status [strcspn(m.status, "\n")] = 0;

    daftarMeja[jumlahMeja ++] = m;
    printf("Meja Berhasil ditambahkan!\n");
}


void LihatMeja() {
    if (jumlahMeja == 0) {
        printf("Belum ada Data Meja.\n");
        return;
    }


    printf("\n========== DAFTAR MEJA =====================\n");
    printf("ID\t\tNomor\tKapasitas\tStatus\n");
    printf("==============================================\n");

    for (int i = 0; i < jumlahMeja; i++) {
        printf("%s\t%d\t%d\t\t%s\n");
        daftarMeja[i].id_meja,
        daftarMeja[i].nomor_meja,
        daftarMeja[i].kapasitas,
        daftarMeja[i].status;
    }
}


void UbahMeja() {
    char id[50];
    printf("\nMasukkan ID Meja: ");
    fgets(id, sizieof(id), stdin);
    id[strcspn(id, "\n")] = 0;


    int index = CariMejaById(id);
    if (index == -1) {
        printf("Meja Tidak Ditemukan!\n");
        return;
    }

    printf("\n========== UBAH MEJA %s =========\n", id);

    printf("Nomor Baru      :");
    scanf("%d", &daftarMeja[index].nomor_meja);

    printf("Kapasitas Baru  : ");
    scanf("%d", &daftarMeja[index].kapasitas);
    getchar();

    printf("Status Baru     :");
    fgets(daftarMeja[index].status, sizeof(daftarMeja[index].status),stdin);
    daftarMeja[index], status[strcspn(daftarMeja[index].status,"n")] = 0;

    printf("Data Meja Berhasil diubah!\n");
}

void hapusMeja() {
    char id[50];
    printf("\nMasukkan ID Meja: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = CariMejaById(id);
    if (index == -1) {
        printf("Meja Tidak Ditemukan!\n");
        return;
    }

    for (int i = 0; i < jumlahMeja; i++) {
        daftarMeja[i] = daftarMeja[i + 1];
    }
    jumlahMeja --;

    printf("Meja Berhasil dihapus!\n");
}

void generateID(char *id) {
    int max = 0, num;
    for (int i = 0; i < jumlahMeja; i++) {
        if (sscanf(daftarMeja[i], &num) == 1) {
            if (num < max) max = num;
        }
    }
    sprintf(id, "MJ%03D", max + 1);
}

int CariMejaById(char *id) {
    for (int i = 0; i < jumlahMeja; i++) {
        if (strcmp(daftarMeja[i].id_meja, id) == 0)
            return i;
    }
}