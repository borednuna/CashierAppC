#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headertoko.h"

int main() {
	while(1) {
		getheader();
		getmenu();
		int chs;
		scanf("%d", &chs);
		if (chs == 1) {
			catalogue();
		} else if (chs == 2) {
			while (1) {
				int chs1;
	            printf(" ========================== MENU BARANG =============================\n");
    	        printf("1. Update master barang\n");
        	    printf("2. Update stok barang\n");
            	printf("3. Tampilkan data barang\n");
            	printf("4. Restock\n");
            	printf("5. Kembali\n");
    	        printf("Pilih : (1/2/3/4/5) ");
        	    scanf("%d", &chs1);
            	if (chs1 == 1) {
                	masterupdate();
	            } else if (chs1 == 2) {
    	            stockupdate();
        	    } else if (chs1 == 3) {
            	    getdata();
	            } else if (chs1 == 4) {
    	        	restock();
				} else if (chs1 == 5) {
					break;
				} else {
            	    printf("Don't get lost ...\n");
                	_getch();
            	}
			}
		} else if (chs == 3) {
			dotrans();
		} else if (chs == 4) {
			printf(" ========================== MENU LAPORAN =============================\n");
            printf("1. Laporan Mingguan\n");
            printf("2. Laporan Bulanan\n");
            printf("3. Laporan Tahunan\n");
            printf("4. Kembali\n");
            int chs2;
            printf("Pilih menu : (1/2/3) ");
            scanf("%d", &chs2);
            if (chs2 == 1) {
            	weekly();
			} else if (chs2 == 2) {
				monthly();
			} else if (chs2 == 3) {
				yearly();
			} else if (chs2 == 4) {
				continue;
			} else {
				printf("Don't get lost buddy ...\n");
				_getch();
			}
		} else if (chs == 5) {
			break;
		} else {
			printf("Don't get lost my friend ...\n");
			_getch();
		}
	}
}

void getheader()
{
    printf(" ==================================================================\n");
    printf("|                           TOKO RAKYAT                            |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("|                      Final Project Daspro B                      |\n");
    printf("|                        051_Hanun Shaka P                         |\n");
    printf(" ==================================================================\n\n");
}

void getmenu()
{
	printf(" ========================== MAIN MENU =============================\n");
    printf("1. Tampilkan katalog\n");
    printf("2. Update barang\n");
    printf("3. Buat transaksi\n");
    printf("4. Tampilkan laporan\n");
    printf("5. Keluar\n\n");
    printf("Pilih menu : ");
}
