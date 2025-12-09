#ifndef EATBOX_DELETE_H
#define EATBOX_DELETE_H
#include <stdio.h>
#include <string.h>

#include "../data.h"

int deleteKaryawan(char idTarget[])
{
    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    FILE *temp = fopen("../FILE/temp.dat", "wb");

    if (!f||!temp)
    {
        printf("Error membuka file!");
        return 0;
    }
    char str[300];
    Karyawan a;
    int found =0;
    while (fgets(str,300,f))
    {
        sscanf(str,
            "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d",
            a.id, a.username, a.telp, a.email, a.alamat, a.role, &a.status
        );

        if (strcmp(idTarget, a.id) == 0)
        {
            found = 1;
            continue;
        }
        fprintf(temp, "%s|%s|%s|%s|%s|%s|%d\n",
                a.id, a.username, a.telp, a.email, a.alamat, a.role, a.status);
    }

    fclose(f);
    fclose(temp);
    remove("../FILE/karyawan.dat");
    rename("../FILE/temp.dat", "../FILE/karyawan.dat");

    if (found)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#endif //EATBOX_DELETE_H