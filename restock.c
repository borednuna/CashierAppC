#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int restock() {
    FILE *stok;
    stok = fopen("stok.dat", "rb+");
    struct stok tempstk = {0, 0, 0};
    int add;

    //allocate memory and input data from file stok.dat
    int max = 10;
    int count = 1;
    struct stok* stk = calloc(max, sizeof(struct stok));
    while (!feof(stok)) {
        fread(&stk[count], sizeof(struct stok), 1, stok);
        count++;
        if (count == max) {
            max = max + 10;
            stk = realloc(stk, max*sizeof(struct stok));
        }
    }

    printf(" ============================= RESTOCK ============================\n");
    while (1) {
        printf("Kode barang yang akan direstock :\n? (0 atau angka negatif untuk berhenti)");
        scanf("%d", &tempstk.kode);
        if (tempstk.kode <= 0) {
            break;
        }

        printf("Restock sebanyak :\n?");
        scanf("%d", &add);
        tempstk.jumlah = stk[tempstk.kode].jumlah + add;
        tempstk.hargajual = stk[tempstk.kode].hargajual;

        fseek(stok, (tempstk.kode - 1)*sizeof(struct stok), SEEK_SET);
        fwrite(&tempstk, sizeof(struct stok), 1, stok);
    }
    fclose(stok);
    printf("Restock berhasil !\nTekan enter untuk kembali ...\n");
    _getch();
}
