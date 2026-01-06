#ifndef EATBOX_PESANAN_H
#define EATBOX_PESANAN_H

#include "../function.h"
#include "../data.h"
#include "../MASTER/meja.h"
int left = 30, top = 11, right = 105, bot = 35;
extern Meja daftarMeja[50];
extern int totalMeja;
extern Menu daftarMenu[100];
extern int jumlahMenu;

void autoIDPesan(char *out) {
    FILE *f = fopen("../FILE/pesanan.dat", "rb");
    Pesanan p;
    int last = 0;

    if (f) {
        while (fread(&p, sizeof(Pesanan), 1, f)) {
            sscanf(p.id_pesan, "ORD%d", &last);
        }
        fclose(f);
    }
    sprintf(out, "ORD%03d", last + 1);
}
double getHargaMenu(char *id_menu) {
    FILE *f = fopen("../FILE/menu.dat", "rb");
    Menu m;
    if (!f) return 0;

    while (fread(&m, sizeof(Menu), 1, f)) {
        if (strcmp(m.id_menu, id_menu) == 0) {
            fclose(f);
            return m.harga;
        }
    }
    fclose(f);
    return 0;
}
int getNamaKasir(const char *id, char *outNama) {
    FILE *f = fopen("../FILE/karyawan.dat", "r");
    if (!f) return 0;

    char line[512];
    char fid[20], user[20], pass[50], nama[50];
    char telp[20], email[50], role[20], alamat[255];
    int stat;

    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               fid, user, pass, nama, telp, email, role, alamat, &stat);

        if (strcmp(fid, id) == 0) {
            strcpy(outNama, nama);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
void miniMeja(int x, int y)
{
    gotoxy(x+1, y+1); printf("Daftar Meja");
    gotoxy(x+1, y+2); printf("No  Meja  Status");

    int yy = y + 3;
    int no = 1;
    for (int i = 0; i < totalMeja; i++)
    {
        if (daftarMeja[i].status == 0) continue;

        gotoxy(x + 1, yy++);
        printf("%-3d %-5d %s",
            no++,
            daftarMeja[i].nomor_meja,
            daftarMeja[i].keterangan == 1 ? "Kosong" : "Terisi"
        );
    }
}
void showMenuPage(int page, int x, int z)
{
    int start = (page - 1) * 10;
    int end = start + 10;

    gotoxy(x, z++);printf("Daftar Menu");
    gotoxy(x, z++);printf("No  Nama Menu          Harga");

    for (int i = start; i < end && i < jumlahMenu; i++)
    {
        gotoxy(x, z++);
        printf("%-3d %-18.18s Rp%.0f",
            i + 1,
            daftarMenu[i].nama_menu,
            daftarMenu[i].harga
        );
    }

    gotoxy(x, z + 1);
    printf("[<] Prev   [>] Next");
}

void tambahPesan() {
    int clearW = consoleW() - 27; int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    Pesanan p;
    char buf[10];
    loadMeja();
    miniMeja(115, top);

    autoIDPesan(p.id_pesan);
    strcpy(p.id_akun, currentKasirID);
    strcpy(p.status, "OPEN");
    p.total = 0;
    p.tanggal = now();

    clearinput(left, top-1, 40);
    gotoxy(left, top-1); printf("[ESC] Batal   [ENTER] Lewati/Lanjut");
    gotoxy(left,top+1);  printf("No Meja (0=Take Away): ");showcurs();
    do
    {
        inputtext(buf);
        if (!onlyNum(buf)) continue;

        int idx = atoi(buf) - 1;
        if (idx < 0 || idx >= totalMeja) continue;

        p.no_meja = daftarMeja[idx].nomor_meja; // ⬅ INI JUGA WAJIB
        break;
    } while (1);
    int apus = top;
    for (int i = 0; i <= totalMeja; i++)
    {
        clearinput(115, apus, 20);
        apus++;
    }

    FILE *fp = fopen("../FILE/pesanan.dat", "ab");
    fwrite(&p, sizeof(Pesanan), 1, fp);
    fclose(fp);

    currentPage = 1;
    while (1) {
        DetailPesanan d;
        strcpy(d.id_pesan, p.id_pesan);

        loadMenu();
        char buf[10] = "";
        int len = 0;

        while (1)
        {
            clearArea(95, top, 40, 20);
            showMenuPage(currentPage, 100, top);

            gotoxy(left, top + 2);
            printf("No Menu : %s", buf);

            char ch = _getch();

            // === PANAH ===
            if (ch == 75 && currentPage > 1) {              // ←
                currentPage--;
                len = 0; buf[0] = '\0';
            }
            else if (ch == 77 && currentPage * 10 < jumlahMenu) { // →
                currentPage++;
                len = 0; buf[0] = '\0';
            }

            // === ENTER ===
            else if (ch == 13 && len > 0) {
                break;
            }

            // === BACKSPACE ===
            else if (ch == 8 && len > 0) {
                buf[--len] = '\0';
            }

            else if (ch==27) return;

            // === ANGKA ===
            else if (ch >= '0' && ch <= '9' && len < 5) {
                buf[len++] = ch;
                buf[len] = '\0';
            }
        }
        int pilih = atoi(buf) - 1;
        int index = (currentPage - 1) * 10 + pilih;

        if (index < 0 || index >= jumlahMenu) {
            popupAlert(0, "Menu tidak valid");
            continue;
        }

        strcpy(d.id_menu, daftarMenu[index].id_menu);

        gotoxy(left,top+3); printf("Jumlah  : ");
        inputtext(buf);
        if (!onlyNum(buf)) continue;
        d.jumlah = atoi(buf);

        d.subtotal = getHargaMenu(d.id_menu) * d.jumlah;
        p.total += d.subtotal;

        FILE *fd = fopen("../FILE/detail_pesanan.dat", "ab");
        fwrite(&d, sizeof(DetailPesanan), 1, fd);
        fclose(fd);

        if (!popupConfirm("Tambah menu lagi?")) break;
    }

    // update total
    FILE *fr = fopen("../FILE/pesanan.dat", "rb+");
    Pesanan temp;
    while (fread(&temp, sizeof(Pesanan), 1, fr)) {
        if (strcmp(temp.id_pesan, p.id_pesan) == 0) {
            temp.total = p.total;
            fseek(fr, -sizeof(Pesanan), SEEK_CUR);
            fwrite(&temp, sizeof(Pesanan), 1, fr);
            break;
        }
    }
    fclose(fr);

    popupAlert(1, "Pesanan berhasil dibuat");
}

int lihatPesan() {
    FILE *f = fopen("../FILE/pesanan.dat", "rb");
    if (!f) return 0;

    Pesanan p;
    int total = 0;
    int left = 28, top = 11;
    char namaKasir[50];
    char jam[10];

    int x = left;
    int y = top + 3;

    while (fread(&p, sizeof(Pesanan), 1, f)) {
        if (!hariIni(p.tanggal)) continue;

        formatJam(p.tanggal, jam);                 // mengambil data jam
        getNamaKasir(p.id_akun, namaKasir);        // mengambil nama kasir

        gotoxy(x+2, y);printf("%d",total + 1);
        gotoxy(x+6, y);printf("%s", namaKasir);
        gotoxy(x+20, y);printf("%d", p.no_meja);
        gotoxy(x+36, y);printf("%.0f", p.total);
        gotoxy(x+50, y);printf("%s", p.status);
        gotoxy(x+66, y); printf("%s", jam);
        total++;
        y++;
    }

    fclose(f);
    return total;
}

void selesaiPesan() {
    int clearW = consoleW() - 27; int clearH = consoleH() - 9;
    clearArea(27, 9, clearW, clearH);

    FILE *f = fopen("../FILE/pesanan.dat", "rb+");
    Pesanan p;

    char id[10];

    clearinput(left, top-1, 40);
    gotoxy(left, top-1); printf("[ESC] Batal   [ENTER] Lewati/Lanjut");
    gotoxy(left,top+1); printf("ID Pesanan: ");
    inputid(id);

    while (fread(&p, sizeof(Pesanan), 1, f)) {
        if (strcmp(p.id_pesan, id) == 0 && strcmp(p.status, "OPEN") == 0) {

            if (pembayaran(p.id_pesan, p.total)) {
                strcpy(p.status, "DONE");
                fseek(f, -sizeof(Pesanan), SEEK_CUR);
                fwrite(&p, sizeof(Pesanan), 1, f);

                if (p.no_meja > 0)
                    kosongkanMeja(p.no_meja);

                popupAlert(1, "Pesanan selesai");
            }
            break;
        }
    }
    fclose(f);
}

#endif //EATBOX_PESANAN_H