#include "core.hpp"

void tampilkanMenuSistemKasUI();

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
    cout << CYAN << "\n==================================================\n";
    cout << "                  CEK SALDO KAS                   \n";
    cout << "==================================================\n" << RESET;
    cout << "Total Saldo Kas Saat Ini : " << GREEN << BOLD << "Rp " << dataKas->saldo << RESET << "\n";
    cout << CYAN << "--------------------------------------------------\n" << RESET;
}

void setorKas(Kas* dataKas) {
    long long nominal;
    cout << CYAN << "\n==================================================\n";
    cout << "                    SETOR KAS                     \n";
    cout << "==================================================\n" << RESET;
    cout << "Masukkan nominal setor (Rp): ";
    cin >> nominal;
    if (nominal > 0) {
        dataKas->saldo += nominal;
        simpanDataKas(dataKas);
        cout << GREEN << ">> Sukses! Berhasil menyetor Rp " << nominal << " ke dalam kas.\n" << RESET;
        cout << ">> Total saldo kas saat ini: " << GREEN << BOLD << "Rp " << dataKas->saldo << RESET << "\n";
    } else {
        cout << RED << ">> Gagal! Nominal tidak valid.\n" << RESET;
    }
}

void tarikKas(Kas* dataKas) {
    long long nominal;
    cout << CYAN << "\n==================================================\n";
    cout << "                    TARIK KAS                     \n";
    cout << "==================================================\n" << RESET;
    cout << "Masukkan nominal tarik (Rp): ";
    cin >> nominal;

    if (nominal > 0) {
        if (dataKas->saldo >= nominal) {
            dataKas->saldo -= nominal; 
            simpanDataKas(dataKas);
            cout << GREEN << ">> Sukses! Berhasil menarik Rp " << nominal << " dari kas.\n" << RESET;
            cout << ">> Total saldo kas saat ini: " << GREEN << BOLD << "Rp " << dataKas->saldo << RESET << "\n";
        } else {
            cout << RED << ">> Gagal! Saldo kas tidak mencukupi untuk penarikan ini.\n" << RESET;
        }
    } else {
        cout << RED << ">> Gagal! Nominal tidak valid.\n" << RESET;
    }
}

void tampilkanMenuKas(Kas* dataKas) {
    int pilihan;
    bool selesai = false;
    muatDataKas(dataKas);
    while (!selesai) {
        bersihkanLayar();
        tampilkanMenuSistemKasUI();
        pilihan = inputChoice(0, 3);
        switch (pilihan) {
            case 1:
                cekSaldoKas(dataKas);
                jedaLayar();
                break;
            case 2:
                setorKas(dataKas);
                jedaLayar();
                break;
            case 3:
                tarikKas(dataKas);
                jedaLayar();
                break;
            case 0:
                selesai = true;
                cout << "\n>> Menyimpan data dan kembali ke Menu Kasir...\n";
                jedaLayar();
                break;
            default:
                cout << "\n>> [ERROR] Pilihan tidak valid! Silakan masukkan angka 0-3.\n";
                jedaLayar();
        }
    }
}

void tampilkanMenuSistemKasUI() {
    cout << CYAN << "==================================================\n";
    cout << "               SISTEM MANAJEMEN KAS               \n";
    cout << "==================================================\n" << RESET;
    cout << "  [1] Cek Saldo Kas                               \n";
    cout << "  [2] Setor Kas                                   \n";
    cout << "  [3] Tarik Kas                                   \n";
    cout << "  [0] Kembali ke Menu Kasir                       \n";
    cout << "--------------------------------------------------\n";
}