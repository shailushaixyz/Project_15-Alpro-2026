#include "core.hpp"

const string FILE_AKUN = "data_akun.txt";

void headerDaftarKasirUI();

void muatDataAkun(Akun dataPengguna[], int &jumlahPengguna) {
    ifstream file(FILE_AKUN);
    if (!file.is_open()) return;
    
    jumlahPengguna = 0;
    string u, p, r, n;
    while (file >> u >> p >> r) {
        file.ignore(); // space
        getline(file, n);
        dataPengguna[jumlahPengguna] = Akun{u, p, r, n};
        jumlahPengguna++;
    }
    file.close();
}

void simpanDataAkun(Akun dataPengguna[], int jumlahPengguna) {
    ofstream file(FILE_AKUN);
    if (!file.is_open()) return;
    for (int i = 0; i < jumlahPengguna; i++) {
        file << dataPengguna[i].username << " "
             << dataPengguna[i].password << " "
             << dataPengguna[i].role << " "
             << dataPengguna[i].nama << "\n";
    }
    file.close();
}

bool tambahAkunKasir(Akun dataPengguna[], int &jumlahPengguna, string username, string password, string nama) {
    if (jumlahPengguna >= MAX_PENGGUNA) {
        cout << RED << "\n[!] Gagal! Kapasitas data pengguna sudah penuh.\n" << RESET;
        return false;
    }

    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == username) {
            cout << RED << "\n[!] Gagal! Username \"" << username << "\" sudah digunakan.\n" << RESET;
            return false;
        }
    }
    
    dataPengguna[jumlahPengguna].username = username;
    dataPengguna[jumlahPengguna].password = password;
    dataPengguna[jumlahPengguna].role = "Kasir";
    dataPengguna[jumlahPengguna].nama = nama;
    
    jumlahPengguna++;
    simpanDataAkun(dataPengguna, jumlahPengguna);
    
    cout << GREEN << "\n[+] Sukses! Akun Kasir '" << nama << "' berhasil ditambahkan.\n" << RESET;
    return true;
}

void lihatDaftarKasir(Akun dataPengguna[], int jumlahPengguna) {
    headerDaftarKasirUI();
    
    bool adaKasir = false;
    int nomor = 1;
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].role == "Kasir") {
            cout << left << setw(5) << nomor 
                 << setw(15) << dataPengguna[i].nama 
                 << setw(15) << dataPengguna[i].username 
                 << dataPengguna[i].password << "\n";
            adaKasir = true;
            nomor++;
        }
    }
    
    if (!adaKasir) {
        cout << YELLOW << "       [-] Belum ada akun kasir.        \n" << RESET;
    }
    cout << CYAN << "==========================================================\n" << RESET;
}

bool editAkunKasir(Akun dataPengguna[], int jumlahPengguna, string usernameTarget, string usernameBaru, string passwordBaru, string namaBaru) {
    int indeksTarget = -1;
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == usernameTarget && dataPengguna[i].role == "Kasir") {
            indeksTarget = i;
            break;
        }
    }

    if (indeksTarget == -1) {
        cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << usernameTarget << "' tidak ditemukan.\n" << RESET;
        return false;
    }

    if (!usernameBaru.empty() && usernameBaru != "-" && usernameBaru != usernameTarget) {
        for (int i = 0; i < jumlahPengguna; i++) {
            if (dataPengguna[i].username == usernameBaru) {
                cout << RED << "\n[!] Gagal! Username baru '" << usernameBaru << "' sudah digunakan oleh akun lain.\n" << RESET;
                return false;
            }
        }
        dataPengguna[indeksTarget].username = usernameBaru;
    }

    if (!passwordBaru.empty() && passwordBaru != "-") dataPengguna[indeksTarget].password = passwordBaru;
    if (!namaBaru.empty() && namaBaru != "-") dataPengguna[indeksTarget].nama = namaBaru;
    
    simpanDataAkun(dataPengguna, jumlahPengguna);
    
    cout << GREEN << "\n[+] Sukses! Data akun berhasil diperbarui.\n" << RESET;
    return true;
}


