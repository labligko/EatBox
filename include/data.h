#ifndef PERAPIHAN_DATA_H
#define PERAPIHAN_DATA_H
#include <stdint.h>

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
}ResepMenu;
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
extern int jumlahMenu;

extern BahanBaku daftarBahan[100]; // Array global
extern int totalBahan;         // Counter global

extern ResepMenu daftarResep[100];
extern int totalResep;

extern char currentKasirID[10];
extern char listPesanHariIni[100][15];
extern int totalPesanHariIni;

extern int totalMeja;
extern Meja daftarMeja[50];
extern int jumlahMeja;
static int currentpage =1;

extern int left, right, top, bot;

extern char namaKasir[50];
extern char keyword[50];
extern int searchMode;

#define FILE_TEMP       "../file/temp.dat"
#define FILE_KARYAWAN   "../file/karyawan.dat"
#define FILE_RESEP      "../file/resep_menu.dat"
#define FILE_PEMBAYARAN "../file/pembayaran.dat"
#define FILE_PESANAN    "../file/pesanan.dat"
#define FILE_DETAIL     "../file/detail_pesanan.dat"
#define FILE_MEJA       "../file/meja.dat"
#define FILE_MENU       "../file/menu.dat"
#define FILE_BAHAN      "../file/bahan.dat"

void injectUserUtama();
void injectDummyKaryawan();
void injectDummyMeja();
void injectDummyMenu();
void injectDummyBahan();
void injectDummyResep();

#endif //PERAPIHAN_DATA_H