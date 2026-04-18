#include "orderbook.h"

int main() {
    OrderBook ob;
    cout << "\n===== FIFO TEST (Single OrderBook) =====\n";

    // Same price FIFO test
    ob.addOrder(Order(1, 100, 10, true, 1)); // first
    ob.addOrder(Order(2, 100, 10, true, 1)); // second
    ob.addOrder(Order(3, 100, 10, true, 1)); // third
    // Price priority test
    ob.addOrder(Order(4, 101, 10, true, 1)); // higher price
    // Sell to trigger matching
    ob.addOrder(Order(5, 100, 35, false, 1));
    ob.printOrderBook();
    cout << "\n===== MODIFY TEST =====\n";
    ob.modifyOrder(3, 100, 10); // should go to back
    ob.addOrder(Order(6, 100, 10, false, 1));
    ob.printOrderBook();
    cout << "\n===== CANCEL TEST =====\n";
    ob.cancelOrder(2);
    ob.addOrder(Order(7, 100, 10, false, 1));
    ob.printOrderBook();
    
    return 0;
}