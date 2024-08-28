#ifndef DATE_H
#define DATE_H

#include <string>
#include <ctime>

class Date {
private:
    std::tm date;

    bool isWeekend() const;
    bool isHoliday() const;
    void normalize();

public:
    Date(int year, int month, int day);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    void nextDay();
    void previousDay();
    std::string toString() const;
    Date getPreviousBusinessDayIfHoliday();
    Date getNextBusinessDayIfHoliday();

    time_t convertToTimestamp(int year, int month, int day);
};

#endif // DATE_H
