#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int getdata() {
    FILE *master, *stock;
    master = fopen("masterbarang.dat", "rb");
    stock = fopen("stok.dat", "rb");
    struct masterbarang mstr = {0, "", 0};
    struct stok stk = {0, 0, 0};

    if ((master == NULL) || (stock == NULL)) {
        printf("Couldn't load file");
    } else {
        printf("======================== DATA BARANG =========================\n");
        printf("|%-5s |%-25s |%-9s |%-9s |%-5s|\n", "Kode", "Barang", "Hrg Jual", "Hrg Beli", "Stock");
        printf("|-------------------------------------------------------------|\n");
        int index = 0;
        while (!feof(master)) {
            fread(&mstr, sizeof(struct masterbarang), 1, master);
            fread(&stk, sizeof(struct stok), 1, stock);
            if (mstr.kode != index) {
                printf("|%-5d |%-25s |%-9d |%-9d |%-5d|\n", mstr.kode, mstr.nama, stk.hargajual, mstr.hargabeli, stk.jumlah);
                index = mstr.kode;
            }
        }
        printf(" =============================================================\n");
    }
    printf("Tekan enter untuk kembali ...\n");
    _getch();
    fclose(master);
    fclose(stock);
}
