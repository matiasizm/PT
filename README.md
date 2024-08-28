# Portfolio Profit Calculation

## Overview

This project is a simple C++ program that models a financial portfolio containing stocks and provides functionality to calculate the profit of the portfolio over a given period. The program can also calculate the annualized return or profit for each year within the specified date range.

## Project Structure

The project consists of the following main components:

- **Stock**: Represents an individual stock in the portfolio.
- **Portfolio**: Manages a collection of `Stock` objects and provides methods to calculate the profit and annualized return.
- **StockAPI**: A utility class to retrieve stock prices from a JSON response (e.g., from an external API like Yahoo Finance).

### Files

- **Stock.h/Stock.cpp**: Defines and implements the `Stock` class. This class includes methods to retrieve the stock symbol, the number of shares, the value of the stock at a specific date, and the total value of the stock.
- **Portfolio.h/Portfolio.cpp**: Defines and implements the `Portfolio` class. This class includes methods to add/remove stocks, calculate total portfolio value, and compute profits over a specified date range.
- **StockAPI.h/StockAPI.cpp**: Provides the `StockAPI` class, which handles the retrieval of stock prices from a JSON response string.
- **main.cpp**: The entry point of the program, demonstrating how to use the `Portfolio` and `Stock` classes to manage a portfolio and calculate profits.

## Functionality

### Stock Class

The `Stock` class is responsible for representing a stock within the portfolio. It has the following key methods:

- `getPriceAtDate(int year, int month, int day)`: Retrieves the price of the stock on a given date using the `StockAPI` class.
- `getTotalValue(double price)`: Calculates the total value of the stock based on the given price and the number of shares owned.

### Portfolio Class

The `Portfolio` class manages a collection of `Stock` objects and provides methods to calculate the profit of the portfolio:

- `Profit(int start_year, int start_month, int start_day, int end_year, int end_month, int end_day)`: Returns the profit for each year between the specified dates.

### StockAPI Class

The `StockAPI` class provides methods for extracting the stock price from a JSON response:

- `getStockPrice(const std::string& jsonData)`: Parses the JSON data to retrieve the closing price of the stock. It returns `std::optional<double>` to indicate that the value might not be present.

## How to Use

### Compilation

To compile the project, use the following command:

```bash
g++ -std=c++17 main.cpp Portfolio.cpp Stock.cpp StockAPI.cpp -o PortfolioApp -lcurl
