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
void cariMejaByID(char *id);

void PilihanMenu();
void tambahMeja();
void lihatMeja();
void ubahMeja();
void hapusMeja();


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

void tambahMeja() {
    if (jumlahMeja >= MAX_MEJA) {
        printf("Data meja penuh!\n");
        return;
    }

    Meja m;
    generateID(m.id_meja);

    printf("\n=== TAMBAH MEJA ===\n");
    printf("ID Meja      : %s\n", m.id_meja);

    printf("Nomor Meja   : ");
    scanf("%d", &m.nomor);

    printf("Kapasitas    : ");
    scanf("%d", &m.kapasitas);
    getchar();

    printf("Status       : ");
    fgets(m.status, sizeof(m.status), stdin);
    m.status[strcspn(m.status, "\n")] = 0;

    daftarMeja[jumlahMeja++] = m;
    printf("Meja berhasil ditambahkan!\n");
}

/* ================= READ ================= */
void lihatMeja() {
    if (jumlahMeja == 0) {
        printf("Belum ada data meja.\n");
        return;
    }

    printf("\n=== DAFTAR MEJA ===\n");
    printf("ID\tNomor\tKapasitas\tStatus\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < jumlahMeja; i++) {
        printf("%s\t%d\t%d\t\t%s\n",
               daftarMeja[i].id_meja,
               daftarMeja[i].nomor,
               daftarMeja[i].kapasitas,
               daftarMeja[i].status);
    }
}

/* ================= UPDATE ================= */
void ubahMeja() {
    char id[10];
    printf("\nMasukkan ID Meja: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = cariMejaByID(id);
    if (index == -1) {
        printf("Meja tidak ditemukan!\n");
        return;
    }

    printf("\n=== UBAH MEJA %s ===\n", id);

    printf("Nomor Baru    : ");
    scanf("%d", &daftarMeja[index].nomor);

    printf("Kapasitas Baru: ");
    scanf("%d", &daftarMeja[index].kapasitas);
    getchar();

    printf("Status Baru   : ");
    fgets(daftarMeja[index].status, sizeof(daftarMeja[index].status), stdin);
    daftarMeja[index].status[strcspn(daftarMeja[index].status, "\n")] = 0;

    printf("Data meja berhasil diubah!\n");
}

/* ================= DELETE ================= */
void hapusMeja() {
    char id[10];
    printf("\nMasukkan ID Meja: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = cariMejaByID(id);
    if (index == -1) {
        printf("Meja tidak ditemukan!\n");
        return;
    }

    for (int i = index; i < jumlahMeja - 1; i++) {
        daftarMeja[i] = daftarMeja[i + 1];
    }
    jumlahMeja--;

    printf("Meja berhasil dihapus!\n");
}

/* ================= SUPPORT ================= */
void generateID(char *id) {
    int max = 0, num;
    for (int i = 0; i < jumlahMeja; i++) {
        if (sscanf(daftarMeja[i].id_meja, "MJ%d", &num) == 1) {
            if (num > max) max = num;
        }
    }
    sprintf(id, "MJ%03d", max + 1);
}

int cariMejaByID(char *id) {
    for (int i = 0; i < jumlahMeja; i++) {
        if (strcmp(daftarMeja[i].id_meja, id) == 0)
            return i;
    }
    return -1;
}