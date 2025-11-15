//orderBook.h
#ifndef ORDENBOOK_H
#define ORDENBOOK_H
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "orden.h"

using namespace std;

struct BuyComparator {
    bool operator()(const orden& a, const orden& b) const;
};

struct SellComparator {
    bool operator()(const orden& a, const orden& b) const;
};

class OrderBook {
    private:
        priority_queue<orden, vector<orden>, BuyComparator> buyOrders;
        priority_queue<orden, vector<orden>, SellComparator> sellOrders;
        int currentTimestamp;
        bool isMatchPossible() const;
        int executeTrade();
        bool tryMatchBest();
    public:
        OrderBook();
        void addOrder(const orden& o);
        void matchOrders();
        void printOrderBook() const;

};

#endif