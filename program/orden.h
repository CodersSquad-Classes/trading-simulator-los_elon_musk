//orden.h
#ifndef ORDEN_H
#define ORDEN_H
#include <string>
#include <iostream>

using namespace std;

enum OrderType {Buy, Sell};

class orden {
    private:
        int trader_id;
        OrderType type; 
        int price;
        int quantity;
        int timestamp; 
        string ticker;
    public:
        orden();
        orden(int trader_id, OrderType type, int price, int quantity, int timestamp, string ticker);
        int getTrader_id() const;
        OrderType getType() const;
        int getPrice() const;
        int getQuantity() const;
        int getTimestamp() const;
        string getTicker() const;
        void reduceQuantity(int amount);
};


#endif