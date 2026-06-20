#include "core.hpp"

const string FILE_PRODUK = "data_produk.txt";

void muatDataProduk(Product daftarProduk[], int& jumlahProduk) {
    ifstream file(FILE_PRODUK);
    if (!file.is_open()) return;
    
    jumlahProduk = 0;
    string id, name;
    double price;
    int stock;
    while (file >> id >> price >> stock) {
        file.ignore();
        getline(file, name);
        daftarProduk[jumlahProduk] = Product{id, name, price, stock};
        jumlahProduk++;
    }
    file.close();
}

void simpanDataProduk(Product daftarProduk[], int jumlahProduk) {
    ofstream file(FILE_PRODUK);
    if (!file.is_open()) return;
    for (int i = 0; i < jumlahProduk; i++) {
        file << daftarProduk[i].id << " "
             << daftarProduk[i].price << " "
             << daftarProduk[i].stock << " "
             << daftarProduk[i].name << "\n";
    }
    file.close();
}

void headerDaftarProdukUI();
void tampilkanMenuProdukUI();

void tambahProduk(Product daftarProduk[], int& jumlahProduk) {
    cout << CYAN << "\n==========================================================\n";
    cout << "                      TAMBAH PRODUK                       \n";
    cout << "==========================================================\n" << RESET;

    string idBaru;
    cout << "ID Produk    : ";
    cin >> idBaru;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == idBaru) {
            cout << RED << "\n[!] Gagal! ID Produk \"" << idBaru << "\" sudah digunakan.\n" << RESET;
            return;
        }
    }

    daftarProduk[jumlahProduk].id = idBaru;
    cin.ignore();

    cout << "Nama Produk  : ";
    getline(cin, daftarProduk[jumlahProduk].name);

    cout << "Harga Produk : ";
    cin >> daftarProduk[jumlahProduk].price;

    cout << "Stok Produk  : ";
    cin >> daftarProduk[jumlahProduk].stock;

    jumlahProduk++;
    simpanDataProduk(daftarProduk, jumlahProduk);

    cout << GREEN << "\n[+] Sukses! Produk berhasil ditambahkan.\n" << RESET;
}

void lihatProduk(Product daftarProduk[], int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << YELLOW << "Belum ada produk.\n" << RESET;
        return;
    }

    headerDaftarProdukUI();

    for (int i = 0; i < jumlahProduk; i++) {
        cout << left << setw(10) << daftarProduk[i].id 
             << setw(20) << daftarProduk[i].name 
             << setw(15) << daftarProduk[i].price 
             << daftarProduk[i].stock << "\n";
    }
    
    cout << CYAN << "==========================================================\n" << RESET;
}

void cariProduk(Product daftarProduk[], int jumlahProduk) {
    string id;
    bool ditemukan = false;

    cout << CYAN << "\n==========================================================\n";
    cout << "                       CARI PRODUK                        \n";
    cout << "==========================================================\n" << RESET;
    cout << "Masukkan ID Produk: ";
    cin >> id;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            cout << GREEN << "\n[+] Produk ditemukan!\n" << RESET;
            cout << "ID     : " << daftarProduk[i].id << endl;
            cout << "Nama   : " << daftarProduk[i].name << endl;
            cout << "Harga  : Rp " << (long long)daftarProduk[i].price << endl;
            cout << "Stok   : " << daftarProduk[i].stock << endl;

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << RED << "\n[!] Produk tidak ditemukan.\n" << RESET;
    }
}

void editProduk(Product daftarProduk[], int jumlahProduk) {
    bersihkanLayar();
    lihatProduk(daftarProduk, jumlahProduk);
    
    string id;
    bool ditemukan = false;

    cout << CYAN << "\n==========================================================\n";
    cout << "                       EDIT PRODUK                        \n";
    cout << "==========================================================\n" << RESET;
    cout << "Masukkan ID Produk yang akan diedit: ";
    cin >> id;

    int indexEdit = -1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            indexEdit = i;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << RED << "Produk tidak ditemukan.\n" << RESET;
        jedaLayar();
        return;
    }

    cin.ignore();
    cout << "Nama Baru   : ";
    getline(cin, daftarProduk[indexEdit].name);

    cout << "Harga Baru  : ";
    cin >> daftarProduk[indexEdit].price;

    cout << "Stok Baru   : ";
    cin >> daftarProduk[indexEdit].stock;
    
    simpanDataProduk(daftarProduk, jumlahProduk);

    cout << GREEN << "\n[+] Sukses! Produk berhasil diperbarui.\n" << RESET;
    jedaLayar();
}

void hapusProduk(Product daftarProduk[], int& jumlahProduk) {
    bersihkanLayar();
    lihatProduk(daftarProduk, jumlahProduk);
    
    string id;
    bool ditemukan = false;

    cout << CYAN << "\n==========================================================\n";
    cout << "                      HAPUS PRODUK                        \n";
    cout << "==========================================================\n" << RESET;
    cout << "Masukkan ID Produk yang akan dihapus: ";
    cin >> id;

    int indexHapus = -1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            indexHapus = i;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << RED << "Produk tidak ditemukan.\n" << RESET;
        jedaLayar();
        return;
    }

    for (int j = indexHapus; j < jumlahProduk - 1; j++) {
        daftarProduk[j] = daftarProduk[j + 1];
    }
    jumlahProduk--;
    
    simpanDataProduk(daftarProduk, jumlahProduk);

    cout << GREEN << "\n[+] Sukses! Produk berhasil dihapus.\n" << RESET;
    jedaLayar();
}

void menuProduk(Product daftarProduk[], int& jumlahProduk) {
    int pilihan;

    do {
        bersihkanLayar();
        tampilkanMenuProdukUI();
        pilihan = inputChoice(0, 5);

        switch (pilihan) {
            case 1:
                bersihkanLayar();
                tambahProduk(daftarProduk, jumlahProduk);
                jedaLayar();
                break;
            case 2:
                bersihkanLayar();
                lihatProduk(daftarProduk, jumlahProduk);
                jedaLayar();
                break;
            case 3:
                bersihkanLayar();
                cariProduk(daftarProduk, jumlahProduk);
                jedaLayar();
                break;
            case 4:
                editProduk(daftarProduk, jumlahProduk);
                break;
            case 5:
                hapusProduk(daftarProduk, jumlahProduk);
                break;
            case 0:
                cout << "Kembali ke menu utama..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);
}

void headerDaftarProdukUI() {
    cout << CYAN << "==========================================================\n";
    cout << "                      DAFTAR PRODUK                       \n";
    cout << "==========================================================\n" << RESET;
    cout << left << setw(10) << "ID" << setw(20) << "NAMA" << setw(15) << "HARGA" << "STOK\n";
    cout << "----------------------------------------------------------\n";
}

void tampilkanMenuProdukUI() {
    cout << CYAN << "=========================================\n";
    cout << "            MANAJEMEN PRODUK             \n";
    cout << "=========================================\n" << RESET;
    cout << "  [1] Tambah Produk\n";
    cout << "  [2] Lihat Daftar Produk\n";
    cout << "  [3] Cari Produk\n";
    cout << "  [4] Edit Produk\n";
    cout << "  [5] Hapus Produk\n";
    cout << "  [0] Kembali\n";
    cout << "-----------------------------------------\n";
}