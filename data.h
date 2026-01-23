#ifndef EATBOX_DATA_H
#define EATBOX_DATA_H
#include <stdint.h>
#include <time.h>

typedef char text[255];
typedef struct
{
    int tahun, bulan, hari;
    int jam, menit, detik;
}DateTime;
typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGBColor;

DateTime now() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    DateTime d;
    d.hari = tm->tm_mday;
    d.bulan = tm->tm_mon + 1;
    d.tahun = tm->tm_year + 1900;
    d.jam = tm->tm_hour;
    d.menit = tm->tm_min;
    d.detik = tm->tm_sec;
    return d;
}
int hariIni(DateTime d)
{
    DateTime sekarang = now();
    return d.hari == sekarang.hari && d.bulan == sekarang.bulan && d.tahun == sekarang.tahun;
}

//YANG BARU
//MASTER
typedef struct
{
    char id[10];
    char username[20];
    char password[35];
    char nama[50];
    char telp[15];
    char email[50];
    char role[20];
    text alamat;
    int status;
}Karyawan;

typedef struct
{
    char id_menu[10];
    char kategori[20];
    char nama_menu[100];
    double harga;
    text deskripsi;
    int keterangan; //buat keterangan tersedia dll
    int status;
}Menu;

typedef struct
{
    char id_bahan[10];
    char nama_bahan[50];
    int stok;
    char satuan[20];
    int minimal_stok;
    int status; // buat status aktif/gk
}BahanBaku;

typedef struct {
    char id_menu[10];
    char id_bahan[10];
    int jumlah; // pemakaian per 1 menu
} ResepMenu;

typedef struct
{
    char id_meja[10];
    int nomor_meja; // nomor fisik meja
    int kapasitas;
    int keterangan; // 1=Kosong, 2=Terisi
    int status;     // 1=Aktif, 0=Rusak
}Meja;

//TRANSAKSI
typedef struct
{
    char id_pesan[10];   // ORDER NUMBER
    char id_akun[10];    // kasir
    char id_meja[10];    // ambil data meja nya
    int no_meja;         // 0 = take away
    double total;        // hasil akumulasi detail
    char status[20];     // Menunggu Bayar / Lunas / Selesai
    DateTime tanggal;
}Pesanan;

typedef struct
{
    char id_pesan[10];   // relasi ke Pesanan
    char id_menu[10];
    int jumlah;
    double subtotal;
}DetailPesanan;

typedef struct
{
    char id_bayar[10];
    char id_pesan[10];
    char id_akun[10];
    DateTime tanggal;
    double jumlah;
    double bayar;
    int metode_bayar;
    char status[20];
}Pembayaran;

extern Menu daftarMenu[100];
int jumlahMenu = 0;

BahanBaku daftarBahan[100]; // Array global
int totalBahan = 0;         // Counter global
ResepMenu daftarResep[500];
int totalResep;
#define FILE_RESEP "../FILE/resep_menu.dat"

extern char currentKasirID[10];
char listPesanHariIni[100][15];
int totalPesanHariIni = 0;
void formatTanggal(DateTime d, char *out)
{
    sprintf(out, "%02d/%02d/%04d", d.hari, d.bulan, d.tahun);//print string sampai batas (abaikan buffer)
}
void formatJam(DateTime d, char *out)
{
    snprintf(out, 6, "%02d:%02d", d.jam, d.menit);//print string sampai batas (abaikan buffer)
}

#endif //EATBOX_DATA_H