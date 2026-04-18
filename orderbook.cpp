#include "orderbook.h"

void OrderBook::addOrder(Order order){
    //when order placed initially it is active
    activeOrders[order.id] = order;
    currentVersion[order.id]=order.version;

    if(order.isBuy){
        buyOrders[order.price].push(order);
    }
    else sellOrders[order.price].push(order);

    matchOrders();
}


// Matching: O(log N) per operation using heap
void OrderBook::matchOrders(){
    while(!buyOrders.empty() && !sellOrders.empty()){
        //taking top 2 orders to trade from map, It will be a pair of double & queue
        auto bestBuyOrders = buyOrders.begin();
        auto bestSellOrders = sellOrders.begin();


        //checking weather bestBuyOrders iterator hold a valid list of orders or not
        if(bestBuyOrders->second.empty()){
            buyOrders.erase(bestBuyOrders);
            continue;
        }
        if(bestSellOrders->second.empty()){
            sellOrders.erase(bestSellOrders);
            continue;
        }

        Order buy = bestBuyOrders->second.front();
        Order sell = bestSellOrders->second.front();

        //handling cancelled orders after placing
        if(activeOrders.count(buy.id)==0 || buy.version!=currentVersion[buy.id]){
            bestBuyOrders->second.pop();
            if(bestBuyOrders->second.empty()){
                buyOrders.erase(bestBuyOrders);
            }
            continue;
        }
        if(activeOrders.count(sell.id)==0 || sell.version!=currentVersion[sell.id]){
            bestSellOrders->second.pop();
            if(bestSellOrders->second.empty()){
                sellOrders.erase(bestSellOrders);
            }
            continue;
        }

        if(buy.price >= sell.price){
            int tradedQty = min(buy.quantity, sell.quantity);
            cout<< "Trade: BUY ID " << buy.id 
                << " matched with SELL ID " << sell.id
                << " Quantity: " << tradedQty 
                << " Price: " << sell.price << endl;
            //printOrderBook();  

            if(buy.quantity > tradedQty){
                activeOrders[buy.id].quantity-=tradedQty;
                bestBuyOrders->second.front().quantity-=tradedQty;
            }
            else{
                activeOrders.erase(buy.id);
                bestBuyOrders->second.pop();
            }

            if(sell.quantity > tradedQty){
                activeOrders[sell.id].quantity-=tradedQty;
                bestSellOrders->second.front().quantity-=tradedQty;
            }
            else{
                activeOrders.erase(sell.id);
                bestSellOrders->second.pop();
            }

            if(bestBuyOrders->second.empty()) buyOrders.erase(bestBuyOrders);
            if(bestSellOrders->second.empty()) sellOrders.erase(bestSellOrders);
        }
        else break; //no more matching happening, not possible
    }
}

void OrderBook::cancelOrder(int orderId){
    // Lazy deletion avoids O(N) removal
    if(activeOrders.erase(orderId)){
        cout<<"Order with OrderId- "<<orderId<<" is cancelled"<<endl;
    }
    else cout<<"Order with OrderId- "<<orderId<<" already executed"<<endl;
}



void OrderBook::modifyOrder(int orderId, double newPrice, int newQuantity){
    if(activeOrders.find(orderId) == activeOrders.end()){
        cout<<"Order with OrderId- "<<orderId<<" not found or already executed"<<endl;
        return;
    }

    Order oldOrder = activeOrders[orderId];
    Order newOrder = oldOrder;
    newOrder.price=newPrice;
    newOrder.quantity=newQuantity;
    newOrder.version= currentVersion[orderId]+1;

    currentVersion[orderId] = newOrder.version;
    activeOrders[orderId] = newOrder;

    if(newOrder.isBuy)
        buyOrders[newOrder.price].push(newOrder);
    else
        sellOrders[newOrder.price].push(newOrder);

    cout << "Order " << orderId << " modified: Price=" << newPrice 
         << ", Quantity=" << newQuantity << endl;

    matchOrders();
}

void OrderBook::printOrderBook() {
    cout << "\n===BUY ORDERS===\n";

    for(auto &level : buyOrders){
        auto q = level.second;
        while(!q.empty()){
            Order o = q.front();
            q.pop();

            if(activeOrders.count(o.id) == 0 || o.version != currentVersion[o.id])
                continue;
            cout<< "ID: " << o.id 
                << " Price: " << o.price 
                << " Qty: " << o.quantity << endl;
        }
    }

    cout << "\n===SELL ORDERS===\n";
    for(auto &level : sellOrders){
        auto q = level.second;
        while(!q.empty()){
            Order o = q.front();
            q.pop();

            if(activeOrders.count(o.id) == 0 || o.version != currentVersion[o.id])
                continue;
            cout<< "ID: " << o.id 
                << " Price: " << o.price 
                << " Qty: " << o.quantity << endl;
        }
    }
    cout << "========================\n";
}