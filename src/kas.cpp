#include <iostream>
#include <fstream>
#include "kas.hpp"
using namespace std;

const string FILE_KAS = "data_kas.txt"; 

void muatDataKas(Kas* dataKas) {
    ifstream file(FILE_KAS);
    if (file.is_open()) {
        file >> dataKas->saldo;
        file.close();
    } else {
        dataKas->saldo = 0;
    }
}

void simpanDataKas(const Kas* dataKas) {
    ofstream file(FILE_KAS);
    if (file.is_open()) {
        file << dataKas->saldo;
        file.close();
    }
}

void cekSaldoKas(const Kas* dataKas) {
    cout << "\n=== CEK SALDO KAS ===\n";
    cout << "Total Saldo Kas Saat Ini: Rp " << dataKas->saldo << "\n";
    cout << "=====================\n";
}

void setorKas(Kas* dataKas) {
    long long nominal;
    cout << "\n=== SETOR KAS ===\n";
    cout << "Masukkan nominal setor (Rp): ";
    cin >> nominal;
    if (nominal > 0) {
        dataKas->saldo += nominal;
        simpanDataKas(dataKas);
        cout << ">> Sukses! Berhasil menyetor Rp " << nominal << " ke dalam kas.\n";
    } else {
        cout << ">> Gagal! Nominal tidak valid.\n";
    }
}

void tarikKas(Kas* dataKas) {
    long long nominal;
    cout << "\n=== TARIK KAS ===\n";
    cout << "Masukkan nominal tarik (Rp): ";
    cin >> nominal;

    if (nominal > 0) {
        if (dataKas->saldo >= nominal) {
            dataKas->saldo -= nominal; 
            simpanDataKas(dataKas);
            cout << ">> Sukses! Berhasil menarik Rp " << nominal << " dari kas.\n";
        } else {
            cout << ">> Gagal! Saldo kas tidak mencukupi untuk penarikan ini.\n";
        }
    } else {
        cout << ">> Gagal! Nominal tidak valid.\n";
    }
}

void tampilkanMenuKas(Kas* dataKas) {
    int pilihan;
    bool selesai = false;
    muatDataKas(dataKas);
    while (!selesai) {
        cout << "\n==================================================\n";
        cout << "               SISTEM MANAJEMEN KAS               \n";
        cout << "==================================================\n";
        cout << "  [1] Cek Saldo Kas                               \n";
        cout << "  [2] Setor Kas                                   \n";
        cout << "  [3] Tarik Kas                                   \n";
        cout << "--------------------------------------------------\n";
        cout << "  [0] Kembali ke Menu Kasir                       \n";
        cout << "==================================================\n";
        cout << ">> Masukkan kode pilihan Anda (0-3): ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                cekSaldoKas(dataKas);
                break;
            case 2:
                setorKas(dataKas);
                break;
            case 3:
                tarikKas(dataKas);
                break;
            case 0:
                selesai = true;
                cout << "\n>> Menyimpan data dan kembali ke Menu Kasir...\n";
                break;
            default:
                cout << "\n>> [ERROR] Pilihan tidak valid! Silakan masukkan angka 0-3.\n";
        }
    }
}