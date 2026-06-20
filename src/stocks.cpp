#include "core.hpp"

void tampilkanMenuStokUI();
void headerDaftarStokUI();

void Stokmenu(Product products[], int productCount){
	bersihkanLayar();
	int opsi;
	while(true){
	    bersihkanLayar();
        tampilkanMenuStokUI();
        opsi = inputChoice(0, 3);
	
        switch (opsi){
            case 0:
                return;
            case 1:
                bersihkanLayar();
                tambahStok(products, productCount);
                break;
            case 2:
                bersihkanLayar();
                kurangStok(products, productCount);
                break;
            case 3:
                bersihkanLayar();
                lihatStok(products, productCount);
                jedaLayar();
                break;
        }
	}
}

void tambahStok(Product products[], int productCount){
    lihatStok(products, productCount);
    
	string code;
	int jumlah;
	cout << CYAN << "\n==========================================================\n";
	cout << "                       TAMBAH STOK                        \n";
	cout << "==========================================================\n" << RESET;
	cout << ">> Masukkan KODE Produk : ";
	cin >> code;
	
	Product* prdt = findProduct(products, productCount, code);
	
	if (prdt == nullptr){
		cout << RED << ">> Produk Tidak Ditemukan!\n" << RESET;
		jedaLayar();
		return;
	}else{
		cout << "Nama Produk   : " << prdt->name << endl;
		cout << "Stok Tersedia : " << prdt->stock << endl;
	}
	
	cout << "\n>> Masukkan jumlah yang ingin ditambahkan: ";
	cin >> jumlah;
	if (jumlah <= 0){
		cout << RED << ">> Gagal! Jumlah harus lebih dari 0\n" << RESET;
		jedaLayar();
		return;
	}else{
	    prdt->stock += jumlah;
	    cout << CYAN << "----------------------------------------------------------\n" << RESET;	
	    cout << GREEN << ">> Sukses! Stok Berhasil ditambahkan.\n" << RESET;
	    cout << ">> Total Stok Saat Ini: " << GREEN << BOLD << prdt->stock << RESET << "\n\n";
	    simpanDataProduk(products, productCount);
	}
	jedaLayar();
}

void kurangStok(Product products[], int productCount){
    lihatStok(products, productCount);
    
	string code;
	int jumlah;
	cout << CYAN << "\n==========================================================\n";
	cout << "                       KURANGI STOK                       \n";
	cout << "==========================================================\n" << RESET;
	cout << ">> Masukkan KODE Produk : ";
	cin >> code;
	
	Product* prdt = findProduct(products, productCount, code);
	
	if (prdt == nullptr){
		cout << RED << ">> Produk Tidak Ditemukan!\n" << RESET;
		jedaLayar();
		return;
	}else{
		cout << "Nama Produk   : " << prdt->name << endl;
		cout << "Stok Tersedia : " << prdt->stock << endl;
	}
	
	cout << "\n>> Masukkan jumlah yang ingin dikurangi: ";
	cin >> jumlah;
	
	if(jumlah <= 0){
        cout << RED << ">> Gagal! Jumlah harus lebih dari 0!\n" << RESET;
	} else if (jumlah > prdt->stock){
        cout << RED << ">> Gagal! Stok tidak mencukupi!\n" << RESET;
	} else{
        prdt->stock -= jumlah;
        cout << CYAN << "----------------------------------------------------------\n" << RESET;
        cout << GREEN << ">> Sukses! Stok berhasil dikurangi.\n" << RESET;
	    cout << ">> Total Stok Saat Ini: " << GREEN << BOLD << prdt->stock << RESET << "\n\n";
	    simpanDataProduk(products, productCount);
	}
	jedaLayar();
}

void lihatStok(Product products[], int productCount) {
    headerDaftarStokUI();

    for(int i = 0; i < productCount; i++) {
        cout << left << setw(10) << products[i].id 
             << setw(20) << products[i].name 
             << setw(15) << products[i].price 
             << products[i].stock << "\n";
    }
    
    cout << CYAN << "==========================================================\n" << RESET;
}

void tampilkanMenuStokUI() {
    cout << CYAN << "=========================================\n";
    cout << "          MENU MANAJEMEN STOK            \n";
    cout << "=========================================\n" << RESET;
    cout << "  [1] Tambah Stok\n";
    cout << "  [2] Kurangi Stok\n";
    cout << "  [3] Lihat Semua Stok\n";
    cout << "  [0] Kembali\n";
    cout << "-----------------------------------------\n";
}

void headerDaftarStokUI() {
    cout << CYAN << "==========================================================\n";
    cout << "                  DAFTAR PRODUK (STOK)                    \n";
    cout << "==========================================================\n" << RESET;
    cout << left << setw(10) << "KODE" << setw(20) << "NAMA" << setw(15) << "HARGA" << "STOK\n";
    cout << "----------------------------------------------------------\n";
}