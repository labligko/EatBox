#include <stdio.h>
#include <stdlib.h>
#include "include/function.h"
#include "include/login.h"

int main(void)
{
    startupSequence();
    char nama[50], pass[50];
    system("chcp 65001 > nul"); //ini buat baca UFT-8

    login(nama, pass);

    printf("\x1b[0m");
    getchar();
    return 0;
}