#include <iostream>
#include <vector>   
#include <string>   

using namespace std;

struct Akun {
    string username;
    string password;
    string role; 
    string nama;
};

vector<Akun> dataPengguna = {
    {"admin1", "123", "Admin", "Neza Admin"},
    {"kasir1", "456", "Kasir", "Alya Kasir"}
};


void bersihkanLayar() {
    cout << "\033[2J\033[1;1H";
}

void jedaLayar() {
    cout << "\nTekan [Enter] untuk melanjutkan...";
    cin.get(); 
}

bool tambahAkunKasir(string username, string password, string nama) {
    for (const auto& akun : dataPengguna) {
        if (akun.username == username) {
            cout << "\n[!] Gagal! Username \"" << username << "\" sudah digunakan.\n";
            return false;
        }
    }
    
    Akun kasirBaru = {username, password, "Kasir", nama};
    dataPengguna.push_back(kasirBaru);
    cout << "\n[+] Sukses! Akun Kasir '" << nama << "' berhasil ditambahkan.\n";
    return true;
}

void lihatDaftarKasir() {
    cout << "=========================================\n";
    cout << "           DAFTAR AKUN KASIR             \n";
    cout << "=========================================\n";
    
    bool adaKasir = false;
    int nomor = 1;
    
    for (const auto& akun : dataPengguna) {
        if (akun.role == "Kasir") {
            cout << nomor << ". Nama: " << akun.nama << "\n";
            cout << "   Username: " << akun.username << " | Password: " << akun.password << "\n";
            cout << "-----------------------------------------\n";
            adaKasir = true;
            nomor++;
        }
    }
    
    if (!adaKasir) {
        cout << "       [-] Belum ada akun kasir.        \n";
        cout << "=========================================\n";
    }
}

bool editAkunKasir(string usernameTarget, string usernameBaru, string passwordBaru, string namaBaru) {
    int indeksTarget = -1;
    for (size_t i = 0; i < dataPengguna.size(); ++i) {
        if (dataPengguna[i].username == usernameTarget && dataPengguna[i].role == "Kasir") {
            indeksTarget = i;
            break;
        }
    }

    if (indeksTarget == -1) {
        cout << "\n[!] Gagal! Akun Kasir dengan username '" << usernameTarget << "' tidak ditemukan.\n";
        return false;
    }

    if (!usernameBaru.empty() && usernameBaru != "-" && usernameBaru != usernameTarget) {
        for (const auto& akun : dataPengguna) {
            if (akun.username == usernameBaru) {
                cout << "\n[!] Gagal! Username baru '" << usernameBaru << "' sudah digunakan oleh akun lain.\n";
                return false;
            }
        }
        dataPengguna[indeksTarget].username = usernameBaru;
    }

    if (!passwordBaru.empty() && passwordBaru != "-") dataPengguna[indeksTarget].password = passwordBaru;
    if (!namaBaru.empty() && namaBaru != "-") dataPengguna[indeksTarget].nama = namaBaru;
    
    cout << "\n[+] Sukses! Data akun berhasil diperbarui.\n";
    return true;
}


bool hapusAkunKasir(string usernameTarget) {
    for (auto it = dataPengguna.begin(); it != dataPengguna.end(); ++it) {
        if (it->username == usernameTarget && it->role == "Kasir") {
            dataPengguna.erase(it);
            cout << "\n[+] Sukses! Akun Kasir '" << usernameTarget << "' telah dihapus.\n";
            return true;
        }
    }
    cout << "\n[!] Gagal! Akun Kasir dengan username '" << usernameTarget << "' tidak ditemukan.\n";
    return false;
}