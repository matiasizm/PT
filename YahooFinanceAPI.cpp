//
// Created by mz on 27-08-24.
//

#include "YahooFinanceAPI.h"
#include <iostream>
#include <ctime>
#include <stdexcept>
#include "Date.h"
 // Include the optional header
StockAPI::StockAPI() {
    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }
}

StockAPI::~StockAPI() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

size_t StockAPI::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        return 0;
    }
    return newLength;
}

std::string StockAPI::getStockInfo(const std::string& symbol, int year, int month, int day) {
    std::string readBuffer;
    //check if there is a working day in US, if holiday, go to the previous working day
    Date input_date(year, month, day);
    Date valid_date = input_date.getPreviousBusinessDayIfHoliday();
    year = valid_date.getYear();
    month = valid_date.getMonth();
    day = valid_date.getDay();


    if (curl) {
        time_t timestamp = valid_date.convertToTimestamp(year, month, day);
        std::string url = "https://query1.finance.yahoo.com/v8/finance/chart/" + symbol +
                          "?period1=" + std::to_string(timestamp) +
                          "&period2=" + std::to_string(timestamp + 86400) +  // Sumar 86400 segundos para obtener el siguiente día
                          "&interval=1d";

        //the lines below are use because the api require a certain user agent and connection header
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: StockAPI/1.0");
        headers = curl_slist_append(headers, "Accept: */*");
        headers = curl_slist_append(headers, "Cache-Control: no-cache");
        headers = curl_slist_append(headers, "Connection: keep-alive");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");

        CURLcode res = curl_easy_perform(curl);

        curl_slist_free_all(headers);

        if (res != CURLE_OK) {
            throw std::runtime_error("CURL error: " + std::string(curl_easy_strerror(res)));
        }

        if (readBuffer.find("Too Many Requests") != std::string::npos) {
            throw std::runtime_error("Too many requests, please try again later.");
        }
    }

    return readBuffer;
}

double StockAPI::getStockPrice(const std::string& jsonData) {
    std::string closeKey = "\"close\":[";
    size_t startPos = jsonData.find(closeKey);

    if (startPos != std::string::npos) {
        startPos += closeKey.length();
        size_t endPos = jsonData.find("]", startPos);
        if (endPos != std::string::npos) {
            std::string closePriceStr = jsonData.substr(startPos, endPos - startPos);
            try {
                return std::stod(closePriceStr);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Failed to parse closing price from JSON.");
            }
        } else {
            throw std::runtime_error("Closing price array not properly terminated.");
        }
    } else {
        throw std::runtime_error("Could not find closing price in JSON.");
    }
}

double StockAPI::getFirstClosingPriceOfYear(const std::string& symbol, int year) {
    Date firstDate(year, 1, 1);
    Date validDate = firstDate.getNextBusinessDayIfHoliday();  // Obtener el primer día hábil del año
    std::string jsonData;
    double closingPrice = 0.0;

    while (true) {
        try {
            jsonData = getStockInfo(symbol, validDate.getYear(), validDate.getMonth(), validDate.getDay());
            closingPrice = getStockPrice(jsonData);
            break;  // Si se obtiene un precio válido, salir del bucle
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << ". Intentando siguiente día hábil..." << std::endl;
            validDate.nextDay();  // Mover al siguiente día
            validDate = validDate.getNextBusinessDayIfHoliday();  // Ajustar si es necesario
        }
    }

    return closingPrice;
}

double StockAPI::getLastClosingPriceOfYear(const std::string &symbol, int year)  {
    Date lastDate(year, 12, 31);
    Date validDate = lastDate.getPreviousBusinessDayIfHoliday();  // Obtener el primer día hábil del año
    std::string jsonData;
    double closingPrice = 0.0;

    while (true) {
        try {
            jsonData = getStockInfo(symbol, validDate.getYear(), validDate.getMonth(), validDate.getDay());
            closingPrice = getStockPrice(jsonData);
            break;  // Si se obtiene un precio válido, salir del bucle
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << ". Intentando siguiente día hábil..." << std::endl;
            validDate.previousDay();  // Mover al siguiente día
            validDate = validDate.getNextBusinessDayIfHoliday();  // Ajustar si es necesario
        }
    }

    return closingPrice;
}