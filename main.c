#include <stdio.h>
#include <stdlib.h>
#include "include/function.h"
#include "include/login.h"
#include "include/master/karyawan/kasir.h"
#include "include/master/karyawan/manajer.h"
#include "include/master/karyawan/staff.h"
#include "include/master/karyawan/superadmin.h"

int main(void)
{
    startupSequence();
    char nama[50];
    int role;
    system("chcp 65001 > nul"); //ini buat baca UFT-8

    while (1) {
        role = login(nama);

        if (role == 1) supadm(nama);
        else if (role == 2) staff(nama);
        else if (role == 3) manajer(nama);
        else if (role == 4) kasir(nama);
    }

    printf("\x1b[0m");
    getchar();
    return 0;
}
