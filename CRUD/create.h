#ifndef EATBOX_CREATE_H
#define EATBOX_CREATE_H
#include <stdio.h>
#include <string.h>

#include "../data.h"

void autoID(char *output, const char *format) {
    FILE *f = fopen("../FILE/id.dat", "rb");
    int lastNum = 0;

    if (f) {
        fscanf(f, "%d", &lastNum);
        fclose(f);
    }

    lastNum++;

    f = fopen("../FILE/id.dat", "wb");
    fprintf(f, "%d", lastNum);
    fclose(f);

    sprintf(output, format, lastNum);
}

void createKaryawan(Karyawan a)
{
    autoID(a.id, "KY%03d");

    FILE *file = fopen("../FILE/karyawan.dat", "ab+");

    if (!file) {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%d|%d\n",
            a.id, a.username, a.password, a.telp,
            a.email, a.role, a.alamat, a.status, a.poin);

    fclose(file);
}

#endif //EATBOX_CREATE_H