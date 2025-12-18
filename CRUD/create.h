#ifndef EATBOX_CREATE_H
#define EATBOX_CREATE_H
#include <stdio.h>
#include <string.h>

#include "../data.h"

void autoID(char *output, const char *format) {
    FILE *f = fopen("../FILE/karyawan.dat", "r"); // Mode read text
    int max = 0;
    char line[512];
    char tempID[50];

    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            if (sscanf(line, "%[^|]", tempID) == 1) {

                int num = 0;
                char *ptr = tempID;

                // 2. Logika lewati huruf (misal 'K', 'R') sampai ketemu angka
                // Ini biar fleksibel, mau ID-nya "KR001", "ADM005", tetap kebaca angkanya
                while (*ptr && !isdigit(*ptr)) {
                    ptr++;
                }

                // 3. Convert angka string ke integer
                if (*ptr) { // Pastikan pointer tidak null/habis
                    num = atoi(ptr);
                }

                // 4. Cari nilai terbesar
                if (num > max) {
                    max = num;
                }
            }
        }
        fclose(f);
    }
    sprintf(output, format, max + 1);
}
void createKaryawan(Karyawan a)
{
    autoID(a.id, "KY%03d");
    FILE *file = fopen("../FILE/karyawan.dat", "ab+");
    if (!file) return;

    // Format: ID|Username|Password|NAMA|Telp|Email|Role|Alamat|Status
    fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s|%d\n",
            a.id, a.username, a.password, a.nama, a.telp,
            a.email, a.role, a.alamat, a.status);

    fclose(file);
}

#endif //EATBOX_CREATE_H