#ifndef PERAPIHAN_FUNCTION_H
#define PERAPIHAN_FUNCTION_H
#include "../include/data.h"

#define INPUT_ESC     0
#define INPUT_OK      1
#define INPUT_LEFT   -1
#define INPUT_RIGHT  -2

typedef int (*CharFilter)(char ch);

DateTime now();
int hariIni(DateTime d);
void formatTanggal(DateTime d, char *out);
void formatJam(DateTime d, char *out);
void formatTanggalJam(DateTime d, char *out);

// FUNGSI UTILITY DASAR
void gotoxy(int x, int y);
int consoleW();
int consoleH();
void appname(int x, int y);
void logname(int x, int y);

void Borderless();
void enableANSI();
void setRGBColor(int r, int g, int b, int isBackground);
void fillScreenBG();
void applyColors();
void Fullscreen();
void maximizeConsole();
void fixConsoleBuffer();
void warna();
void startupSequence();

void garisx(int x, int y);
void garisy(int x, int y);

void clearinput(int x, int y, int l);
void inputpasslog(char pass[], int x, int y, char *ouput);
int inputusname(char input[]);
int inputpass(char pass[], int x, int y, char *ouput);
int inputtext(char input[]);
int inputid(char input[]);
int inputTelp08(char *input);
int inputbebas(char input[]);
int inputName(char input[]);
int inputField(char input[]);

void frame(int left, int top, int right, int bot);
char *cutname(char nama[]);
int cekEmail(char *s);
int cekrole(char *r);
int onlyNum(char *s);
int isDuplicate(char *jenis, char *isiData, char *idPengecualian);

void resetColor();
void showcurs();
void clearArea(int x, int y, int width, int height);
int menuSelect(int x, int y, char *menu[], int count);

int popupConfirm(char *msg, char *pesan1, char *pesan2);
void popupAlert(int code, char *msg);

void drawGantiPassBox(int x, int y, int w, int h);

int stringCek(char *mainStr, char *subStr);
int getNamaKasir(const char* id, char* outNama);
int getMenuByID(const char *id, Menu *out);

char* formatHarga(double harga);

#endif //PERAPIHAN_FUNCTION_H