#ifndef EATBOX_MENU_H
#define EATBOX_MENU_H

#define MAX_MENU 100
#define FILENAME "../FILE/menu.dat"
#define ITEMS_PER_PAGE 10

extern Menu daftarMenu[MAX_MENU];
extern int jumlahMenu;

// DECLARATION
void tampilMenuUtama();
int cariMenuByID(char *id);
void tampilkanTabel(int page);
void cariMenu();
void tambahMenu();
void lihatMenu();
void ubahMenu();
void hapusMenu();
void saveMenu();

// int Main() {
//     loadMenu();
//     int pilih;
//
//     do {
//         system("cls");
//         tampilMenuUtama();
//         printf("\nPilih menu (1-6): ");
//
//         if (scanf("%d", &pilih) != 1) {
//             while (getchar() != '\n');
//             printf("\nInput tidak valid! Tekan Enter...");
//             getch();
//             continue;
//         }
//         while (getchar() != '\n');
//
//         switch (pilih) {
//             case 1:
//                 tambahMenu();
//                 break;
//             case 2:
//                 lihatMenu();
//                 break;
//             case 3:
//                 ubahMenu();
//                 break;
//             case 4:
//                 hapusMenu();
//                 break;
//             case 5:
//                 cariMenu();
//                 break;
//             case 6:
//                 printf("\n=== Terima kasih ===\n");
//                 saveMenu();
//                 break;
//             default:
//                 printf("\nPilihan tidak sesuai! Tekan Enter untuk kembali...");
//                 getch();
//         }
//     } while (pilih != 6);
//
//     return 0;
// }
// void tampilMenuUtama() {
//     applyColors();
//     printf("\n");
//     printf("|========================================|\n");
//     printf("|               EAT BOX                  |\n");
//     printf("|========================================|\n");
//     printf("|  1. Tambah Menu Baru                   |\n");
//     printf("|  2. Lihat Semua Menu                   |\n");
//     printf("|  3. Ubah Menu                          |\n");
//     printf("|  4. Hapus Menu                         |\n");
//     printf("|  5. Cari Menu                          |\n");
//     printf("|  6. Keluar                             |\n");
//     printf("|========================================|\n");
// }

void saveMenu() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("\n[ERROR] Gagal menyimpan data!\n");
        return;
    }

    for (int i = 0; i < jumlahMenu; i++) {
        fprintf(file, "%s|%s|%s|%.2lf|%s|%d\n",
        daftarMenu[i].id_menu,
        daftarMenu[i].kategori,
        daftarMenu[i].nama_menu,
        daftarMenu[i].harga,
        daftarMenu[i].deskripsi,
        daftarMenu[i].status);
    }

    fclose(file);
}
void generateID(char *id) {
    int maxNum = 0;
    for (int i = 0; i < jumlahMenu; i++) {
        int num;
        if (sscanf(daftarMenu[i].id_menu, "MN%d", &num) == 1) {
            if (num > maxNum) maxNum = num;
        }
    }
    sprintf(id, "MN%03d", maxNum + 1);
}
int cariMenuByID(char *id) {
    for (int i = 0; i < jumlahMenu; i++) {
        if (strcmp(daftarMenu[i].id_menu, id) == 0) {
            return i;
        }
    }
    return -1;
}

