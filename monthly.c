#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int monthly() {
    printf(" ========================= LAPORAN BULANAN ========================\n");
    int year, month;
    int modal = 0, masuk = 0, laba = 0, brgterjual = 0;

    printf("Laporan tahun : ");
    scanf("%d", &year);
    printf("Bulan ke : ");
    scanf("%d", &month);

    FILE *report;
    report = fopen("laporan.dat", "wb+");

    FILE *master;
    master = fopen("masterbarang.dat", "rb");
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

    //get transaction according to inputs
    int arr = count;
    int sold[arr];
    int i;
    for (i=1; i < arr; i++) {
    	sold[i] = 0;
	}
    max = 10;
    count = 1;
    FILE *history;
    history = fopen("histori.dat", "rb");
    struct history histori = {"", 0, 0, 0, 0, 0, 0, 0, 0};
    struct history* histdata = calloc(max, sizeof(struct history));
    while (!feof(history)) {
        fread(&histori, sizeof(struct history), 1, history);
        if ((histori.year == year) && (histori.month == month)) {
            histdata[count] = histori;
            count++;
        }
        if (count >= max) {
            max = max + 10;
            histdata = realloc(histdata, max*sizeof(struct history));
        }
    }

    //display history
    printf(" ======================== RIWAYAT %d-%d ==========================\n", year, month);
    printf("| %-2s-%-2s-%-4s | %-10s | %-5s | %-23s | %-5s|\n", "T", "B", "Thn", "Customer", "Kode", "Barang", "Qty");
    printf("|------------------------------------------------------------------|\n");
    int index = 0;
    for (i=1; i < count; i++) {
        if (histdata[i].kode != index) {
            printf("| %-2d-%-2d-%-4d | %-10s | %-5d | %-23s | %-5d|\n", histdata[i].day, histdata[i].month, histdata[i].year, histdata[i].nama,
            histdata[i].kode, mstr[histdata[i].kode].nama, histdata[i].qty);
            modal = modal + (histdata[i].hargabeli*histdata[i].qty);
            masuk = masuk + (histdata[i].hargajual*histdata[i].qty);
            brgterjual = brgterjual + histdata[i].qty;
            index = histdata[i].kode;
            sold[histdata[i].kode] = sold[histdata[i].kode] + histdata[i].qty;
        }
    }
    printf(" ------------------------------------------------------------------\n\n");

    printf("============================ INSIGHT ==============================\n");
    laba = masuk - modal;
    printf("Jumlah barang terjual   : %d\n", brgterjual);
    printf("Modal                   : Rp%d\n", modal);
    printf("Pemasukan               : Rp%d\n", masuk);
    if (laba >= 0) {
    	printf("Keuntungan/Laba		: Rp%d\n", laba);
	} else {
		printf("Rugi			: Rp%d\n", abs(laba));
	}
    printf("===================================================================\n");
    
    printf(" =========================== RINCIAN =============================\n");
    printf("| %-13s | %-32s | %13s|\n", "Kode", "Barang", "Terjual");
    printf(" -----------------------------------------------------------------\n");
    for (i=1; i < arr; i++) {
    	if (sold[i] != 0) {
    		printf("| %-13d | %-32s | %13d|\n", i, mstr[i].nama, sold[i]);
		}
	}
	printf(" -----------------------------------------------------------------\n\n");

    int chs;
    printf("Cetak laporan ?\n(1 untuk ya/0 untuk kembali) ");
    scanf("%d", &chs);
    if (chs == 1) {
        fprintf(report, " ==================================================================\n");
        fprintf(report, "|                            TRIAL TOKO                            |\n");
        fprintf(report, "|------------------------------------------------------------------|\n");
        fprintf(report, "|                      Final Project Daspro B                      |\n");
        fprintf(report, "|                        051_Hanun Shaka P                         |\n");
        fprintf(report, " ==================================================================\n\n");
        fprintf(report, " ========================= RIWAYAT %d-%d =========================\n", year, month);
        fprintf(report, "| %-2s-%-2s-%-4s | %-10s | %-5s | %-23s | %-5s|\n", "T", "B", "Thn", "Customer", "Kode", "Barang", "Qty");
        fprintf(report, "|------------------------------------------------------------------|\n");
        int index = 0;
        int i;
        for (i=1; i < count; i++) {
            if (histdata[i].kode != index) {
                fprintf(report, "| %-2d-%-2d-%-4d | %-10s | %-5d | %-23s | %-5d|\n", histdata[i].day, 
                histdata[i].month, histdata[i].year, histdata[i].nama,
                histdata[i].kode, mstr[histdata[i].kode].nama, histdata[i].qty);
            }
        }
        fprintf(report, " ------------------------------------------------------------------\n\n");
        fprintf(report, "============================ INSIGHT ===============================\n");
        fprintf(report, "Jumlah barang terjual   : %d\n", brgterjual);
        fprintf(report, "Modal                   : Rp%d\n", modal);
        fprintf(report, "Pemasukan               : Rp%d\n", masuk);
        if (laba >= 0) {
    		fprintf(report, "Keuntungan/Laba         : Rp%d\n", laba);
		} else {
			fprintf(report, "Rugi					: Rp%d\n", abs(laba));
		}
        fprintf(report, "====================================================================\n");
        fprintf(report, " =========================== RINCIAN =============================\n");
	    fprintf(report, "| %-13s | %-32s | %13s|\n", "Kode", "Barang", "Terjual");
    	fprintf(report, " -----------------------------------------------------------------\n");
    	for (i=1; i < arr; i++) {
    		if (sold[i] != 0) {
    			fprintf(report, "| %-13d | %-32s | %13d|\n", i, mstr[i].nama, sold[i]);
			}
		}
		fprintf(report, " -----------------------------------------------------------------\n\n");
        printf("Berhasil mencetak laporan.\n");
    }
    printf("Selesai menampilkan laporan, tekan enter untuk kembali ...\n");
    _getch();
    fclose(report);
    fclose(history);
    fclose(master);
}
