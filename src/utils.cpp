#include "core.hpp"
#include <limits>
#include <ctime>

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string date = to_string(ltm->tm_mday) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(1900 + ltm->tm_year);

    return date;
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void pauseScreen() {
    cout << "\nTekan [Enter] untuk melanjutkan...";
    if (cin.peek() == '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.get();
}

void bersihkanLayar() {
    clearScreen();
}

void jedaLayar() {
    pauseScreen();
}

// Fungsi-fungsi kompleks berbasis vector dihapus agar sesuai dengan materi Alpro

int inputChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Pilih (" << min << "-" << max << "): ";
        cin >> choice;
        
        if (cin.fail()) {
            cout << RED << "Input tidak valid. Harap masukkan angka.\n" << RESET;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (choice >= min && choice <= max) {
            return choice;
        } else {
            cout << RED << "Pilihan di luar rentang. Silakan coba lagi.\n" << RESET;
        }
    }
}