bool hapusAkunKasir(Akun dataPengguna[], int &jumlahPengguna, string usernameTarget) {
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == usernameTarget && dataPengguna[i].role == "Kasir") {
            
            // Geser elemen-elemen setelahnya ke kiri
            for (int j = i; j < jumlahPengguna - 1; j++) {
                dataPengguna[j] = dataPengguna[j + 1];
            }
            
            jumlahPengguna--;
            simpanDataAkun(dataPengguna, jumlahPengguna);
            cout << GREEN << "\n[+] Sukses! Akun Kasir '" << usernameTarget << "' telah dihapus.\n" << RESET;
            return true;
        }
    }
    cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << usernameTarget << "' tidak ditemukan.\n" << RESET;
    return false;
}

void headerDaftarKasirUI() {
    cout << CYAN << "==========================================================\n";
    cout << "                    DAFTAR AKUN KASIR                     \n";
    cout << "==========================================================\n" << RESET;
    cout << left << setw(5) << "NO" << setw(15) << "NAMA" << setw(15) << "USERNAME" << "PASSWORD\n";
    cout << "----------------------------------------------------------\n";
}

void tampilkanMenuManajemenAkunUI() {
    cout << CYAN << "=========================================\n";
    cout << "          MANAJEMEN AKUN KASIR           \n";
    cout << "=========================================\n" << RESET;
    cout << "  [1] Tambah Akun Kasir\n";
    cout << "  [2] Lihat Daftar Kasir\n";
    cout << "  [3] Edit Akun Kasir\n";
    cout << "  [4] Hapus Akun Kasir\n";
    cout << "  [0] Kembali\n";
    cout << "-----------------------------------------\n";
}

void menuManajemenAkun(Akun dataPengguna[], int &jumlahPengguna) {
    int pilihan;
    do {
        bersihkanLayar();
        tampilkanMenuManajemenAkunUI();
        pilihan = inputChoice(0, 4);

        if (pilihan == 1) {
            string u, p, n;
            cout << CYAN << "\n==========================================================\n";
            cout << "                       TAMBAH KASIR                       \n";
            cout << "==========================================================\n" << RESET;
            cout << "Username Baru : "; cin >> u;
            cout << "Password Baru : "; cin >> p;
            cout << "Nama Kasir    : "; 
            cin.ignore(); getline(cin, n);
            tambahAkunKasir(dataPengguna, jumlahPengguna, u, p, n);
            jedaLayar();
        } 
        else if (pilihan == 2) {
            bersihkanLayar();
            lihatDaftarKasir(dataPengguna, jumlahPengguna);
            jedaLayar();
        } 
        else if (pilihan == 3) {
            bersihkanLayar();
            lihatDaftarKasir(dataPengguna, jumlahPengguna);
            string target, u, p, n;
            cout << CYAN << "\n==========================================================\n";
            cout << "                        EDIT KASIR                        \n";
            cout << "==========================================================\n" << RESET;
            cout << "Masukkan Username yang ingin diedit: "; cin >> target;
            
            bool ketemu = false;
            for (int i = 0; i < jumlahPengguna; i++) {
                if (dataPengguna[i].username == target && dataPengguna[i].role == "Kasir") {
                    ketemu = true;
                    break;
                }
            }
            
            if (!ketemu) {
                cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << target << "' tidak ditemukan.\n" << RESET;
            } else {
                cout << "Username Baru (- jika tidak diubah): "; cin >> u;
                cout << "Password Baru (- jika tidak diubah): "; cin >> p;
                cout << "Nama Baru (- jika tidak diubah)    : "; 
                cin.ignore(); getline(cin, n);
                if(n.empty()) n = "-";
                editAkunKasir(dataPengguna, jumlahPengguna, target, u, p, n);
            }
            jedaLayar();
        } 
        else if (pilihan == 4) {
            bersihkanLayar();
            lihatDaftarKasir(dataPengguna, jumlahPengguna);
            string target;
            cout << CYAN << "\n==========================================================\n";
            cout << "                       HAPUS KASIR                        \n";
            cout << "==========================================================\n" << RESET;
            cout << "Masukkan Username yang ingin dihapus: "; cin >> target;
            
            bool ketemu = false;
            for (int i = 0; i < jumlahPengguna; i++) {
                if (dataPengguna[i].username == target && dataPengguna[i].role == "Kasir") {
                    ketemu = true;
                    break;
                }
            }
            
            if (!ketemu) {
                cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << target << "' tidak ditemukan.\n" << RESET;
            } else {
                hapusAkunKasir(dataPengguna, jumlahPengguna, target);
            }
            jedaLayar();
        }
    } while (pilihan != 0);
}