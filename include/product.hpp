#ifndef PRODUCT_HPP
#define PRODUCT_HPP

struct Product {
    int id;
    char nama[100];
    int harga;
    int stok;
};

void tambahProduk();
void editProduk();
void hapusProduk();
void lihatProduk();
void cariProduk();
void menuProduk();

#endif