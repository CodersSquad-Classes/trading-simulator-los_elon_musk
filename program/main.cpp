//main.cpp
#include <iostream>
#include <string>
#include "orden.h"
#include "orderBook.h"

using namespace std;

int main(){
    OrderBook ob;

    // BUY orders
    ob.addOrder(orden(1, Buy, 100, 10, 1, "AAPL"));  // trader 1 buy 10 @100
    ob.addOrder(orden(2, Buy, 102, 5,  2, "AAPL"));  // trader 2 buy 5 @102 (the best price)
    ob.addOrder(orden(3, Buy, 101, 20, 3, "AAPL"));  // trader 3 buy 20 @101
    
 // SELL orders without matching
    ob.addOrder(orden(4, Sell, 110, 10, 4, "AAPL")); // sell 10 @110
    ob.addOrder(orden(5, Sell, 108, 5,  5, "AAPL")); // sell 5 @108

    cout << "\n=== ORDER BOOK AFTER ORDERS WITH NO MATCH ===\n";
    ob.printOrderBook();

    // Matching orders
    ob.addOrder(orden(6, Sell, 101, 7, 6, "AAPL"));  // sell 7 @101 (match with BUY >=101)
    ob.addOrder(orden(7, Sell, 99,  50, 7, "AAPL")); // sell 50 @99 (match with almost any BUY)

    cout << "\n=== ORDER BOOK AFTER MATCHES ===\n";
    ob.printOrderBook();

  

    return 0;
}
