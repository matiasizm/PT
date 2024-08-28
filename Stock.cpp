//
// Created by mz on 27-08-24.
//

#include "Stock.h"
#include "YahooFinanceAPI.h"

Stock::Stock(const std::string& symbol,int shares)
        : symbol(symbol), shares(shares) {}

std::string Stock::getSymbol() const {
    return symbol;
}

double Stock::getShares() const {
    return shares;
}

double Stock::getPriceAtDate(const int year,const int month,const int day) const {
    StockAPI api;
    std::string stockData = api.getStockInfo(symbol, year, month, day);
    double closingPrice = api.getStockPrice(stockData);
    return closingPrice;
}

double Stock::getTotalValue(double price) {
    return shares*price;
}