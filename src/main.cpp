#include <iostream>
#include "model.hpp"
#include "cart.hpp"
#include "transaction.hpp"
#include "kas.hpp"

using namespace std;

int main() {
    Product products[100];
    int productCount = 2;

    products[0] = Product{"BR001", "Indomie", 3500, 50};
    products[1] = Product{"BR002", "Aqua", 4000, 30};

    Transaction transactions[100];
    int transactionCount = 0;

    Kas cash;
    muatDataKas(&cash);

    string cashierId = "KS001";

    int pilihan;

    do {
        cout << "\n=== MENU KASIR ===\n";
        cout << "1. Transaksi Baru\n";
        cout << "2. Manajemen Kas\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                startTransaction(
                    products,
                    productCount,
                    transactions,
                    transactionCount,
                    &cash,
                    cashierId
                );
                simpanDataKas(&cash);
                break;

            case 2:
                tampilkanMenuKas(&cash);
                break;

            case 0:
                simpanDataKas(&cash);
                cout << "Keluar program.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}