
/*
Convert C to K. Just checking env is set up ok.
*/

#include "utils.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::string; // another convention to extract what is needed from namespacec std

double ctock(std::string should_be_cel);

// Example usage of error()
int main()
{
    std::string c;  
    try
    {
        cin >> c;

        // check double or in fail state
        if (!cin || !isDouble(c))
        {
            error("Input failed or error occurred. Using 0 C instead.");
        }
        else if (std::stod(c) < -273.15)
        {
            error("Absolute zero is lowest possible temp reached. Stopping.");
        }

        double k = ctock(c);
        cout << k << '\n';
        return 0; // indicate success as usual
    }
    catch (const std::runtime_error &e)
    {
        // what() extracts error message from runtime error
        std::cout << "Error: " << e.what() << std::endl;

        // return a default value of 0 Celsius
        cout << ctock("0") << '\n';

        return 0;
    }
    catch (...)
    {
        // Generic catch-all block for any other type of exception
        std::cerr << "Idk what this error is!" << std::endl;
        return 2;
    }
}

double ctock(std::string C) // converts Celsius to Kelvin
{
    return std::stod(C) + 273.15;
}

// now simply compile with cmake or g++ ctok.cpp utils.hpp -o ctok
// then execute ./ctok (note: on windows)