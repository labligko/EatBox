#ifndef EATBOX_DELETE_H
#define EATBOX_DELETE_H
#include <stdio.h>
#include <string.h>
#include "../data.h"

int deleteKaryawan(char idTarget[])
{
    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    FILE *temp = fopen("../FILE/temp.dat", "wb");

    if (!f || !temp) {
        // printf("Error membuka file!"); // Opsional
        if(f) fclose(f);
        if(temp) fclose(temp);
        return 0;
    }

    char str[512]; // Buffer digedein dikit biar aman
    Karyawan a;
    int found = 0;

    while (fgets(str, sizeof(str), f))
    {
        str[strcspn(str, "\n")] = 0; // Hapus newline

        // [FIX] Tambahkan PASSWORD (total 8 kolom)
        sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               a.id, a.username, a.password, a.telp, a.email, a.role, a.alamat, &a.status);

        if (strcmp(idTarget, a.id) == 0)
        {
            found = 1;
            continue; // Skip (Data dihapus)
        }

        // [FIX] Tulis ulang lengkap 8 kolom
        fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                a.id, a.username, a.password, a.telp, a.email, a.role, a.alamat, a.status);
    }

    fclose(f);
    fclose(temp);

    remove("../FILE/karyawan.dat");
    rename("../FILE/temp.dat", "../FILE/karyawan.dat");

    return found;
}
#endif