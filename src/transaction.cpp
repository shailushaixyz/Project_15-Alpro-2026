#include "transaction.hpp"

void Transaction::setTransaction(string trxId, string userId, string trxDate, double trxTotal) {
    id = trxId;
    cashierId = userId;
    date = trxDate;
    total = trxTotal;
    payment = 0;
    change = 0;
}

bool Transaction::pay(double money) {
    if (money < total) {
        return false;
    }

    payment = money;
    change = payment - total;
    return true;
}

void checkout(
    Product products[],
    int productCount,
    CartItem cart[],
    int cartCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
) {
    if (cartCount == 0) {
        cout << "Keranjang kosong.\n";
        return;
    }

    Transaction trx;
    trx.setTransaction(
        "TRX" + to_string(transactionCount + 1),
        cashierId,
        getCurrentDate(),
        calculateTotal(cart, cartCount)
    );

    double money;
    cout << "Total: " << trx.total << endl;
    cout << "Bayar: ";
    cin >> money;

    while (!trx.pay(money)) {
        cout << "Uang kurang.\n";
        cout << "Bayar: ";
        cin >> money;
    }

    for (int i = 0; i < cartCount; i++) {
    Product* product = findProduct(products, productCount, cart[i].productId);

    if (product != nullptr) {
        product->stock -= cart[i].quantity;
    }
    }

    cout << "Saldo kas sebelum transaksi: Rp " << cash->saldo << endl;

    cash->saldo += trx.total;

    cout << "Saldo kas setelah transaksi : Rp " << cash->saldo << endl;

    transactions[transactionCount] = trx;
    transactionCount++;

    cout << "\nTransaksi berhasil.\n";
    cout << "Kembalian: " << trx.change << endl;
}

void startTransaction(
    Product products[],
    int productCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
) {
    CartItem cart[MAX_CART];
    int cartCount = 0;

    string input;
    string lastProductId = "";

    while (true) {
        showCart(cart, cartCount);

        cout << "\nInput kode barang / command: ";
        cin >> input;

        if (input == "q") {
            if (lastProductId == "") {
                cout << "Belum ada barang yang dipilih.\n";
                continue;
            }
            
            CartItem* item = findCartItem(cart, cartCount, lastProductId);

            int qty;
            cout << "Jumlah baru untuk " << item->productName << " : ";
            cin >> qty;

            if (item != nullptr) {
                item->quantity = 0;
                item->subtotal = 0;

                addToCart(products, productCount, cart, cartCount, lastProductId, qty);
            }
        }
        else if (input == "c") {
            checkout(
                products,
                productCount,
                cart,
                cartCount,
                transactions,
                transactionCount,
                cash,
                cashierId
            );
            break;
        }
        else if (input == "x") {
            cout << "Transaksi dibatalkan.\n";
            break;
        }
        else {
            addToCart(products, productCount, cart, cartCount, input, 1);
            lastProductId = input;
        }
    }
}

void transactionHistory(Transaction transactions[], int transactionCount) {
    if (transactionCount == 0) {
        cout << "belum ada transaksi.\n";
        return;
    }

    cout << "Riwayat Transaksi:\n";
    for (int i = 0; i < transactionCount; i++) {
        cout << transactions[i].id << " | "
             << transactions[i].cashierId << " | "
             << transactions[i].date << " | "
             << "total: " << transactions[i].total << " | "
             << "bayar: " << transactions[i].payment << " | "
             << "kembalian: " << transactions[i].change << endl;
    }
}

void totalSales(Transaction transactions[], int transactionCount) {
    double total = 0;
    for (int i = 0; i < transactionCount; i++) {
        total += transactions[i].total;
    }
    cout << "total penjualan: Rp " << total << endl;
}

void soldProducts(Transaction transactions[], int transactionCount) {
    if (transactionCount == 0) {
        cout << "belum ada transaksi.\n";
        return;
    }

    cout << "Produk Terjual:\n";
    for (int i = 0; i < transactionCount; i++) {
        cout << transactions[i].id << " | "
             << transactions[i].cashierId << " | "
             << transactions[i].date << " | "
             << "Total: " << transactions[i].total << endl;
    }
}

void tampilkanMenuLaporan(Transaction transactions[], int transactionCount) {
    int pilihan;
    do {
        cout << "\n==================================================\n";
        cout << "               SISTEM MANAJEMEN KAS               \n";
        cout << "==================================================\n";
        cout << "  [1] List Transaksi                              \n";
        cout << "  [2] Total Penjualan                             \n";
        cout << "  [3] Produk Terjual                              \n";
        cout << "--------------------------------------------------\n";
        cout << "  [0] Kembali ke Menu Kasir                       \n";
        cout << "==================================================\n";
        cout << ">> Masukkan kode pilihan Anda (0-3): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                transactionHistory(transactions, transactionCount);
                break;
            case 2:
                totalSales(transactions, transactionCount);
                break;
            case 3:
                soldProducts(transactions, transactionCount);
                break;
            case 0:
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}