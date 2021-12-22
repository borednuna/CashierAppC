#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int dotrans() {
    // get time
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);

    //open files
    FILE *histori, *struk, *master, *stok;
    histori = fopen("histori.dat", "rb+");
    struk = fopen("struk.dat", "wb+");
    master = fopen("masterbarang.dat", "rb");
    stok = fopen("stok.dat", "rb+");

    //allocate memory and input data from file masterbarang.dat
    int max = 10;
    int count = 1;
    struct masterbarang* mstr = calloc(max, sizeof(struct masterbarang));
    while (!feof(master)) {
        fread(&mstr[count], sizeof(struct masterbarang), 1, master);
        count++;
        if (count == max) {
            max = max + 10;
            mstr = realloc(mstr, max*sizeof(struct masterbarang));
        }
    }

    //allocate memory and input data from file stok.dat
    max = 10;
    count = 1;
    struct stok* stk = calloc(max, sizeof(struct stok));
    while (!feof(stok)) {
        fread(&stk[count], sizeof(struct stok), 1, stok);
        count++;
        if (count == max) {
            max = max + 10;
            stk = realloc(stk, max*sizeof(struct stok));
        }
    }

    //variables declaration
    struct stok tempstk = {0, 0, 0};
    char cust[100];
    int total = 0, tunai = 0, kembali = 0;

    //start transaction and fprintf struk.dat simultaneously
    printf(" ============================ TRANSAKSI ===========================\n");
    printf("Nama Customer\n?");
    scanf("%s", cust);

    fprintf(struk, " ==================================================================\n");
    fprintf(struk, "|                            TRIAL TOKO                            |\n");
    fprintf(struk, "|------------------------------------------------------------------|\n");
    fprintf(struk, "|                      Final Project Daspro B                      |\n");
    fprintf(struk, "|                        051_Hanun Shaka P                         |\n");
    fprintf(struk, " ==================================================================\n\n");

    fprintf(struk, "Customer : %s\n", cust);
    fprintf(struk, "%s", asctime(ptr));
    fprintf(struk, "--------------------------------------------------------------------\n");
    fprintf(struk, " %-20s %-10s %-15s %-15s\n", "Nama Brg", "qty", "Harga Satuan", "Harga Total");
    fprintf(struk, "--------------------------------------------------------------------\n");

    while (1) {
        //input barang
        struct history trans = {"", 0, 0, 0, 0, 0, 0, 0, 0};
        strcpy(trans.nama, cust);
        printf("Kode Barang : (0 untuk selesai)\n");
        scanf("%d", &trans.kode);
        if (trans.kode == 0) {
            break;
        }

        //cek kode barang
        if ((trans.kode > count) || (mstr[trans.kode].kode == 0)) {
            printf("Barang tidak terdaftar !\n");
            continue;
        }

        //input keterangan barang
        printf("Qty :\n");
        scanf("%d", &trans.qty);
        trans.year = ptr->tm_year+1900;
        trans.month = ptr->tm_mon+1;
        trans.week = (ptr->tm_mday/7)+1;
        trans.day = (ptr->tm_mday);

        //cek stok
        if (trans.qty > stk[trans.kode].jumlah) {
            printf("Stok %s hanya tersisa %d !\n", mstr[trans.kode].nama, stk[trans.kode].jumlah);
            continue;
        }

        //proses data
        trans.hargabeli = mstr[trans.kode].hargabeli;
        trans.hargajual = stk[trans.kode].hargajual;
        int totalqty = trans.hargajual*trans.qty;
        total = total + totalqty;

        //cetak tiap item ke struk.dat
        fprintf(struk, " %-20s  %-10d  %-15d %-15d\n", mstr[trans.kode].nama, trans.qty, stk[trans.kode].hargajual, totalqty);

        //update stok
        tempstk.kode = stk[trans.kode].kode;
        tempstk.jumlah = stk[trans.kode].jumlah - trans.qty;
        tempstk.hargajual = stk[trans.kode].hargajual;
        fseek(stok, (tempstk.kode - 1)*sizeof(struct stok), SEEK_SET);
        fwrite(&tempstk, sizeof(struct stok), 1, stok);

        //catat dalam histori transaksi
        fseek(histori, 0, SEEK_END);
        fwrite(&trans, sizeof(struct history), 1, histori);
    }
    //pembayaran
    bayar:
    printf("Total : Rp%d\n", total);
    printf("Tunai : Rp");
    scanf("%d", &tunai);
    kembali = tunai - total;
    if (kembali < 0) {
        printf("Bayar tunai kurang Rp%d\n", abs(kembali));
        goto bayar;
    }
    printf("Kembali : Rp%d\n", kembali);
    printf("Transaksi selesai !\n");

    fprintf(struk, "====================================================================\n");
    fprintf(struk, "Total       : Rp%d\n", total);
    fprintf(struk, "Bayar       : Rp%d\n", tunai);
    fprintf(struk, "Kembali     : Rp%d\n", kembali);
    fprintf(struk, "====================================================================\n");
    fprintf(struk, "    Barang yang sudah dibeli tidak dapat dikembalikan atau ditukar\n");
    fprintf(struk, "            Terima Kasih atas kunjungan Anda, %s :D\n", cust);
    fprintf(struk, "********************************************************************\n");

    fclose(histori);
    fclose(struk);
    fclose(master);
    fclose(stok);

    printf("Tekan enter untuk kembali ...\n");
    _getch();
}
