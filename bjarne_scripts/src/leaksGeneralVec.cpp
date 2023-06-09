#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "generalVec.cpp"

template <typename T>
void testDefaultConstructor()
{
    generalVec<T> vec;
    if (vec.capacity() == 0 && vec.getElem() == nullptr)
        std::cout << "DefaultConstructor: Passed" << std::endl;
    else
        std::cout << "DefaultConstructor: Failed" << std::endl;
}

template <typename T>
void testSizeConstructor()
{
    size_t size = 5;
    generalVec<int> vec(size);

    if (vec.size() == size)
    {
        bool allZero = true;
        for (size_t i = 0; i < size; ++i)
        {
            if (vec[i] != 0)
            {
                allZero = false;
                break;
            }
        }

        if (allZero && vec.getElem() != nullptr)
            std::cout << "SizeConstructor: Passed" << std::endl;
        else
            std::cout << "SizeConstructor: Failed" << std::endl;
    }
    else
    {
        std::cout << "SizeConstructor: Failed" << std::endl;
    }
}

template <typename T>
void testInitListConstructor()
{
    std::initializer_list<T> lst = {1, 2, 3, 4, 5};
    generalVec<T> vec(lst);

    if (vec.size() == lst.size() && vec.getElem() != nullptr)
    {
        bool elementsMatch = true;
        size_t i = 0;
        for (const auto &elem : lst)
        {
            if (vec[i] != elem)
            {
                elementsMatch = false;
                break;
            }
            ++i;
        }

        if (elementsMatch)
            std::cout << "InitListConstructor: Passed" << std::endl;
        else
            std::cout << "InitListConstructor: Failed" << std::endl;
    }
    else
    {
        std::cout << "InitListConstructor: Failed" << std::endl;
    }
}

template <typename T>
void testCopyConstructor()
{
    generalVec<T> vec1 = {1, 2, 3, 4, 5};
    generalVec<T> vec2(vec1);

    if (vec1.size() == vec2.size() && vec1.getElem() != vec2.getElem())
    {
        bool elementsMatch = true;
        for (size_t i = 0; i < vec1.size(); ++i)
        {
            if (vec1[i] != vec2[i])
            {
                elementsMatch = false;
                break;
            }
        }

        if (elementsMatch)
            std::cout << "CopyConstructor: Passed" << std::endl;
        else
            std::cout << "CopyConstructor: Failed" << std::endl;
    }
    else
    {
        std::cout << "CopyConstructor: Failed" << std::endl;
    }
}

template <typename T>
void testPushBack()
{
    generalVec<T> vec;
    if (vec.capacity() == 0 && vec.size() == 0)
    {
        vec.push_back(1);
        if (vec.capacity() == 8 && vec[0] == 1)
            std::cout << "Initial PushBack: Passed" << std::endl;
        else
            std::cout << "Initial PushBack: Failed" << std::endl;

        for (size_t i = 1; i < vec.capacity(); ++i)
        {
            vec.push_back(i);
        }

        if (vec.capacity() == 8)
        {
            vec.push_back(100);
            if (vec.capacity() == 16 && vec[8] == 100)
                std::cout << "PushBack: Passed" << std::endl;
        }
        else
            std::cout << "PushBack: Failed" << std::endl;
    }
    else
    {
        std::cout << "PushBack: Failed" << std::endl;
    }
}

template <typename T>
void testReserve()
{
    generalVec<T> vec;
    if (vec.size() == 0)
    {
        vec.reserve(10);
        if (vec.capacity() == 10)
        {
            vec.reserve(5);
            if (vec.capacity() == 10)
            {
                vec.push_back(1); // need to test alone
                if (vec.capacity() == 10 && vec.size() == 1)
                    std::cout << "Reserve: Passed" << std::endl;
            }
            else
                std::cout << "Reserve: Failed" << std::endl;
        }
        else
        {
            std::cout << "Reserve: Failed" << std::endl;
        }
    }
    else
    {
        std::cout << "Reserve: Failed" << std::endl;
    }
}

template <typename T>
void testResize()
{
    generalVec<T> vec;
    if (vec.size() == 0)
    {
        vec.resize(5);
        if (vec.size() == 5)
        {
            vec.resize(20, 7);
            if (vec.size() == 20 && vec.capacity() == 20)
            {
                bool correctValues = true;
                for (size_t i = 5; i < vec.size(); ++i)
                {
                    if (vec[i] != 7)
                    {
                        correctValues = false;
                        break;
                    }
                }

                if (correctValues)
                {
                    vec.resize(3);
                    if (vec.size() == 3 && vec.capacity() == 20) //capacity unchanged
                        std::cout << "Resize: Passed" << std::endl;
                    else
                        std::cout << "Resize: Failed" << std::endl;
                }
                else
                {
                    std::cout << "Resize: Failed" << std::endl;
                }
            }
            else
            {
                std::cout << "Resize: Failed" << std::endl;
            }
        }
        else
        {
            std::cout << "Resize: Failed" << std::endl;
        }
    }
    else
    {
        std::cout << "Resize: Failed" << std::endl;
    }
}

template <typename T>
void testAt()
{
    generalVec<T> vec = {1, 2, 3, 4, 5};

    bool elementsMatch = true;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] != vec.at(i))
        {
            elementsMatch = false;
            break;
        }
    }

    bool throwsException = false;
    try
    {
        vec.at(10);
    }
    catch (const std::out_of_range &)
    {
        throwsException = true;
    }

    if (elementsMatch && throwsException)
        std::cout << "At: Passed" << std::endl;
    else
        std::cout << "At: Failed" << std::endl;
}

template <typename T>
void testSubscriptOperator()
{
    generalVec<T> vec = {1, 2, 3, 4, 5};

    bool elementsMatch = true;

    if (vec[0] != 1 || vec[4] != 5)
    {
        elementsMatch = false;
    }

    if (elementsMatch)
        std::cout << "SubscriptOperator: Passed" << std::endl;
    else
        std::cout << "SubscriptOperator: Failed" << std::endl;
}

int main()
{
    // Enable memory leak detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    testDefaultConstructor<int>();
    testSizeConstructor<int>();
    testInitListConstructor<int>();
    testCopyConstructor<int>();
    testPushBack<int>();
    testReserve<int>();
    testResize<int>();
    testAt<int>();
    testSubscriptOperator<int>();

    testDefaultConstructor<float>();
    testSizeConstructor<float>();
    testInitListConstructor<float>();
    testCopyConstructor<float>();
    testPushBack<float>();
    testReserve<float>();
    testResize<float>();
    testAt<float>();
    testSubscriptOperator<float>();

    // Check for memory leaks and print the leak report if found
    _CrtDumpMemoryLeaks();

    return 0;
}
