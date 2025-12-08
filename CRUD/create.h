#ifndef EATBOX_CREATE_H
#define EATBOX_CREATE_H
#include <stdio.h>
#include <string.h>

#include "../data.h"

void autoID(char *output, char tipe[]) {
    FILE *f;
    int lastNum = 0;

    f = fopen("akun.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d", &lastNum);
        fclose(f);
    }
    lastNum++;

    f = fopen("akun.txt", "w");
    fprintf(f, "%d", lastNum);
    fclose(f);

    sprintf(output, tipe, lastNum);
}

void createAkun(Akun a)
{
    char idAkun[20];
    autoID(idAkun, "KRY%03d");

    FILE *file = fopen("akun.dat", "ab+");

    if (!file) {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(file, "%s|%s|%s|%s|%s|%s|%d|%d\n",
            idAkun, a.username, a.password, a.telp,
            a.email, a.role, a.status, a.poin);

    fclose(file);
}

#endif //EATBOX_CREATE_H