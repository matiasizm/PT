
#include <iostream>
#include <tuple>  // For std::tuple
#include "Stock.h"
#include "Portfolio.h"
#include "YahooFinanceAPI.h"

int main() {

    Portfolio portfolio;
    portfolio.addStock(Stock("IBM",50));
    portfolio.addStock(Stock("AAPL",10));
    portfolio.addStock(Stock("AMD",100));


    double portfolio_profit = portfolio.Profit(2021, 5, 20,2023,1,20);
    std::cout << "PortFolio Profit: " << portfolio_profit << std::endl;

    std::vector<std::tuple<int, double>> annual_profit = portfolio.annualProfit(2015, 5, 20,2018,5,7);
    // Print the profit for each year
    for (const auto& [year, profit] : annual_profit) {
        std::cout << "Year: " << year << ", Profit: $" << profit << std::endl;
    }





    return 0;
}
