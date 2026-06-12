#pragma once
#include "model.hpp"
#include "cart.hpp"
#include "utils.hpp"

using namespace std;

struct Transaction {
    string id;
    string cashierId;
    string date;
    double total;
    double payment;
    double change;

    void setTransaction(string trxId, string userId, string trxDate, double trxTotal);
    bool pay(double money);
};

void checkout(
    Product products[],
    int productCount,
    CartItem cart[],
    int cartCount,
    Transaction transactions[],
    int &transactionCount,
    Cash* cash,
    string cashierId
);

void startTransaction(
    Product products[],
    int productCount,
    Transaction transactions[],
    int &transactionCount,
    Cash* cash,
    string cashierId
);
