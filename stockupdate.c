#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int stockupdate() {
    printf("=========================== INPUT/EDIT ==========================\n");

    FILE *stok;
    stok = fopen("stok.dat", "rb+");
    struct stok stokdata = {0, 0, 0};

    while(1) {
        printf("Masukkan kode barang (0 untuk selesai)\n? ");
        scanf("%d", &stokdata.kode);
        if (stokdata.kode <= 0) {
            break;
        }

        printf("Masukkan jumlah stok dan harga jual barang\n? ");
        scanf("%d %d", &stokdata.jumlah, &stokdata.hargajual);
        fseek(stok, (stokdata.kode - 1)*sizeof(struct stok), SEEK_SET);
        fwrite(&stokdata, sizeof(struct stok), 1, stok);
    }
    printf("Stok barang di-update.\nTekan enter untuk kembali ke menu awal ...\n");
    _getch();
    fclose(stok);
}
