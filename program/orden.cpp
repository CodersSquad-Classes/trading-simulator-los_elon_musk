//orden.cpp
#include "orden.h"

using namespace std;

orden::orden(){}

orden::orden(int trader_id, OrderType type, int price, int quantity, int timestamp, string ticker) {
    this->trader_id = trader_id;
    this->type = type;
    this->price = price;
    this->quantity = quantity;
    this->timestamp = timestamp;
    this->ticker = ticker;
}

int orden::getTrader_id() const {
    return trader_id;
}

OrderType orden::getType() const {
    return type;
}

int orden::getPrice() const {
    return price;
}

int orden::getQuantity() const {
    return quantity;
}

int orden::getTimestamp() const {
    return timestamp;
}

string orden::getTicker() const {
    return ticker;
}

void orden::reduceQuantity(int amount){
    quantity -= amount;
    if (quantity < 0) quantity = 0;    
}
