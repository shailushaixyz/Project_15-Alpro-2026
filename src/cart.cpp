#include "cart.hpp"
#include "utils.hpp"

using namespace std;

const int MAX_CART = 50;

void CartItem::setItem(Product* product, int qty) {
    productId = product->id;
    productName = product->name;
    price = product->price;
    quantity = qty;
    subtotal = price * quantity;
}

void CartItem::addQuantity(int qty) {
    quantity += qty;
    subtotal = price * quantity;
}

CartItem* findCartItem(CartItem cart[], int cartCount, string productId) {
    for (int i = 0; i < cartCount; i++) {
        if (cart[i].productId == productId) {
            return &cart[i];
        }
    }
    return nullptr;
}

Product* findProduct(Product products[], int productCount, string productId) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            return &products[i];
        }
    }
    return nullptr;
}

double calculateTotal(CartItem cart[], int cartCount) {
    double total = 0;
    for (int i = 0; i < cartCount; i++) {
        total += cart[i].subtotal;
    }
    return total;
}

void addToCart(
    Product products[],
    int productCount,
    CartItem cart[],
    int &cartCount,
    string productId,
    int qty
) {
    Product* product = findProduct(products, productCount, productId);

    if (product == nullptr) {
        cout << "Produk tidak ditemukan.\n";
        return;
    }

    CartItem* item = findCartItem(cart, cartCount, productId);

    int currentQty = 0;
    if (item != nullptr) {
        currentQty = item->quantity;
    }

    if (product->stock < currentQty + qty) {
        cout << "Stok tidak cukup.\n";
        return;
    }

    if (item != nullptr) {
        item->addQuantity(qty);
    } else {
        cart[cartCount].setItem(product, qty);
        cartCount++;
    }

    cout << "Produk berhasil ditambahkan.\n";
}

void showCart(CartItem cart[], int cartCount) {
    clearScreen();

    if (cartCount == 0) {
        cout << "Keranjang kosong.\n";
        return;
    }

    cout << "\n===== KERANJANG =====\n";

    for (int i = 0; i < cartCount; i++) {
        cout << cart[i].productName
             << " x" << cart[i].quantity
             << " = " << cart[i].subtotal << endl;
    }

    cout << "=====================\n";
}
