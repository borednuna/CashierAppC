# Cashier App C
This repository documents my 1st term final project where each student gets assigned to make a simple cashier app using C. The language used are English and Bahasa, where I actually mixed them up in the process (welp, sorry for that)

- The main source codes are the ones with .c extensions. The main menu of the program is in TA4.c
- "headertoko.h" is the header file containing 3 struct declarations, each for processing the file "masterbarang.dat", "stock.dat", and "histori.dat". Other functions are declared in this file as well.
- "masterbarang.dat" contains data of commodities with the property of commodity code, commodity name, and asset/purchase price for 1 qty of the commodity. "stock.dat" contains data of the commodities with the property of commodity code, active stock, and selling price for 1 qty. "histori.dat" documents every transaction done. "struk.dat" is where the receipt for each transaction is printed out. It is overwritten as a new transaction is done. "laporan.dat" is where weekly/monthly/annual report is printed out. Like "struk.dat", it is also overwritten as a new report is made.
