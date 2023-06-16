#include <iostream>
#include <vector>

double *get_from_jack(int *count)
{
    // Example implementation
    double *data = new double[4];
    data[0] = 100.1;
    data[1] = 10.5999;
    data[2] = 10.5;
    data[3] = 1234.5;
    *count = 4;
    return data;
}

std::vector<double> *get_from_jill()
{
    // Example implementation
    std::vector<double> *data = new std::vector<double>();
    data->push_back(40.4);
    data->push_back(5.5);
    data->push_back(6.66);
    return data;
}

void worst_fct()
{
    int jack_count = 0; // will be updated
    double *jack_data = get_from_jack(&jack_count);
    std::vector<double> *jill_data = get_from_jill();
    // Process the data
    double h = -1;     // ugh..magic number
    double *jack_high; // pts to element with highest value
    double *jill_high;
    for (int i = 0; i < jack_count; ++i)
    {
        if (h < jack_data[i])
        {
            jack_high = &jack_data[i]; // save address of highest element
            h = jack_data[i];          // update largest element
        }
    }

    h = -1; // another magic number
    for (int i = 0; i < jill_data->size(); ++i)
    {
        if (h < (*jill_data)[i]) // ugh...bizarre notation; note that [] binds tighter than *, hence the parenthesis
        {
            jill_high = &(*jill_data)[i]; // save address of largest element
            h = (*jill_data)[i];          // update largest element
        }
    }

    std::cout << "Jack's highest: " << *jack_high << std::endl;
    std::cout << "Jill's highest: " << *jill_high << std::endl;

    // Clean up the allocated memory
    delete[] jack_data;
    delete jill_data;
}

void bad_fct()
{
    int jack_count = 0; // will be updated
    double *jack_data = get_from_jack(&jack_count);
    std::vector<double> *jill_data = get_from_jill();
    std::vector<double> &v = *jill_data; // eliminates funky notation
    // Process the data
    double h = -1;     // ugh..magic number
    double *jack_high; // pts to element with highest value
    double *jill_high;
    for (int i = 0; i < jack_count; ++i)
    {
        if (h < jack_data[i])
        {
            jack_high = &jack_data[i]; // save address of highest element
            h = jack_data[i];          // update largest element
        }
    }

    h = -1; // another magic number
    for (int i = 0; i < v.size(); ++i)
    {
        if (h < v[i]) // better notation matches that of Jack's
        {
            jill_high = &v[i]; // save address of largest element
            h = v[i];          // update largest element
        }
    }

    std::cout << "Jack's highest: " << *jack_high << std::endl;
    std::cout << "Jill's highest: " << *jill_high << std::endl;

    // Clean up the allocated memory
    delete[] jack_data;
    delete jill_data;
}

template <typename Iterator>
Iterator high(Iterator first, Iterator last)
{
    Iterator high = first;
    for (Iterator p = first; p != last; ++p)
    {
        if (*high < *p)
            high = p;
    }
    return high;
}

void better_fct()
{
    int jack_count = 0; // will be updated
    double *jack_data = get_from_jack(&jack_count);
    std::vector<double> *jill_data = get_from_jill();
    std::vector<double> &v = *jill_data; // eliminates funky notation
    // Process the data more efficiently and cleanly
    double *jack_high = high(jack_data, jack_data + jack_count);
    double *jill_high = high(&v[0], &v[0] + v.size());

    std::cout << "Jack's highest: " << *jack_high << std::endl;
    std::cout << "Jill's highest: " << *jill_high << std::endl;

    // Clean up the allocated memory
    delete[] jack_data;
    delete jill_data;
}

int main()
{
    worst_fct();
    bad_fct();
    better_fct();
    return 0;
}
