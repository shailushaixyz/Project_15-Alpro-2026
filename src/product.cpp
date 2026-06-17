#include "../include/product.hpp"
#include <iostream>
#include <cstring>

using namespace std;

Product daftarProduk[100];
int jumlahProduk = 0;

void tambahProduk() {
    cout << "\n=== Tambah Produk ===" << endl;

    cout << "ID Produk    : ";
    cin >> daftarProduk[jumlahProduk].id;
    cin.ignore();

    cout << "Nama Produk  : ";
    cin.getline(daftarProduk[jumlahProduk].nama, 100);

    cout << "Harga Produk : ";
    cin >> daftarProduk[jumlahProduk].harga;

    cout << "Stok Produk  : ";
    cin >> daftarProduk[jumlahProduk].stok;

    jumlahProduk++;

    cout << "\nProduk berhasil ditambahkan!" << endl;
}

void lihatProduk() {
    cout << "\n=== Daftar Produk ===" << endl;

    if (jumlahProduk == 0) {
        cout << "Belum ada produk." << endl;
        return;
    }

    for (int i = 0; i < jumlahProduk; i++) {
        cout << "\nProduk ke-" << i + 1 << endl;
        cout << "ID     : " << daftarProduk[i].id << endl;
        cout << "Nama   : " << daftarProduk[i].nama << endl;
        cout << "Harga  : " << daftarProduk[i].harga << endl;
        cout << "Stok   : " << daftarProduk[i].stok << endl;
    }
}

void cariProduk() {
    int id;
    bool ditemukan = false;

    cout << "\n=== Cari Produk ===" << endl;
    cout << "Masukkan ID Produk: ";
    cin >> id;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            cout << "\nProduk ditemukan!" << endl;
            cout << "ID     : " << daftarProduk[i].id << endl;
            cout << "Nama   : " << daftarProduk[i].nama << endl;
            cout << "Harga  : " << daftarProduk[i].harga << endl;
            cout << "Stok   : " << daftarProduk[i].stok << endl;

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void editProduk() {
    int id;
    bool ditemukan = false;

    cout << "\n=== Edit Produk ===" << endl;
    cout << "Masukkan ID Produk yang akan diedit: ";
    cin >> id;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            cin.ignore();

            cout << "Nama Baru   : ";
            cin.getline(daftarProduk[i].nama, 100);

            cout << "Harga Baru  : ";
            cin >> daftarProduk[i].harga;

            cout << "Stok Baru   : ";
            cin >> daftarProduk[i].stok;

            cout << "Produk berhasil diperbarui!" << endl;

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void hapusProduk() {
    int id;
    bool ditemukan = false;

    cout << "\n=== Hapus Produk ===" << endl;
    cout << "Masukkan ID Produk yang akan dihapus: ";
    cin >> id;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {

            for (int j = i; j < jumlahProduk - 1; j++) {
                daftarProduk[j] = daftarProduk[j + 1];
            }

            jumlahProduk--;

            cout << "Produk berhasil dihapus!" << endl;

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void menuProduk() {
    int pilihan;

    do {
        cout << "\n=== MANAJEMEN PRODUK ===" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Lihat Daftar Produk" << endl;
        cout << "3. Cari Produk" << endl;
        cout << "4. Edit Produk" << endl;
        cout << "5. Hapus Produk" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahProduk();
                break;
            case 2:
                lihatProduk();
                break;
            case 3:
                cariProduk();
                break;
            case 4:
                editProduk();
                break;
            case 5:
                hapusProduk();
                break;
            case 0:
                cout << "Kembali ke menu utama..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);
}