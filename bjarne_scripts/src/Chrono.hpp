#ifndef MY_CHRONO_HPP // lowercase as there is already a std library chrono class much more robust than that of this exercise
#define MY_CHRONO_HPP

#ifndef UTILS_HPP
#define UTILS_HPP
#include "utils.hpp"
#endif // UTILS_HPP

namespace Chrono
{
    enum class Month
    {
        jan,
        feb,
        mar,
        apr,
        may,
        jun,
        jul,
        aug,
        sep,
        oct,
        nov,
        dec
    };

    enum class Day
    {
        sunday,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday
    };

    class Date
    {
    public:
        class Invalid
        {
        };                           // throw as an exception
        Date(int y, Month m, int d); // check for valid data and init
        Date();                      // default contructor; default copy instrctions fine for now

        int getDay() const { return d; }
        Month getMonth() const { return m; }
        int getYear() const { return y; }

        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        int y;
        Month m;
        int d;
    };

    int getDaysInMonth(const int &y, const Month &m);
    bool is_date(int y, Month m, int d);
    bool leapyear(int y);
    bool operator==(const Date &a, const Date &b);
    bool operator!=(const Date &a, const Date &b);
    std::ostream &operator<<(std::ostream &os, const Date &d);
    std::istream &operator>>(std::istream &is, Date &dd);
    Day day_of_week(const Date &d);
    Date next_Sunday(const Date &d);
    Date next_weekday(const Date &d);

} // Chrono

#endif // MY_CHRONO_HPP

