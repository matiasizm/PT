#include "Date.h"
#include <map>
#include <set>

Date::Date(int year, int month, int day) {
    date = {};
    date.tm_year = year - 1900; // tm_year cuenta desde 1900
    date.tm_mon = month - 1;    // tm_mon es de 0 (enero) a 11 (diciembre)
    date.tm_mday = day;
    normalize();
}

bool Date::isWeekend() const {
    return date.tm_wday == 0 || date.tm_wday == 6; // Domingo = 0, Sábado = 6
}

bool Date::isHoliday() const {
    // Define aquí los feriados legales de EE.UU.
    static const std::map<int, std::set<int>> holidays = {
            { 0, {1} },     // Año Nuevo (1 de enero)
            { 6, {4} },     // Día de la Independencia (4 de julio)
            { 11, {25} },   // Navidad (25 de diciembre)
            // Otros feriados se pueden añadir aquí
    };

    // Busca si el mes y el día son un feriado
    auto month_it = holidays.find(date.tm_mon);
    if (month_it != holidays.end() && month_it->second.count(date.tm_mday)) {
        return true;
    }
    return false;
}

void Date::previousDay() {
    date.tm_mday -= 1;
    mktime(&date); // Normaliza la fecha
}

void Date::nextDay() {
    date.tm_mday -= 1;
    mktime(&date); // Normaliza la fecha
}

void Date::normalize() {
    mktime(&date); // Normaliza la fecha
}

std::string Date::toString() const {
    char buffer[11];
    strftime(buffer, 11, "%Y-%m-%d", &date);
    return std::string(buffer);
}

//function to convert date to Timestamp
time_t Date::convertToTimestamp(int year, int month, int day) {
    std::tm timeStruct = {};

    timeStruct.tm_year = year - 1900;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_mday = day;
    timeStruct.tm_hour = 0;
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;
    timeStruct.tm_isdst = -1;

    return std::mktime(&timeStruct);
}



Date Date::getPreviousBusinessDayIfHoliday() {
    if (isHoliday()) {
        do {
            previousDay();
        } while (isWeekend());
    }
    return *this;
}

Date Date::getNextBusinessDayIfHoliday() {
    if (isHoliday()) {
        do {
            nextDay();
        } while (isWeekend());
    }
    return *this;
}


int Date::getYear() const {
    return date.tm_year + 1900; // tm_year cuenta desde 1900
}

int Date::getMonth() const {
    return date.tm_mon + 1; // tm_mon es de 0 (enero) a 11 (diciembre)
}

int Date::getDay() const {
    return date.tm_mday;
}
