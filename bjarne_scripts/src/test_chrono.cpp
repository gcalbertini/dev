#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept> // for error
#include <iostream>  //for std namespace stuff
#include <fstream>
#include <vector>
#include "utils.hpp"
#include "Chrono.hpp"

namespace Chrono
{

    // Test fixture for the Date class
    class DateTest : public ::testing::Test
    {
    protected:
        // You can add setup and teardown methods here if needed

        // Commonly used variables for tests
        int year;
        Month month;
        int day;

        // Helper method to compare two Date objects
        void expectSameDates(const Date &actual, const Date &expected)
        {
            EXPECT_EQ(actual.getYear(), expected.getYear());
            EXPECT_EQ(actual.getMonth(), expected.getMonth());
            EXPECT_EQ(actual.getDay(), expected.getDay());
        }

        void assertDateEquals(const Date &actual, int y, Month m, int d)
        {
            EXPECT_EQ(actual.getYear(), y);
            EXPECT_EQ(actual.getMonth(), m);
            EXPECT_EQ(actual.getDay(), d);
        }
    };

    // Test cases for the Date class
    TEST_F(DateTest, DefaultConstructor)
    {
        Date date;
        // Add assertions to test the behavior of the default constructor
        assertDateEquals(date, 1995, Month::sep, 29);
    }

    TEST_F(DateTest, SameDates)
    {
        Date date1(2023, Month::jan, 31);
        Date date2(2023, Month::jan, 31);
        expectSameDates(date1, date2);
    }

    TEST_F(DateTest, ConstructorWithParameters)
    {
        // Create a Date object using the constructor with parameters
        Date date(2023, Month::jan, 31);
        // Add assertions to test the behavior of the constructor with parameters
        assertDateEquals(date, 2023, Month::jan, 31);
    }

    // Test the add_day() function of Date
    TEST_F(DateTest, AddDay)
    {
        Date d(2023, Month::may, 31);
        d.add_day(1);
        // Perform assertions
        assertDateEquals(d, 2023, Month::jun, 1);
    }

    // Example test case for the leapyear function
    TEST(ChronoTest, LeapYear)
    {
        EXPECT_TRUE(leapyear(2020));
        EXPECT_FALSE(leapyear(2021));
        EXPECT_FALSE(leapyear(2100));
        // Add more assertions to test the leapyear function
    }

    // Example test case for the day_of_week function
    TEST(ChronoTest, DayOfWeek)
    {
        Date date(2023, Month::feb, 5);
        EXPECT_EQ(day_of_week(date), Day::sunday);

        Date d(2023, Month::may, 31);
        EXPECT_EQ(day_of_week(d), Day::wednesday);
    }

    // Test the operator<< for Date
    TEST(OperatorOutputTest, WritesCorrectly)
    {
        // Create a temporary file for testing
        std::string filename = "test_output.txt";

        // Open the file for writing
        std::ofstream outputFile(filename);

        // Create a Date object to write to the file
        Date date(2023, Month::jan, 15);

        // Use the overloaded operator<< to write the Date object to the file
        outputFile << date;

        // Close the file
        outputFile.close();

        // Open the file for reading
        std::ifstream inputFile(filename);

        // Read the contents of the file
        std::string fileContents;

        // std::getline(input_stream, string_variable, optional_delimiter_else '\n');
        // read an entire line of input, including any whitespace characters, until delimiter found
        std::getline(inputFile, fileContents);

        // Close the file
        inputFile.close();

        // Verify the contents of the file
        std::string expectedContents = "(2023,0,15)";
        EXPECT_EQ(fileContents, expectedContents);

        // Clean up the temporary file; returns a pointer (const char *) to a null-terminated character array for removal
        std::remove(filename.c_str());
    }

    // Add more test cases for other functions in the Chrono namespace as needed

} // namespace Chrono
