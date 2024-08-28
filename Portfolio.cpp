//
// Created by mz on 27-08-24.
//

#include "Portfolio.h"
#include "YahooFinanceAPI.h"
#include <algorithm>
#include <stdexcept>
void Portfolio::addStock(const Stock& stock) {
    stocks.push_back(stock);
}

void Portfolio::removeStock(const std::string& symbol) {
    auto it = std::remove_if(stocks.begin(), stocks.end(),
                             [&](const Stock& s) { return s.getSymbol() == symbol; });
    if (it != stocks.end()) {
        stocks.erase(it, stocks.end());
    }
}

Stock* Portfolio::getStock(const std::string& symbol) {
    for (auto& stock : stocks) {
        if (stock.getSymbol() == symbol) {
            return &stock;
        }
    }
    return nullptr;  // Stock not found
}

const std::vector<Stock>& Portfolio::getStocks() const {
    return stocks;
}

double Portfolio::Profit(int start_year, int start_month, int start_day, int end_year, int end_month,
                         int end_day) const {
    double profit = 0;
    for (auto& stock : stocks) {
        double start_price = stock.getPriceAtDate(start_year,start_month,start_day);
        double end_price = stock.getPriceAtDate(end_year,end_month,end_day);
        profit = profit + stock.getShares()*(end_price-start_price);
    }
    return profit;
}

std::vector<std::tuple<int, double>> Portfolio::annualProfit(int start_year, int start_month, int start_day,
                                                             int end_year, int end_month, int end_day) const {


    std::vector<std::tuple<int, double>> annual_profits;
    StockAPI stockApi;
    for (int year = start_year; year <= end_year; ++year) {
        int start_m = (year == start_year) ? start_month : 1;
        int start_d = (year == start_year) ? start_day : 1;//
        int end_m = (year == end_year) ? end_month : 12;
        int end_d = (year == end_year) ? end_day : 31; //

        double year_start_value = 0.0;
        double year_end_value = 0.0;

        for (const auto& stock : stocks) {
            double start_price;
            double end_price;
            if(start_d == 1 and start_m ==1){

                 start_price = stockApi.getFirstClosingPriceOfYear(stock.getSymbol(), year);
            }
            else  start_price = stock.getPriceAtDate(year, start_m, start_d);
            if(end_d == 31 && end_m == 12)
            {
                 end_price = stockApi.getLastClosingPriceOfYear(stock.getSymbol(), year);
            }
            else  end_price = stock.getPriceAtDate(year, end_m, end_d);

            double stock_start_value = stock.getShares() * start_price;
            double stock_end_value = stock.getShares() * end_price;

            year_start_value += stock_start_value;
            year_end_value += stock_end_value;
        }

        if (year_start_value == 0) {
            throw std::runtime_error("Initial value of the portfolio is zero. Cannot calculate profit.");
        }

        double annual_profit = year_end_value - year_start_value;
        annual_profits.push_back(std::make_tuple(year, annual_profit));
    }
    return annual_profits;

}