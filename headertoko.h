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
