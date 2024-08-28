//
// Created by mz on 27-08-24.
//

#ifndef STOCKAPI_H
#define STOCKAPI_H

#include <string>
#include <curl/curl.h>

class StockAPI {
public:
    StockAPI();
    ~StockAPI();
    std::string getStockInfo(const std::string& symbol, int year, int month, int day);
    double getStockPrice(const std::string& jsonData);
    double getFirstClosingPriceOfYear(const std::string &symbol, int year);
    double getLastClosingPriceOfYear(const std::string &symbol, int year);

private:
    CURL* curl;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);


};

#endif // STOCKAPI_H
