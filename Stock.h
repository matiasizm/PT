//
// Created by mz on 27-08-24.
//

#ifndef PT_FINTUAL_STOCK_H
#define PT_FINTUAL_STOCK_H

#include <string>


class Stock {
public:
    Stock(const std::string& symbol,int shares);

    std::string getSymbol() const;
    double getPriceAtDate(const int year,const int month,const int day) const;
    double getShares() const;
    double getTotalValue(double price) ;

    double getFirstClosingPriceOfYear(const std::string& symbol, int year);

private:
    std::string symbol;
    double shares;
};


#endif //PT_FINTUAL_STOCK_H
