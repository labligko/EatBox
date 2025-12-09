#ifndef EATBOX_UPDATE_H
#define EATBOX_UPDATE_H

int updateKaryawan(const Karyawan *a)
{
    FILE *f = fopen("../FILE/karyawan.dat", "rb");
    if (!f) return 0;

    Karyawan list[500];
    int count = 0, found = -1;

    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n",
              list[count].id,
              list[count].username,
              list[count].password,
              list[count].telp,
              list[count].email,
              list[count].role,
              list[count].alamat,
              &list[count].status,
              &list[count].poin) != EOF)
    {
        if (strcmp(list[count].id, a->id) == 0)
            found = count;

        count++;
    }
    fclose(f);

    if (found == -1) return 0;

    // --- Update data lama ---
    list[found] = *a;

    // --- Write ulang file ---
    f = fopen("../FILE/karyawan.dat", "wb");
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s|%s|%s|%s|%s|%s|%s|%d|%d\n",
            list[i].id,
            list[i].username,
            list[i].password,
            list[i].telp,
            list[i].email,
            list[i].role,
            list[i].alamat,
            list[i].status,
            list[i].poin);
    }
    fclose(f);

    return 1;
}

#endif
