#ifndef EATBOX_UPDATE_H
#define EATBOX_UPDATE_H
#include <stdio.h>
#include <string.h>
#include "../data.h"

int updateKaryawan(const Karyawan *dataBaru)
{
    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    FILE *temp = fopen("../FILE/temp.dat", "wb");

    if (!f || !temp) {
        if(f) fclose(f);
        if(temp) fclose(temp);
        return 0;
    }

    char str[512];
    Karyawan a;
    int found = 0;

    while (fgets(str, sizeof(str), f))
    {
        str[strcspn(str, "\n")] = 0;

        // Baca data lama
        sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               a.id, a.username, a.password, a.telp, a.email, a.role, a.alamat, &a.status);

        // Jika ID cocok, tulis DATA BARU ke file temp
        if (strcmp(a.id, dataBaru->id) == 0)
        {
            fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                dataBaru->id, dataBaru->username, dataBaru->password,
                dataBaru->telp, dataBaru->email, dataBaru->role,
                dataBaru->alamat, dataBaru->status);
            found = 1;
        }
        else
        {
            // Jika tidak cocok, tulis DATA LAMA (copy paste)
            fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                a.id, a.username, a.password, a.telp, a.email, a.role, a.alamat, a.status);
        }
    }

    fclose(f);
    fclose(temp);

    remove("../FILE/karyawan.dat");
    rename("../FILE/temp.dat", "../FILE/karyawan.dat");

    return found;
}
#endif