#ifndef EATBOX_DELETE_H
#define EATBOX_DELETE_H
#include <stdio.h>
#include <string.h>
#include "../data.h"

int deleteKaryawan(char idTarget[])
{
    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    FILE *temp = fopen("../FILE/temp.dat", "wb");
    if (!f || !temp) { if(f) fclose(f); if(temp) fclose(temp); return 0; }

    char str[512];
    Karyawan a;
    int found = 0;

    while (fgets(str, sizeof(str), f))
    {
        str[strcspn(str, "\n")] = 0;
        sscanf(str, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
               a.id, a.username, a.password, a.nama, a.telp,
               a.email, a.role, a.alamat, &a.status);

        if (strcmp(idTarget, a.id) == 0) {
            a.status = 0; // UBAH JADI NON-AKTIF (Soft Delete)
            found = 1;
        }

        fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%s|%d\n",
                a.id, a.username, a.password, a.nama, a.telp,
                a.email, a.role, a.alamat, a.status);
    }
    fclose(f); fclose(temp);
    remove("../FILE/karyawan.dat");
    rename("../FILE/temp.dat", "../FILE/karyawan.dat");
    return found;
}
#endif
