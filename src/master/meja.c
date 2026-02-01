#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data.h"
#include "../../include/function.h"
#include "../../include/master/meja.h"

int totalMeja;
Meja daftarMeja[50];
int jumlahMeja = 0;

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
    int count = 0;
    for (int i = totalMeja - 1; i >= 0; i--)
    {
        if (daftarMeja[i].status != 1) continue;

        count++;
        if (count == noUrut) return i;
    }
    return -1;
}
int cariMeja(int noMeja) { // Fungsi ini mencari index array berdasarkan Nomor Meja
    for (int i = totalMeja - 1; i >= 0; i--) {
        if (daftarMeja[i].nomor_meja == noMeja) {
            return i; // Ketemu, kembalikan index array-nya
        }
    }
    return -1; // Tidak ketemu
}
void loadMeja() {
    FILE *f = fopen(FILE_MEJA, "rb");
    if (!f) {
        totalMeja = 0;
        return;
    }

    totalMeja = 0;
    while (fread(&daftarMeja[totalMeja], sizeof(Meja), 1, f)) {
        totalMeja++;
        if (totalMeja >= 50) break;
    }

    fclose(f);
}
void saveMeja() {
    FILE *f = fopen(FILE_MEJA, "wb");
    if (!f) return;

    fwrite(daftarMeja, sizeof(Meja), totalMeja, f);

    fclose(f);
}

/* ================= CREATE ================= */
void tambahMeja() {
    Meja m;
    char buffer[20];
    int left = 30, top = 11, right = 80, bot = 25;

    generateIDMeja(m.id_meja);
    m.keterangan = 1;   // Kosong
    m.status = 1;       // Aktif

    while(1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        frame(left, top, right, bot);

        gotoxy(1, 10); printf("TAMBAH MEJA BARU    ");
        gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Lanjut");

        int y = top + 2;
        y+=2; gotoxy(left + 2, y); printf("Nomor Meja : ");
        y+=2; gotoxy(left + 2, y); printf("Kapasitas  : ");

        // INPUT NOMOR
        do {
            clearinput(left+15, top+4, 10);
            gotoxy(left+15, top+4);
            showcurs();

            if(inputField(buffer) == 0) return;

            if(!onlyNum(buffer) || strlen(buffer) == 0) {
                gotoxy(left+2, bot-2); printf("Input harus angka!   ");
                continue;
            }

            int no = atoi(buffer);
            if(cariMeja(no) != -1) {
                gotoxy(left+2, bot-2); printf("Nomor Meja Sudah Ada!");
                continue;
            }

            m.nomor_meja = no;
            break;

        } while(1);
        clearinput(left+2, bot-2, 40);

        // INPUT KAPASITAS
        do {
            clearinput(left+15, top+6, 10); gotoxy(left+15, top+6); showcurs();
            if(inputField(buffer) == 0) return;
            if(onlyNum(buffer) && strlen(buffer) > 0) {
                m.kapasitas = atoi(buffer); break;
            }
            gotoxy(left+2, bot-2); printf("Input harus angka!");
        } while(1);
        clearinput(left+2, bot-2, 40);

        // SIMPAN
        if(popupConfirm("Simpan Meja Ini?", "Ya", "Batal")) {
            daftarMeja[totalMeja] = m;
            totalMeja++;
            saveMeja();
            popupAlert(1,"Meja Berhasil Ditambahkan!");
            return;
        }
    }
}

/* ================= READ ================= */
int renderTabelMeja(int left, int top, int right, int bot, int page) {
    gotoxy(60, 10); printf("DATA MEJA RESTORAN");
    frame(left, top, right, bot);

    int yhead = top + 1;
    gotoxy(left+2,  yhead); printf("No");
    gotoxy(left+10, yhead); printf("Nomor");
    gotoxy(left+25, yhead); printf("Kapasitas");
    gotoxy(left+42, yhead); printf("Keterangan");
    gotoxy(left+58, yhead); printf("Status");

    for (int x = left+1; x < right; x++) { gotoxy(x, yhead+1); printf("─"); }

    if(totalMeja == 0) loadMeja();

    int limit = 20;
    int start = (page - 1) * limit; // Item yang harus dilewati (skip)

    int printed = 0; // Jumlah item yang sudah DITAMPILKAN di layar
    int skipped = 0; // Jumlah item valid yang sudah DILEWATI (pagination logic)
    int y;

    // === LOOP 1: MEJA AKTIF (Status == 1) ===
    for (int i = totalMeja - 1; i >= 0; i--) {
        if (daftarMeja[i].status != 1) continue; // Skip jika bukan meja aktif

        // Logika Pagination
        if (skipped < start) {
            skipped++; // Ini item valid, tapi jatah halaman sebelumnya
            continue;
        }

        if (printed >= limit) break; // Halaman penuh

        // Cetak Data
        y = yhead + 2 + printed;

        // PERBAIKAN: Gunakan (start + printed + 1) untuk No Urut Tampilan
        gotoxy(left+2, y);  printf("%d", start + printed + 1);
        gotoxy(left+10, y); printf("Meja %02d", daftarMeja[i].nomor_meja);
        gotoxy(left+25, y); printf("%d Org", daftarMeja[i].kapasitas);
        gotoxy(left+42, y); printf("%s", daftarMeja[i].keterangan == 1 ? "Kosong" : "Terisi");
        gotoxy(left+58, y); printf("Aktif");

        printed++;
    }

    // === LOOP 2: MEJA RUSAK (Status == 0) ===
    // Lanjutkan counter 'skipped' dan 'printed' dari loop sebelumnya
    for (int i = totalMeja - 1; i >= 0 && printed < limit; i--)
    {
        if (daftarMeja[i].status != 0) continue; // Skip jika bukan meja rusak

        if (printed >= limit) break; // Jika halaman sudah penuh oleh meja aktif, stop.

        if (skipped < start) {
            skipped++;
            continue;
        }
        setRGBColor(210, 212, 200, 0);
        y = yhead + 2 + printed;

        gotoxy(left+2, y);  printf("%d", start + printed + 1);
        gotoxy(left+10, y); printf("Meja %02d", daftarMeja[i].nomor_meja);
        gotoxy(left+25, y); printf("%d Org", daftarMeja[i].kapasitas);
        gotoxy(left+42, y); printf("-");
        gotoxy(left+58, y); printf("Rusak");

        printed++;
    }
    return totalMeja;
}
int hitungMejaAktif()
{
    int count = 0;
    for (int i = 0; i < totalMeja; i++)
    {
        if (daftarMeja[i].status == 1)
            count++;
    }
    return count;
}

