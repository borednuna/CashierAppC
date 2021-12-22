//struct masterbrg
struct masterbarang 
{
    int kode;
    char nama[100];
    int hargabeli;
};

//struct stok
struct stok
{
    int kode;
    int hargajual;
    int jumlah;
};

//struct data
struct databrg
{
    int kode;
    char nama[100];
    int hargabeli;
    int hargajual;
    int jumlah;
};

//struct histori
struct history
{
    char nama[100];
    int kode;
    int qty;
    int hargajual;
    int hargabeli;
    int year;
    int month;
    int week;
    int day;
};

int catalogue();
int dotrans();
int getdata();
int masterupdate();
int stockupdate();
int monthly();
int restock();
int weekly();
int yearly();

/*Baris berikutnya adalah fungsi-fungsi bantuan
saat membangun program ini

//cetak kop
void getheader()
{
    printf(" ==================================================================\n");
    printf("|                            TRIAL TOKO                            |\n");
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
    printf("3. Restock barang\n");
    printf("4. Buat transaksi\n");
    printf("5. Tampilkan laporan\n");
    printf("6. Keluar\n\n");
    printf("Pilih menu : ");
}

//tampilkan file masterbarang
void viewmstr()
{
    getheader();
    printf("======================= MASTER BARANG =========================\n");
    struct masterbarang data = {0, "", 0};
    FILE *master;
    master = fopen("masterbarang.dat", "rb");

    if (master == NULL) {
        printf("Can't load file\n");
    } else {
        int index;
        printf("%-10s %-30s %-10s\n", "Kode", "Nama Brg", "Harga Beli");
        while (!feof(master)) {
            fread(&data, sizeof(struct masterbarang), 1, master);
            if ((data.kode != 0) && (data.kode != index)) {
                printf("%-10d %-30s Rp%-10d\n", data.kode, data.nama, data.hargabeli);
                index = data.kode;
            }
        }
        printf("===============================================================\n");
        fclose(master);
        printf("Tekan enter untuk kembali . . .");
        _getch();
    }
}

//tampilkan file stok
void viewstok()
{
    getheader();
    printf("============================ STOK =============================\n");
    struct stok stokdata = {0, 0, 0};
    FILE *stok;
    stok = fopen("stok.dat", "rb");

    if (stok == NULL) {
        printf("Can't load file\n");
    } else {
        int index;
        printf("%-10s %-30s %-10s\n", "Kode", "Jml Stok", "Hrg Jual");
        while (!feof(stok)) {
            fread(&stokdata, sizeof(struct stok), 1, stok);
            if ((stokdata.kode != 0) && (stokdata.kode != index)) {
                printf("%-10d %-30d Rp%-10d\n", stokdata.kode, stokdata.jumlah, stokdata.hargajual);
                index = stokdata.kode;
            }
        }
        printf("===============================================================\n");
        fclose(stok);
        printf("Tekan enter untuk kembali . . .");
        _getch();
    }
}

//1 kali transaksi
void addtrans()
{
    // get time
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    //printf("\n%s\n", asctime(ptr));

    //open file
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
    getheader();
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
        printf("Qty, tahun, bulan, minggu, hari :\n");
        scanf("%d %d %d %d %d", &trans.qty, &trans.year, &trans.month, &trans.week, &trans.day);

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
}

//tampilkan riwayat
void viewhistory()
{
    getheader();
    printf("============================ HISTORI ==============================\n");
    struct history rwyt = {"", 0, 0, 0, 0, 0, 0, 0, 0};
    FILE *histori, *master;
    histori = fopen("histori.dat", "rb");
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

    if (histori == NULL) {
        printf("Can't load file\n");
    } else {
        int index = 0;
        char cpyname[100] = "";
        printf("%-2s-%-2s-%-4s %-10s %-5s %-25s %-4s %-10s\n", "H", "B", "Thn", "Customer", "Kode", "Barang", "Qty", "Laba");
        printf("-------------------------------------------------------------------\n");
        while (!feof(histori)) {
            fread(&rwyt, sizeof(struct history), 1, histori);
            if (!((rwyt.kode == index) && (strcmp(rwyt.nama, cpyname) == 0))) {
                printf("%-2d-%-2d-%-4d %-10s %-5d %-25s %-4d Rp%-10d\n", rwyt.day, rwyt.month, rwyt.year, rwyt.nama, rwyt.kode, mstr[rwyt.kode].nama, rwyt.qty, rwyt.hargajual-rwyt.hargabeli);
                index = rwyt.kode;
                strcpy(cpyname, rwyt.nama);
            }
        }
        printf("===================================================================\n");
        fclose(histori);
        fclose(master);
        printf("Tekan enter untuk kembali . . .");
        _getch();
    }
}

//update stok oto
void autostock()
{
    FILE *master, *stok;
    master = fopen("masterbarang.dat", "rb");
    stok = fopen("stok.dat", "rb+");
    struct stok stk = {0, 0, 0};
    struct masterbarang mstr = {0, "", 0};

    if (master == NULL) {
        printf("Couldn't load data\n");
    } else {
        while (!feof(master)) {
            fread(&mstr, sizeof(struct masterbarang), 1, master);
            stk.kode = mstr.kode;
            stk.jumlah = 100;
            if (mstr.kode != 0) {
                stk.hargajual = mstr.hargabeli*105/100;
                fseek(stok, (stk.kode-1)*sizeof(struct stok), SEEK_SET);
                fwrite(&stk, 1, sizeof(struct stok), stok);
            }
        }
        printf("Stock updated !\n");
        fclose(master);
        fclose(stok);
    }
} */
