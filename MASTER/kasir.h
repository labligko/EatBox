#ifndef EATBOX_KASIR_H
#define EATBOX_KASIR_H

void kasir(char nama[50])
{
    system("cls");
    applyColors();appname(43, 1);
    garisx(0,8);
    garisy(25,8); // Garis Sidebar

    gotoxy(1,10); printf("Halo, %s", cutname(nama));
    gotoxy(1,20); printf(" [↕] Pilih Menu");

    int currentView = 0;

    char *menuSup[] = {
        " Data Karyawan", " Cari Karyawan", " Tambah Karyawan", " Ubah Karyawan", " Hapus Karyawan", " Keluar"
    };

    while(1)
    {
        int clearW = consoleW() - 27;
        int clearH = consoleH() - 9;
        clearArea(27, 9, clearW, clearH);
        clearinput(1,10,24);

        int totalData = 0;
        int maxPage = 1;

        if (currentView == 0) {
            dashboard(nama);
        }
        else if (currentView == 1) {
            totalData = lihatKar(); // Render tabel & dapatkan total data
            maxPage = (totalData == 0) ? 1 : (totalData - 1) / 20 + 1;

            // Render Footer Paging
            int bot = 34;
            gotoxy(29, bot+1);
            setRGBColor(202, 40, 44, 1);
            setRGBColor(251, 255, 199,0);
            printf("Halaman: %d / %d (Total: %d)   [<] Prev  [>] Next", currentPage, maxPage, totalData);
        }

        // 4. Handle Sidebar Title (Biar balik lagi kalo abis diganti submenu)
        if(currentView == 0) { gotoxy(1,10); printf("Halo, %s", cutname(nama)); }
        else if(currentView == 1) { gotoxy(1,10); printf("DATA KARYAWAN"); }

        // 5. Menu Select (Program Pauses Here)
        int pilih = menuSelect(1, 12, menuSup, 6);

        // 6. Logic Navigasi
        if (pilih == -1) { // Prev Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentPage > 1) currentPage--;
        }
        else if (pilih == -2) { // Next Page (Hanya jika di View Tabel)
            if (currentView == 1 && currentPage < maxPage) currentPage++;
        }
        else if (pilih == 0) { // DATA KARYAWAN
            currentView = 1;
            currentPage = 1;
        }
        else if (pilih == 1) { // CARI KARYAWAN
            detailKar();
            // Setelah search selesai, kembalikan tampilan
            currentView = 0; // Atau 1 terserah mau balik kemana
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 2) { // TAMBAH
            createKar(); // Masuk ke fungsi create, loop didalamnya, lalu return kesini
            currentView = 1; // Setelah tambah, tampilkan tabel
            // Fix Sidebar (karena createKar pakai sidebar buat helper)
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 3) { // UBAH
            updateKar();
            currentView = 1;
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 4) { // HAPUS
            hapusKar();
            currentView = 1;
            clearArea(1, 10, 24, 30); gotoxy(1,20); printf(" [↕] Pilih Menu");
        }
        else if (pilih == 5) { // KELUAR
            exit(0);
        }
    }
}


#endif //EATBOX_KASIR_H