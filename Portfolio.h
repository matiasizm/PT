//
// Created by mz on 27-08-24.
//

#ifndef PT_FINTUAL_PORTFOLIO_H
#define PT_FINTUAL_PORTFOLIO_H

#include"Stock.h"
#include<string.h>
#include <vector>

class Portfolio {
public:
    void addStock(const Stock& stock);
    void removeStock(const std::string& symbol);

    double Profit(int start_year, int start_month,int start_day,int end_year,int end_month,int end_day) const;

    Stock* getStock(const std::string& symbol);
    const std::vector<Stock>& getStocks() const;
    std::vector<std::tuple<int, double>> annualProfit(int start_year, int start_month,int start_day,int end_year,int end_month,int end_day) const;

private:
    std::vector<Stock> stocks;
};


#endif //PT_FINTUAL_PORTFOLIO_H
