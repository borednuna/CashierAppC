#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int catalogue() {
    printf("============================ KATALOG ==============================\n");
    FILE *master, *stok;
    struct masterbarang masterdata = {0, "", 0};
    struct stok stokdata = {0, 0, 0};
    stok = fopen("stok.dat", "rb");
    master = fopen("masterbarang.dat", "rb");

    if ((master == NULL) || (stok == NULL)) {
        printf("Couldn't load data\n");
    } else {
        int index = 0;
        printf("-------------------------------------------------------------------\n");
        printf("| %-10s| %-30s| %-20s|\n", "Kode", "Nama Barang", "Harga Barang");
        printf("-------------------------------------------------------------------\n");
        while (!feof(master)) {
            fread(&masterdata, sizeof(struct masterbarang), 1, master);
            fread(&stokdata, sizeof(struct stok), 1, stok);
            if ((masterdata.kode != index) && (masterdata.kode != 0)) {
                printf("| %-10d| %-30s| Rp%-18d|\n", masterdata.kode, masterdata.nama, stokdata.hargajual);
                index = masterdata.kode;
            }
        }
        printf("-------------------------------------------------------------------\n");
        fclose(master);
        fclose(stok);
        printf("Tekan enter untuk kembali ...\n");
        _getch();
    }
}
