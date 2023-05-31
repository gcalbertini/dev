#include "Chrono.hpp"

namespace Chrono
{
    Date::Date(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd}
    {
        if (!is_date(yy, mm, dd))
            throw Invalid{};
    }

    const Date &default_date()
    {
        static Date dd{1995, Month::sep, 29};
        return dd;
    }

    Date::Date() : y{default_date().getYear()},
                   m{default_date().getMonth()},
                   d{default_date().getDay()}
    {
        // default constructor
    }

    void Date::add_month(int n)
    {
        int totalMonths = static_cast<int>(m) + n;

        int yearOffset = totalMonths / 12;
        int monthOffset = totalMonths % 12;

        y += yearOffset;
        Month mOff = static_cast<Month>(monthOffset);

        // Handle cases where the resulting month is outside the range 0-11
        if (mOff < Month::jan)
        {
            m = static_cast<Month>(static_cast<int>(Month::dec) + 1 + monthOffset);
            --y;
        }
        else if (mOff > Month::dec)
        {
            m = static_cast<Month>(monthOffset - static_cast<int>(Month::dec) - 1);
            ++y;
        }
    }

    void Date::add_year(int n)
    {
        if (m == Month::feb && d == 29 && !leapyear(y + n))
        {
            m = Month::mar;
            d = 1;
        }
        y += n;
    }

    void Date::add_day(int n)
    {
        d++;

        int daysInMonth = getDaysInMonth(y, m);

        if (d > daysInMonth)
        {
            d = 1;
            int nextMonth = static_cast<int>(m) + 1;
            if (nextMonth > 11)
            {
                nextMonth = 0;
                y++;
            }
            m = static_cast<Month>(nextMonth);
        }
    }

    int getDaysInMonth(const int &y, const Month &m)
    {
        int days_in_month;

        switch (m)
        {
        case Month::feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            days_in_month = 30;
            break;
        default:
            days_in_month = 31;
            break;
        }

        return days_in_month;
    }

    bool is_date(int y, Month m, int d)
    {
        // assume y is valid
        if (d <= 0)
            return false;
        if (m < Month::jan || Month::dec < m)
            return false;

        int days_in_month = getDaysInMonth(y, m);

        if (days_in_month < d)
            return false;

        return true;
    }

    bool leapyear(int y)
    {
        // year is a leap year if it is divisible by 4, except for years that are divisible by 100
        // BUT years that are divisible by 400 are still considered leap years

        bool is_leapyear = (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) ? true : false;
        return is_leapyear;
    }

    bool operator==(const Date &a, const Date &b)
    {
        return a.getYear() == b.getYear() &&
               a.getMonth() == b.getMonth() &&
               a.getDay() == b.getDay();
    }

    std::istream &operator>>(std::istream &is, Date &dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is)
            return is;
        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
        {
            is.clear(std::ios_base::failbit); // oops: format error so set failbit
            return is;
        }
        dd = Date(y, Month(m), d); // update dd
        return is;
    }

    bool operator!=(const Date &a, const Date &b)
    {
        return !(a == b);
    }

    std::ostream &operator<<(std::ostream &os, const Date &dd)
    {
        return os << '(' << dd.getYear() << ',' << static_cast<int>(dd.getMonth()) << ',' << dd.getDay() << ')';
    }

    Day day_of_week(const Date &d)
    {
        int month = static_cast<int>(d.getMonth());
        int year = d.getYear();
        int day = d.getDay();

        // Adjust months of jan and feb (and their years) based on the convention; requires march = 3, apr = 4, ..., jan = 13, feb = 14
        if (month < 2)
        {
            month += 12;
            year--;
        }

        // Zeller's Congruence algorithm: unfortunately, in the truncating way most computer languages implement
        // the remainder function, −2 mod 7 returns a result of −2. So, to implement Zeller's congruence on a computer,
        // the formulas should be altered slightly to ensure a positive numerator (+5J)
        int q = day;
        int m = month + 1; // jan was set to 0, but algo assumed jan was 1 --> requires march = 3, apr = 4, ..., dec = 12
        int K = year % 100;
        int J = year / 100;

        int h = (q + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

        // Adjust the result to match the convention (Sunday is 0)
        return static_cast<Day>((h + 6) % 7 + 0);
    }

    Date next_Sunday(const Date &d)
    {
        Date next = d;
        next.add_day(1); // Start with the next day

        while (day_of_week(next) != Day::sunday)
        {
            next.add_day(1);
        }

        return next;
    }

    Date next_weekday(const Date &d)
    {
        Date next = d;
        next.add_day(1); // Start with the next day

        while (day_of_week(next) == Day::saturday || day_of_week(next) == Day::sunday)
        {
            next.add_day(1);
        }

        return next;
    }

}
