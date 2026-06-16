#include <iostream>
#include <vector>   
#include <string>   

using namespace std;

// ================= FUNGSI SISTEM (LOGIN & MENU) =================

string prosesLogin(Akun &userAktif) {
    bersihkanLayar();
    cout << "=========================================\n";
    cout << "               MENU LOGIN                \n";
    cout << "=========================================\n";
    cout << "Ketik 'exit' pada Username untuk keluar program.\n\n";
    
    string uname, pwd;
    cout << "Username : "; cin >> uname;
    
    if (uname == "exit") {
        return "Exit"; 
    }

    cout << "Password : "; cin >> pwd;

    // Cek username, kecocokan password, lalu kembalikan rolenya
    for (const auto& akun : dataPengguna) {
        if (akun.username == uname && akun.password == pwd) {
            userAktif = akun; 
            
            if (akun.role == "Admin") {
                return "Admin";
            } else if (akun.role == "Kasir") {
                return "Kasir";
            }
        }
    }
    
    return "Gagal"; 
}

void menuAdmin(Akun adminAktif) {
    bool sesiAktif = true;
    while (sesiAktif) {
        bersihkanLayar();
        cout << "=========================================\n";
        cout << "               MENU ADMIN                \n";
        cout << "=========================================\n";
        cout << "Halo, " << adminAktif.nama << "!\n\n";
        cout << "1. Tambah Akun Kasir\n";
        cout << "2. Lihat Daftar Kasir\n";
        cout << "3. Edit Akun Kasir\n";
        cout << "4. Hapus Akun Kasir\n";
        cout << "5. Logout\n";
        cout << "-----------------------------------------\n";
        
        string pilihan;
        cout << "Pilih menu [1-5]: ";
        cin >> pilihan;

        if (pilihan == "1") {
            string u, p, n;
            cout << "\n=== TAMBAH KASIR ===\n";
            cout << "Username Baru : "; cin >> u;
            cout << "Password Baru : "; cin >> p;
            cout << "Nama Kasir    : "; 
            cin.ignore(); getline(cin, n);
            tambahAkunKasir(u, p, n);
            jedaLayar();
        } 
        else if (pilihan == "2") {
            lihatDaftarKasir();
            jedaLayar();
        } 
        else if (pilihan == "3") {
            string target, u, p, n;
            cout << "\n=== EDIT KASIR ===\n";
            cout << "Masukkan Username yang ingin diedit: "; cin >> target;
            cout << "Username Baru (- jika tidak diubah): "; cin >> u;
            cout << "Password Baru (- jika tidak diubah): "; cin >> p;
            cout << "Nama Baru (- jika tidak diubah)    : "; 
            cin.ignore(); getline(cin, n);
            if(n.empty()) n = "-";
            editAkunKasir(target, u, p, n);
            jedaLayar();
        } 
        else if (pilihan == "4") {
            string target;
            cout << "\n=== HAPUS KASIR ===\n";
            cout << "Masukkan Username yang ingin dihapus: "; cin >> target;
            hapusAkunKasir(target);
            jedaLayar();
        } 
        else if (pilihan == "5") {
            cout << "\n[+] Anda berhasil logout dari Admin.\n";
            jedaLayar();
            return; 
        } 
        else {
            cout << "\n[!] Pilihan tidak valid!\n";
            jedaLayar();
        }
    }
}

void menuKasir(Akun kasirAktif) {
    bool sesiAktif = true;
    while (sesiAktif) {
        bersihkanLayar();
        cout << "=========================================\n";
        cout << "               MENU KASIR                \n";
        cout << "=========================================\n";
        cout << "Halo, " << kasirAktif.nama << "!\n\n";
        cout << "1. Menu Transaksi (Belum Tersedia)\n";
        cout << "2. Logout\n";
        cout << "-----------------------------------------\n";
        
        string pilihan;
        cout << "Pilih menu [1-2]: ";
        cin >> pilihan;

        if (pilihan == "1") {
            cout << "\n[!] Fitur transaksi sedang dalam pengembangan...\n";
            jedaLayar();
        } 
        else if (pilihan == "2") {
            cout << "\n[+] Anda berhasil logout dari Kasir.\n";
            jedaLayar();
            return; 
        } 
        else {
            cout << "\n[!] Pilihan tidak valid!\n";
            jedaLayar();
        }
    }
}


