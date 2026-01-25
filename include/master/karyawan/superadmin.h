#ifndef PERAPIHAN_SUPERADMIN_H
#define PERAPIHAN_SUPERADMIN_H

void createKar();
void updateKar();
void hapusKar();
void detailKar();
int lihatKar();
void dashboard(char *nama);
void supadm(char nama[50]);
void formEdit(Karyawan *a);
int finID(int targetNo, char *destID);
int gantiPass(char *passAwal);

void autoID(char *output, const char *format);
void createKaryawan(Karyawan a);
int deleteKaryawan(char idTarget[]);
int updateKaryawan(const Karyawan *dataBaru);
int dataKaryawan(int left, int startY, int page);

#endif //PERAPIHAN_SUPERADMIN_H