void tambahMenu() {
    // system("cls");
    // applyColors();
    // jangan di pake, biar g ke hapus navigasi menu nya

    Menu m;
    int pointer = 0;   // indeks input yang aktif
    int maxField = 5;  // kategori, nama, harga, deskripsi, status
    int left = 30, top = 11, right = 105, bot = 35; // ini kordinat buat isi nya

    strcpy(m.kategori, "");
    strcpy(m.nama_menu, "");
    m.harga = 0;
    strcpy(m.deskripsi, "");
    // m.status = 0;   // <-- PERBAIKAN (bukan strcpy)
    m.status = 1; // biar default nya tersedia
    generateID(m.id_menu);

    while (1) {
        // system("cls");  jangan di pake

        //ini pengganti cls biar g keapus semua
        int clearW = consoleW() - 27; int clearH = consoleH() - 9; //deklarasi kordinat yang jadi lokasi isi nya
        clearArea(27, 9, clearW, clearH); //hapus isi sebelum nya
        frame(left, top, right, bot); // buat garis tabel

        clearinput(1,10,24); gotoxy(1, 10); printf("TAMBAH MENU BARU");
        gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Lanjut");

        // ini buat form nya kalo mau coba bikin sendiri silahkan, tapi ini template punya ku
        // int y = top + 2;
        // gotoxy(left + 2, y); printf("ID Menu   : %s", m.id_menu);
        // y += 2; gotoxy(left + 2, y); printf("Kategori  : ");
        // y += 2; gotoxy(left + 2, y); printf("Nama Menu : ");
        // y += 2; gotoxy(left + 2, y); printf("Harga     : Rp ");
        // y += 2; gotoxy(left + 2, y); printf("Deskripsi : ");
        // y += 2; gotoxy(left + 2, y); printf("Status    : ");

        // // 1. INPUT KATEGORI
        // do {
        //     clearinput(left + 14, top + 4, 30); gotoxy(left + 14, top + 4); showcurs();
        //     if (inputtext(m.kategori) == 0) return; // ESC
        //     if (strlen(m.kategori) == 0) { gotoxy(left + 14, top + 5); printf("Wajib diisi!"); }
        //     else break;
        // } while (1);
        // clearinput(left + 14, top + 5, 20);
        //
        // // 2. INPUT NAMA MENU
        // do {
        //     clearinput(left + 14, top + 6, 40); gotoxy(left + 14, top + 6); showcurs();
        //     if (inputMultiWord(m.nama_menu) == 0) return;
        //     if (strlen(m.nama_menu) == 0) { gotoxy(left + 14, top + 7); printf("Wajib diisi!"); }
        //     else break;
        // } while (1);
        // clearinput(left + 14, top + 7, 20);
        //
        // // 3. INPUT HARGA
        // do {
        //     clearinput(left + 17, top + 8, 20); gotoxy(left + 17, top + 8); showcurs();
        //     if (inputtext(buffer) == 0) return;
        //     if (strlen(buffer) > 0 && onlyNum(buffer)) {
        //         m.harga = atof(buffer);
        //         break;
        //     }
        //     gotoxy(left + 17, top + 9); printf("Harus angka!");
        // } while (1);
        // clearinput(left + 17, top + 9, 20);
        //
        // // 4. INPUT DESKRIPSI
        // clearinput(left + 14, top + 10, 50); gotoxy(left + 14, top + 10); showcurs();
        // if (inputMultiWord(m.deskripsi) == 0) return;
        //
        // // SIMPAN
        // if (popupConfirm("Simpan Menu Ini?")) {
        //     daftarMenu[jumlahMenu] = m;
        //     jumlahMenu++;
        //     saveMenu();
        //     popupAlert("Menu Berhasil Ditambahkan!");
        //     return;
        // }

        //posisi header
        printf("\033[41m\033[93m");  // background merah, teks kuning
        printf("\n\n                 EATBOX - INPUT MENU BARU\n\n");
        printf("\033[0m");

        //form
        printf("\033[41m"); // background merah
        printf("  ---------------------------------------------------------  \n");
        printf("     ID Menu      : %s\n", m.id_menu);
        printf("     Kategori     : %s\n", m.kategori);
        printf("     Nama Menu    : %s\n", m.nama_menu);
        printf("     Harga        : %.0lf\n", m.harga);
        printf("     Deskripsi    : %s\n", m.deskripsi);
        printf("     Status       : %s\n", (m.status == 1) ? "Tersedia" : "Habis");
        printf("  ---------------------------------------------------------  \n\n");
        printf("\033[0m");

        //sidebar
        char *field[] = {
            "Kategori",
            "Nama Menu",
            "Harga",
            "Deskripsi",
            "Status",
            "Simpan",
            "Batal"
        };

        printf("\033[41m\033[93m");
        printf("   [↑↓] Pilih Input   [ENTER] Edit / Lanjut\n\n");
        printf("\033[0m");

        for (int i = 0; i < 7; i++) {
            if (i == pointer) {
                setRGBColor(202, 40, 44, 0);
                setRGBColor(251, 255, 199, 1);
                printf("   \033[93m> %s\033[0m\n", field[i]);
            }
            else {
                setRGBColor(202, 40, 44, 1);
                setRGBColor(251, 255, 199, 0);
                printf("     %s\n", field[i]);
            }
        }

        //untuk memulai
        char tombol = getch();

        if (tombol == 72) {  // UP
            pointer--;
            if (pointer < 0) pointer = 6;
        }
        else if (tombol == 80) { // DOWN
            pointer++;
            if (pointer > 6) pointer = 0;
        }
        else if (tombol == 13) { // ENTER
            system("cls");

            switch (pointer) {

            case 0: // Kategori
                printf("Masukkan Kategori : ");
                fgets(m.kategori, sizeof(m.kategori), stdin);
                m.kategori[strcspn(m.kategori, "\n")] = 0;
                break;

            case 1: // Nama Menu
                printf("Masukkan Nama Menu : ");
                fgets(m.nama_menu, sizeof(m.nama_menu), stdin);
                m.nama_menu[strcspn(m.nama_menu, "\n")] = 0;
                break;

            case 2: // Harga
                printf("Masukkan Harga : ");
                while (scanf("%lf", &m.harga) != 1 || m.harga < 0) {
                    while (getchar() != '\n');
                    printf("Harga tidak valid! Masukkan angka: ");
                }
                while (getchar() != '\n');
                break;

            case 3: // Deskripsi
                printf("Masukkan Deskripsi : ");
                fgets(m.deskripsi, sizeof(m.deskripsi), stdin);
                m.deskripsi[strcspn(m.deskripsi, "\n")] = 0;
                break;

                case 4:
                    printf("Masukkan Status (1=Tersedia, 0=Habis): ");
                    scanf("%d", &m.status);
                    while (getchar() != '\n');
                    break;

            case 5: //menyimpan
                daftarMenu[jumlahMenu++] = m;
                saveMenu();
                printf("\nMenu berhasil disimpan!");
                getch();
                return;

            case 6: //batal
                return;
            }
        }
    }
}
void ubahMenu() {
    // system("cls");
    // applyColors();
    // masih sama, dua ini g perlu di kasih kyk yang atas.

    //ini punya mu oke, tapi karna printf dan \n jadi susah atur posisi nya
    //coba pake fungsi gotoxy() udh ada g ush buat lagi
    //di bawah ini template kalo mau ikutin style nya samaan,
    // int left = 30, top = 11, right = 105, bot = 35; // acuah buat lokasi isi nya
    // char buffer[100];
    // char idTarget[20];
    //
    // // STEP 1: Minta ID Menu
    // while(1) {
    //     int clearW = consoleW() - 27; int clearH = consoleH() - 9;
    //     clearArea(27, 9, clearW, clearH);
    //
    //     gotoxy(1, 10); printf("UBAH DATA MENU      ");
    //     gotoxy(30, 10); printf("Masukkan ID Menu (cth: MN001): ");
    //     showcurs();
    //     if(inputtext(idTarget) == 0) return; // ESC
    //
    //     int idx = cariMenuIndex(idTarget);
    //     if(idx == -1) {
    //         gotoxy(30, 12); printf("ID Tidak Ditemukan!"); Sleep(1000);
    //         continue;
    //     }
    //
    //     // Data Ketemu, Masuk Form Edit
    //     Menu *m = &daftarMenu[idx]; // Pointer ke data asli
    //
    //     while(1) {
    //         clearArea(27, 9, clearW, clearH);
    //         frame(left, top, right, bot);
    //
    //         gotoxy(1, 10); printf("UBAH DATA MENU      ");
    //         gotoxy(left, top - 1); printf(" [ESC] Batal   [ENTER] Skip/Lanjut");
    //
    //         // Tampilkan Data Lama
    //         int y = top + 2;
    //         gotoxy(left + 2, y); printf("ID Menu   : %s", m->id_menu);
    //         y += 2; gotoxy(left + 2, y); printf("Kategori  : %s", m->kategori);
    //         y += 2; gotoxy(left + 2, y); printf("Nama Menu : %s", m->nama_menu);
    //         y += 2; gotoxy(left + 2, y); printf("Harga     : %.0lf", m->harga);
    //         y += 2; gotoxy(left + 2, y); printf("Deskripsi : %s", m->deskripsi);
    //         y += 2; gotoxy(left + 2, y); printf("Status    : %s", (m->status == 1 ? "1 (Ready)" : "0 (Habis)"));
    //
    //         // EDIT KATEGORI
    //         clearinput(left + 14, top + 4, 30); gotoxy(left + 14, top + 4); showcurs();
    //         if (inputtext(buffer) == 0) return;
    //         if (strlen(buffer) > 0) strcpy(m->kategori, buffer);
    //         gotoxy(left + 14, top + 4); printf("%s", m->kategori); // Reprint
    //
    //         // EDIT NAMA
    //         clearinput(left + 14, top + 6, 40); gotoxy(left + 14, top + 6); showcurs();
    //         if (inputMultiWord(buffer) == 0) return;
    //         if (strlen(buffer) > 0) strcpy(m->nama_menu, buffer);
    //         gotoxy(left + 14, top + 6); printf("%s", m->nama_menu);
    //
    //         // EDIT HARGA
    //         do {
    //             clearinput(left + 14, top + 8, 20); gotoxy(left + 14, top + 8); showcurs();
    //             if (inputtext(buffer) == 0) return;
    //             if (strlen(buffer) == 0) break; // Skip
    //             if (onlyNum(buffer)) {
    //                 m->harga = atof(buffer);
    //                 break;
    //             }
    //         } while(1);
    //         gotoxy(left + 14, top + 8); printf("%.0lf", m->harga);
    //
    //         // EDIT DESKRIPSI
    //         clearinput(left + 14, top + 10, 50); gotoxy(left + 14, top + 10); showcurs();
    //         if (inputMultiWord(buffer) == 0) return;
    //         if (strlen(buffer) > 0) strcpy(m->deskripsi, buffer);
    //
    //         // EDIT STATUS
    //         clearinput(left + 14, top + 12, 10); gotoxy(left + 14, top + 12); showcurs();
    //         if (inputtext(buffer) == 0) return;
    //         if (strlen(buffer) > 0) {
    //             if(strcmp(buffer, "1")==0) m->status = 1;
    //             else m->status = 0;
    //         }
    //
    //         if(popupConfirm("Simpan Perubahan?")) {
    //             saveMenu();
    //             popupAlert("Data Berhasil Diubah!");
    //             return;
    //         }
    //     }
    // }


    printf("\n|=======================================|\n");
    printf("|             UBAH MENU                   |\n");
    printf("\n|=======================================|\n");

    char id[10];
    printf("\nMasukkan ID menu yang ingin diubah: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = cariMenuByID(id);

    if (index == -1) {
        printf("\n[ERROR] Menu dengan ID '%s' tidak ditemukan!\n", id);
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    printf("\n--- Data Saat Ini ---\n");
    printf("ID        : %s\n", daftarMenu[index].id_menu);
    printf("Kategori  : %s\n", daftarMenu[index].kategori);
    printf("Nama      : %s\n", daftarMenu[index].nama_menu);
    printf("Harga     : Rp %.2lf\n", daftarMenu[index].harga);
    printf("Deskripsi : %s\n", daftarMenu[index].deskripsi);
    printf("Status    : %s\n", daftarMenu[index].status);

    printf("\n--- Masukkan Data Baru ---\n");

    printf("Kategori Baru  : ");
    fgets(daftarMenu[index].kategori, sizeof(daftarMenu[index].kategori), stdin);
    daftarMenu[index].kategori[strcspn(daftarMenu[index].kategori, "\n")] = 0;

    printf("Nama Baru      : ");
    fgets(daftarMenu[index].nama_menu, sizeof(daftarMenu[index].nama_menu), stdin);
    daftarMenu[index].nama_menu[strcspn(daftarMenu[index].nama_menu, "\n")] = 0;

    printf("Harga Baru     : ");
    while (scanf("%lf", &daftarMenu[index].harga) != 1 || daftarMenu[index].harga < 0) {
        while (getchar() != '\n');
        printf("Input tidak valid! Masukkan harga yang benar: ");
    }
    while (getchar() != '\n');

    printf("Deskripsi Baru : ");
    fgets(daftarMenu[index].deskripsi, sizeof(daftarMenu[index].deskripsi), stdin);
    daftarMenu[index].deskripsi[strcspn(daftarMenu[index].deskripsi, "\n")] = 0;

    printf("Status Baru (1 = Tersedia, 0 = Habis): ");
    scanf("%d", &daftarMenu[index].status);
    getchar(); // menghilangkan newline


    saveMenu();
    printf("\nMenu berhasil diubah!\n");
    printf("Tekan Enter untuk kembali.");
    getch();
}
void hapusMenu() {
    // system("cls");
    // applyColors();
    //sama kayak yang atas

    //ini template nya biar g bingung, bebas kalo mau coba sendiri
    // char idTarget[20];
    //
    // while(1) {
    //     int clearW = consoleW() - 27; int clearH = consoleH() - 9;
    //     clearArea(27, 9, clearW, clearH);
    //
    //     gotoxy(1, 10); printf("HAPUS DATA MENU     ");
    //     gotoxy(30, 10); printf("Masukkan ID Menu : ");
    //     showcurs();
    //     if(inputtext(idTarget) == 0) return;
    //
    //     int idx = cariMenuIndex(idTarget);
    //     if(idx == -1) {
    //         gotoxy(30, 12); printf("ID Tidak Ditemukan!"); Sleep(1000);
    //         continue;
    //     }
    //
    //     // Tampilkan info sedikit biar yakin
    //     gotoxy(30, 12); printf("Menu: %s (Rp %.0lf)", daftarMenu[idx].nama_menu, daftarMenu[idx].harga);
    //
    //     if(popupConfirm("Yakin Hapus Menu Ini?")) {
    //         // Geser Array
    //         for (int i = idx; i < jumlahMenu - 1; i++) {
    //             daftarMenu[i] = daftarMenu[i + 1];
    //         }
    //         jumlahMenu--;
    //         saveMenu();
    //         popupAlert("Menu Berhasil Dihapus!");
    //         return;
    //     }
    // }


    printf("\n|=======================================|\n");
    printf("\n|          HAPUS MENU                   |\n");
    printf("\n|=======================================|\n");

    char id[10];
    printf("\nMasukkan ID menu yang ingin dihapus: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = cariMenuByID(id);

    if (index == -1) {
        printf("\n[ERROR] Menu dengan ID '%s' tidak ditemukan!\n", id);
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    printf("\n--- Data Menu ---\n");
    printf("ID        : %s\n", daftarMenu[index].id_menu);
    printf("Kategori  : %s\n", daftarMenu[index].kategori);
    printf("Nama      : %s\n", daftarMenu[index].nama_menu);
    printf("Harga     : Rp %.2lf\n", daftarMenu[index].harga);

    printf("\nApakah Anda yakin ingin menghapus menu ini? (y/n): ");
    char konfirmasi;
    scanf(" %c", &konfirmasi);
    while (getchar() != '\n');

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = index; i < jumlahMenu - 1; i++) {
            daftarMenu[i] = daftarMenu[i + 1];
        }
        jumlahMenu--;

        saveMenu();
        printf("\n[OK] Menu berhasil dihapus!\n");
    } else {
        printf("\n[INFO] Penghapusan dibatalkan.\n");
    }

    printf("Tekan Enter untuk kembali.");
    getch();
}
void cariMenu() {
    // system("cls");
    // applyColors();
    // ini juga sama

    //template
    // char keyword[50];
    // int clearW = consoleW() - 27; int clearH = consoleH() - 9;
    // clearArea(27, 9, clearW, clearH);
    //
    // gotoxy(1, 10); printf("CARI DATA MENU      ");
    // gotoxy(30, 10); printf("Masukkan Kata Kunci : ");
    // showcurs();
    // if(inputtext(keyword) == 0) return;
    //
    // // Tampilkan Hasil di Tabel Sederhana
    // int left = 30, top = 13, right = 105, bot = 35;
    // frame(left, top, right, bot);
    //
    // int y = top + 1;
    // gotoxy(left+2, y++); printf("%-6s %-20s %-15s", "ID", "Nama Menu", "Kategori");
    // gotoxy(left+1, y++); for(int k=left+1;k<right;k++) printf("─");
    //
    // int found = 0;
    // for(int i=0; i<jumlahMenu; i++) {
    //     // Cek Nama ATAU Kategori
    //     if(strstr(daftarMenu[i].nama_menu, keyword) || strstr(daftarMenu[i].kategori, keyword)) {
    //         if(y >= bot-1) break; // Mentok bawah
    //         gotoxy(left+2, y++);
    //         printf("%-6s %-20s %-15s", daftarMenu[i].id_menu, daftarMenu[i].nama_menu, daftarMenu[i].kategori);
    //         found++;
    //     }
    // }
    //
    // if(found==0) { gotoxy(left+2, y); printf("Tidak ditemukan."); }
    // else { gotoxy(left, bot+1); printf("Ditemukan %d menu.", found); }
    //
    // _getch();


    printf("\n|=======================================|\n");
    printf("|               CARI MENU               |\n");
    printf("|=======================================|\n");

    char keyword[100];
    printf("\nMasukkan kata kunci (nama/kategori): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("\n");
    printf("|======|==================|========================|==========|=========================|============|\n");
    printf("| %-4s | %-16s | %-22s | %-8s | %-23s | %-10s |\n",
           "ID", "Kategori", "Nama Menu", "Harga", "Deskripsi", "Status");
    printf("|======|==================|========================|==========|=========================|============|\n");

    int found = 0;

    for (int i = 0; i < jumlahMenu; i++) {
        if (strstr(daftarMenu[i].nama_menu, keyword) ||
            strstr(daftarMenu[i].kategori, keyword)) {

            char desc_short[24];
            if (strlen(daftarMenu[i].deskripsi) > 23) {
                strncpy(desc_short, daftarMenu[i].deskripsi, 20);
                desc_short[20] = '.';
                desc_short[21] = '.';
                desc_short[22] = '.';
                desc_short[23] = '\0';
            } else {
                strcpy(desc_short, daftarMenu[i].deskripsi);
            }

            printf("| %-4s | %-16s | %-22s | %8.0lf | %-23s | %-10s |\n",
                   daftarMenu[i].id_menu,
                   daftarMenu[i].kategori,
                   daftarMenu[i].nama_menu,
                   daftarMenu[i].harga,
                   desc_short,
                   daftarMenu[i].status);
            found = 1;
            }
    }

    if (!found) {
        printf("| %-100s |\n", "Tidak ada menu yang cocok dengan pencarian.");
    }

    printf("|======|==================|========================|==========|=========================|============|\n");
    printf("Tekan Enter untuk kembali...");
    getch();
}

void tampilkanTabel(int page) {
    applyColors();

    int maxPage = (jumlahMenu == 0) ? 1 : ((jumlahMenu - 1) / ITEMS_PER_PAGE) + 1;

    if (page > maxPage) page = maxPage;
    if (page < 1) page = 1;
    currentPage = page;

    int start = (page - 1) * ITEMS_PER_PAGE;
    int end = start + ITEMS_PER_PAGE;
    if (end > jumlahMenu) end = jumlahMenu;

    printf("\n");
    printf("|======|==================|========================|==========|=========================|============|\n");
    printf("| %-4s | %-16s | %-22s | %-8s | %-23s | %-10s |\n",
           "ID", "Kategori", "Nama Menu", "Harga", "Deskripsi", "Status");
    printf("|======|==================|========================|==========|=========================|============|\n");

    for (int i = start; i < end; i++) {
        char statusTxt[12];
        strcpy(statusTxt, (daftarMenu[i].status == 1) ? "Tersedia" : "Habis");

        char desc_short[24];
        if (strlen(daftarMenu[i].deskripsi) > 23) {
            strncpy(desc_short, daftarMenu[i].deskripsi, 20);
            desc_short[20] = '.';
            desc_short[21] = '.';
            desc_short[22] = '.';
            desc_short[23] = '\0';
        } else {
            strcpy(desc_short, daftarMenu[i].deskripsi);
        }

        printf("| %-4s | %-16s | %-22s | %8.0lf | %-23s | %-10s |\n",
               daftarMenu[i].id_menu,
               daftarMenu[i].kategori,
               daftarMenu[i].nama_menu,
               daftarMenu[i].harga,
               desc_short,
               statusTxt);
    }

    printf("|======|==================|========================|==========|=========================|============|\n");
    printf("Halaman: %d / %d  (Total Menu: %d)\n", currentPage, maxPage, jumlahMenu);
}

void lihatMenu() {
    applyColors();
    if (jumlahMenu == 0) {
        system("cls");
        printf("\n[INFO] Belum ada menu yang tersedia.\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    int pilihan;
    int maxPage = ((jumlahMenu - 1) / ITEMS_PER_PAGE) + 1;

    do {
        system("cls");
        printf("\n|=======================================|\n");
        printf("\n|          DAFTAR MENU                  |\n");
        printf("\n|=======================================|\n");

        tampilkanTabel(currentPage);

        printf("\n[1] Halaman Sebelumnya  [2] Halaman Selanjutnya  [0] Kembali\n");
        printf("Pilihan: ");

        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (pilihan == 1 && currentPage > 1) {
            currentPage--;
        } else if (pilihan == 2 && currentPage < maxPage) {
            currentPage++;
        }
    } while (pilihan != 0);

    currentPage = 1;
}






#endif //EATBOX_MENU_H