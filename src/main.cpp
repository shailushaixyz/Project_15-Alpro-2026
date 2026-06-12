#include "model.hpp"
#include "cart.hpp"
#include "transaction.hpp"

int main() {
    Product products[100];
    int productCount = 2;

    products[0] = Product{"BR001", "Indomie", 3500, 50};
    products[1] = Product{"BR002", "Aqua", 4000, 30};

    Transaction transactions[100];
    int transactionCount = 0;

    Cash cash;
    cash.balance = 100000;

    string cashierId = "KS001";

    startTransaction(
        products,
        productCount,
        transactions,
        transactionCount,
        &cash,
        cashierId
    );

    return 0;
}