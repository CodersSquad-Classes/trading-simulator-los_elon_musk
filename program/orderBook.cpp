//orderBook.cpp
#include "orderBook.h"
#include <iostream>

OrderBook::OrderBook(): currentTimestamp(0) {}

bool BuyComparator::operator()(const orden& a, const orden& b) const {
    if (a.getPrice() != b.getPrice()){          //Comparamos orden y si son 
        return a.getPrice() < b.getPrice();     //iguales no entra al if y se 
    }                                           //comparan por quien llego antes con el timestamp
    return a.getTimestamp() > b.getTimestamp(); // ENTIENDE IJITO
}

bool SellComparator::operator()(const orden& a, const orden& b) const {
    if (a.getPrice() != b.getPrice()) {         //Mismo pero con sell = venta xd
        return a.getPrice() > b.getPrice();
     } 
    return a.getTimestamp() > b.getTimestamp(); 
}

void OrderBook::addOrder(const orden& o) {
    if (o.getType() == Buy) {
        buyOrders.push(o);
    } 
    else {
        sellOrders.push(o);
    }
    matchOrders();
}

bool OrderBook::isMatchPossible() const {
    if (buyOrders.empty() || sellOrders.empty()) {
        return false;
    }
    const orden& bestBuy  = buyOrders.top();
    const orden& bestSell = sellOrders.top();
    return bestBuy.getPrice() >= bestSell.getPrice();
}

int OrderBook::executeTrade() {
    if (buyOrders.empty() || sellOrders.empty()) {
        return 0;
    }
    // Sacamos copias de las órdenes top
    orden buy = buyOrders.top();
    orden sell = sellOrders.top();
    buyOrders.pop();
    sellOrders.pop();

    // amount = min(buy.quantity, sell.quantity)
    int amount = std::min(buy.getQuantity(), sell.getQuantity());

    // Reducir cantidades (usa el método de orden)
    buy.reduceQuantity(amount);
    sell.reduceQuantity(amount);

    // Registrar/imprimir el trade (precio de ejecución: puedes decidir usar sell.getPrice() o buy.getPrice() o midpoint)
    int execPrice = sell.getPrice(); // por ejemplo: ejecutar al precio del maker (sell price) -- decide según política
    cout << "TRADE: " << amount << " " << buy.getTicker() << " @ " << execPrice
    << " (buyTrader=" << buy.getTrader_id() << ", sellTrader=" << sell.getTrader_id() << ")\n";

    // Si alguna orden aún tiene cantidad > 0, la volvemos a insertar en su cola
    if (buy.getQuantity() > 0) buyOrders.push(buy);
    if (sell.getQuantity() > 0) sellOrders.push(sell);

    return amount;
}

// Intenta un solo match: si es posible lo ejecuta y retorna true; si no posible, retorna false.
bool OrderBook::tryMatchBest() {
    if (!isMatchPossible()){
        return false;
    }
    executeTrade();
    return true;
}

// Ejecuta todos los matches posibles
void OrderBook::matchOrders() {
    while (tryMatchBest()) {} // loop hasta que ya no exista match
}

// Imprime un snapshot simple del libro (solo top N si quieres)
void OrderBook::printOrderBook() const {
    cout << "\n---------------------- ORDER BOOK ----------------------\n";
    cout << "   BUY (BIDS)                       |        SELL (ASKS)\n";
    cout << "---------------------------------------------------------\n";
    cout << "Qty     Price     Time              |   Price    Qty    Time\n";
    cout << "---------------------------------------------------------\n";

    // Hacemos copias temporales de las priority queues
    auto buyCopy = buyOrders;
    auto sellCopy = sellOrders;

    // Vamos a imprimir mientras haya órdenes en cualquiera lado
    while (!buyCopy.empty() || !sellCopy.empty()) {
        // Lado BUY
        if (!buyCopy.empty()) {
            const orden& b = buyCopy.top();
            cout << setw(4) << b.getQuantity() << "   "
                 << setw(7) << fixed << setprecision(2) << b.getPrice() << "   "
                 << setw(6) << b.getTimestamp();
            buyCopy.pop();
        } else {
            // Si ya no hay BUY, imprimimos espacios
            cout << "                          ";
        }

        cout << "    |   ";

        // Lado SELL
        if (!sellCopy.empty()) {
            const orden& s = sellCopy.top();
            cout << setw(7) << fixed << setprecision(2) << s.getPrice() << "   "
                 << setw(4) << s.getQuantity() << "   "
                 << setw(6) << s.getTimestamp();
            sellCopy.pop();
        }

        cout << "\n";
    }

    cout << "---------------------------------------------------------\n";
}
