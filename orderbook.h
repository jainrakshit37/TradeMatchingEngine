#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include<bits/stdc++.h>
using namespace std;

struct Order{
    int id;
    double price;
    int quantity;
    bool isBuy;
    int version;

    Order(){}
    Order(int id, double price, int quantity, bool  isBuy, int version)
        : id(id), price(price), quantity(quantity), isBuy(isBuy), version(version){}
};

// struct BuyComparator{
//     bool  operator()(const Order &a, const Order &b){
//         return a.price < b.price;
//     }
// };

// struct SellComparator {
//     bool operator()(const Order& a, const Order& b) {
//         return a.price > b.price;
//     }
// };

class OrderBook{
    // Matching: O(log N) per operation using heap
    private:
    map<double, queue<Order>, greater<double>> buyOrders;
    map<double, queue<Order>> sellOrders;

    //priority_queue<Order, vector<Order>, BuyComparator> buyOrders;
    //priority_queue<Order, vector<Order>, SellComparator> sellOrders;

    //for lazy deletion as pq don't support deletion directly
    unordered_map<int, Order> activeOrders;
    //for version storing
    unordered_map<int, int> currentVersion;

    public:
    void addOrder(Order order);
    void matchOrders();

    void cancelOrder(int orderId);
    void modifyOrder(int orderId, double newPrice, int newQuantity);
    void printOrderBook();
};

#endif

