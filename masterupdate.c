#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int masterupdate() {
    printf("=========================== INPUT/EDIT/ ==========================\n");
    struct masterbarang data = {0, "", 0};
    FILE *master;
    master = fopen("masterbarang.dat", "rb+");

    while(1) {
        printf("Masukkan kode barang (0 untuk selesai)\n? ");
        scanf("%d", &data.kode);
        if (data.kode <= 0) {
            break;
        }

        printf("Masukkan nama barang dan harga beli barang\n? ");
        scanf("%s %d", data.nama, &data.hargabeli);
        fseek(master, (data.kode - 1)*sizeof(struct masterbarang), SEEK_SET);
        fwrite(&data, sizeof(struct masterbarang), 1, master);
    }
    printf("Master barang di-update.\nTekan enter untuk kembali ke menu awal ...\n");
    _getch();
    fclose(master);
}
