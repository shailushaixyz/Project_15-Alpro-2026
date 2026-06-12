#pragma once
#include "model.hpp"

using namespace std;

extern const int MAX_CART;

struct CartItem {
    string productId;
    string productName;
    double price;
    int quantity;
    double subtotal;

    void setItem(Product* product, int qty);
    void addQuantity(int qty);
};

CartItem* findCartItem(CartItem cart[], int cartCount, string productId);
Product* findProduct(Product products[], int productCount, string productId);
double calculateTotal(CartItem cart[], int cartCount);
void addToCart(Product products[], int productCount, CartItem cart[], int &cartCount, string productId, int qty);
void showCart(CartItem cart[], int cartCount);