/* ================= UPDATE ================= */
void ubahMeja() {
    int noUrut;
    char buffer[20];
    int left = 30, top = 11, right = 80, bot = 25;

    while(1) {
        int clearW = consoleW() - 27; int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);

        gotoxy(1, 10); printf("UBAH DATA MEJA      ");
        gotoxy(30, 10); printf("[ESC] Batal   [ENTER] Lanjut");
        gotoxy(30, 11); printf("Masukkan No Urut : ");
        showcurs();
        if (inputField(buffer) == 0) return;
        noUrut = atoi(buffer);

        int idx = cariMejaNorut(noUrut);
        if(idx == -1) { popupAlert(0,"Nomor Tidak Valid!"); continue; }

        Meja *m = &daftarMeja[idx];

        while(1) {
            clearArea(27, 9, clearW, clearH);
            frame(left, top, right, bot);
            gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Skip/Lanjut");

            int y = top + 2;
            gotoxy(left+2, y); printf("ID Meja    : %s", m->id_meja);
            y+=2; gotoxy(left+2, y); printf("Nomor Meja : %d", m->nomor_meja);
            y+=2; gotoxy(left+2, y); printf("Kapasitas  : %d Orang", m->kapasitas);
            y+=2; gotoxy(left+2, y); printf("Keterangan : %d", m->keterangan);
            y+=1; gotoxy(left+15, y); printf("(1=Kosong, 2=Terisi)");

            // EDIT NOMOR
            clearinput(left+15, top+4, 10); gotoxy(left+15, top+4); showcurs();
            if(inputField(buffer) == 0) return;
            if(strlen(buffer) > 0) m->nomor_meja = atoi(buffer);
            gotoxy(left+15, top+4); printf("%d", m->nomor_meja);

            // EDIT KAPASITAS
            clearinput(left+15, top+6, 10); gotoxy(left+15, top+6); showcurs();
            if(inputField(buffer) == 0) return;
            if(strlen(buffer) > 0) m->kapasitas = atoi(buffer);
            gotoxy(left+15, top+6); printf("%d", m->kapasitas);

            // EDIT STATUS
            clearinput(left+15, top+8, 5); gotoxy(left+15, top+8); showcurs();
            if (inputField(buffer) == 0) return;
            if (strlen(buffer) > 0) m->keterangan = atoi(buffer);
            gotoxy(left+15, top+8); printf("%d", m->keterangan);

            if(popupConfirm("Simpan Perubahan?", "Ya", "batal")) {
                saveMeja();
                popupAlert(1,"Data Berhasil Diubah!");
                return;
            }
        }
    }
}

/* ================= DELETE ================= */
void hapusMeja() {
    char buffer[10];
    int noUrut;

    int left = 30, top = 11, right = 80, bot = 25;

    int clearW = consoleW() - 27;
    int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    gotoxy(30, 10); printf("[ESC] Batal   [ENTER] Lanjut");
    gotoxy(30, 11); printf("Masukkan No Urut : ");
    showcurs();
    if (inputField(buffer) == 0) return;
    noUrut = atoi(buffer);

    int idx = cariMejaNorut(noUrut);
    if (idx == -1) {
        popupAlert(0, "Nomor Tidak Valid!");
        return;
    }

    if (daftarMeja[idx].keterangan == 2) {
        popupAlert(0, "Meja Sedang Terisi!");
        return;
    }

    if (daftarMeja[idx].status == 0) {
        popupAlert(0, "Meja Sudah Dinonaktifkan!");
        return;
    }

    Meja *m = &daftarMeja[idx];

    int y = top + 2;
    gotoxy(left+2, y); printf("ID Meja    : %s", m->id_meja);
    y+=2; gotoxy(left+2, y); printf("Nomor Meja : %d", m->nomor_meja);
    y+=2; gotoxy(left+2, y); printf("Kapasitas  : %d Orang", m->kapasitas);
    y+=2; gotoxy(left+2, y); printf("Keterangan : %s", m->keterangan==1?"Kosong":"Terisi");

    y+=2;gotoxy(left+2,y);printf("tekan ENTER untuk lanjut..."); getchar();

    if (popupConfirm("Nonaktifkan Meja Ini?", "ya", "Batal")) {
        daftarMeja[idx].status = 0; // Rusak
        saveMeja();
        popupAlert(1, "Meja Dinonaktifkan");
    }
}