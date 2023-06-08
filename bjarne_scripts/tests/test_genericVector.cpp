#include <gtest/gtest.h>
#include "genericVector.cpp"

namespace myNaive
{
    // Test fixture for generalVector tests
    class GeneralVectorTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Optional: Any setup you need to perform before each test
        }

        void TearDown() override
        {
            // Optional: Any teardown you need to perform after each test
        }
    };

    TEST_F(GeneralVectorTest, DefaultConstructor_Int)
    {
        generalVector<int> vec;
        EXPECT_EQ(vec.size(), 0);
        EXPECT_EQ(vec.capacity(), 0);
    }

    TEST_F(GeneralVectorTest, SizeConstructor_Int)
    {
        generalVector<int> vec(5);
        EXPECT_EQ(vec.size(), 5);
        EXPECT_EQ(vec.capacity(), 5);
    }

    TEST_F(GeneralVectorTest, InitListConstructor_Int)
    {
        generalVector<int> vec = {1, 2, 3};
        EXPECT_EQ(vec.size(), 3);
        EXPECT_EQ(vec.capacity(), 3);
        EXPECT_EQ(vec[0], 1);
        EXPECT_EQ(vec[1], 2);
        EXPECT_EQ(vec[2], 3);
    }

    TEST_F(GeneralVectorTest, CopyConstructor_Int)
    {
        generalVector<int> vec1 = {1, 2, 3};
        generalVector<int> vec2(vec1);
        EXPECT_EQ(vec1.size(), vec2.size());
        EXPECT_EQ(vec1.capacity(), vec2.capacity());
        for (int i = 0; i < vec1.size(); i++)
        {
            EXPECT_EQ(vec1[i], vec2[i]);
        }
    }

    TEST_F(GeneralVectorTest, MoveConstructor_Int)
    {
        generalVector<int> vec1 = {1, 2, 3};
        generalVector<int> vec2(std::move(vec1));
        EXPECT_EQ(vec2.size(), 3);
        EXPECT_EQ(vec2.capacity(), 3);
        EXPECT_EQ(vec2[0], 1);
        EXPECT_EQ(vec2[1], 2);
        EXPECT_EQ(vec2[2], 3);
        EXPECT_EQ(vec1.size(), 0);
        EXPECT_EQ(vec1.capacity(), 0);
        EXPECT_EQ(vec1.checkElem(), nullptr);
    }

    TEST_F(GeneralVectorTest, CopyAssignment_Int)
    {
        generalVector<int> vec1 = {1, 2, 3};
        generalVector<int> vec2;
        vec2 = vec1;
        EXPECT_EQ(vec1.size(), vec2.size());
        EXPECT_EQ(vec1.capacity(), vec2.capacity());
        for (int i = 0; i < vec1.size(); i++)
        {
            EXPECT_EQ(vec1[i], vec2[i]);
        }
    }

    TEST_F(GeneralVectorTest, MoveAssignment_Int)
    {
        generalVector<int> vec1 = {1, 2, 3};
        generalVector<int> vec2;
        vec2 = std::move(vec1);
        EXPECT_EQ(vec2.size(), 3);
        EXPECT_EQ(vec2.capacity(), 3);
        EXPECT_EQ(vec2[0], 1);
        EXPECT_EQ(vec2[1], 2);
        EXPECT_EQ(vec2[2], 3);
        EXPECT_EQ(vec1.size(), 0);
        EXPECT_EQ(vec1.capacity(), 0);
        EXPECT_EQ(vec1.checkElem(), nullptr);
    }

    TEST_F(GeneralVectorTest, Resize_Int)
    {
        generalVector<int> vec = {1, 2, 3};
        vec.resize(5);
        EXPECT_EQ(vec.size(), 5);
        EXPECT_EQ(vec.capacity(), 5);
        EXPECT_EQ(vec[3], 0);
        EXPECT_EQ(vec[4], 0);
    }

    TEST_F(GeneralVectorTest, Reserve_Int)
    {
        generalVector<int> vec = {1, 2, 3};
        vec.reserve(10);
        EXPECT_EQ(vec.size(), 3);
        EXPECT_EQ(vec.capacity(), 10);
    }

    TEST_F(GeneralVectorTest, PushBack_Int)
    {
        generalVector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        EXPECT_EQ(vec.size(), 3);
        EXPECT_EQ(vec.capacity(), 4);
        EXPECT_EQ(vec[0], 1);
        EXPECT_EQ(vec[1], 2);
        EXPECT_EQ(vec[2], 3);
    }

    TEST_F(GeneralVectorTest, DefaultConstructor_Double)
    {
        generalVector<double> vec;
        EXPECT_EQ(vec.size(), 0);
        EXPECT_EQ(vec.capacity(), 0);
    }

    TEST_F(GeneralVectorTest, SizeConstructor_Double)
    {
        generalVector<double> vec(5);
        EXPECT_EQ(vec.size(), 5);
        EXPECT_EQ(vec.capacity(), 5);
    }

    TEST_F(GeneralVectorTest, InitListConstructor_Double)
    {
        generalVector<double> vec = {1.1, 2.2, 3.3};
        EXPECT_EQ(vec.size(), 3);
        EXPECT_EQ(vec.capacity(), 3);
        EXPECT_DOUBLE_EQ(vec[0], 1.1);
        EXPECT_DOUBLE_EQ(vec[1], 2.2);
        EXPECT_DOUBLE_EQ(vec[2], 3.3);
    }

    TEST_F(GeneralVectorTest, CopyConstructor_Double)
    {
        generalVector<double> vec1 = {1.1, 2.2, 3.3};
        generalVector<double> vec2(vec1);
        EXPECT_EQ(vec1.size(), vec2.size());
        EXPECT_EQ(vec1.capacity(), vec2.capacity());
        for (int i = 0; i < vec1.size(); i++)
        {
            EXPECT_DOUBLE_EQ(vec1[i], vec2[i]);
        }
    }

    TEST_F(GeneralVectorTest, MoveConstructor_Double)
    {
        generalVector<double> vec1 = {1.1, 2.2, 3.3};
        generalVector<double> vec2(std::move(vec1));
        EXPECT_EQ(vec2.size(), 3);
        EXPECT_EQ(vec2.capacity(), 3);
        EXPECT_DOUBLE_EQ(vec2[0], 1.1);
        EXPECT_DOUBLE_EQ(vec2[1], 2.2);
        EXPECT_DOUBLE_EQ(vec2[2], 3.3);
        EXPECT_EQ(vec1.size(), 0);
        EXPECT_EQ(vec1.capacity(), 0);
        EXPECT_EQ(vec1.checkElem(), nullptr);
    }

    TEST_F(GeneralVectorTest, CopyAssignment_Double)
    {
        generalVector<double> vec1 = {1.1, 2.2, 3.3};
        generalVector<double> vec2;
        vec2 = vec1;
        EXPECT_EQ(vec1.size(), vec2.size());
        EXPECT_EQ(vec1.capacity(), vec2.capacity());
        for (int i = 0; i < vec1.size(); i++)
        {
            EXPECT_DOUBLE_EQ(vec1[i], vec2[i]);
        }
    }

    TEST_F(GeneralVectorTest, MoveAssignment_Double)
    {
        generalVector<double> vec1 = {1.1, 2.2, 3.3};
        generalVector<double> vec2;
        vec2 = std::move(vec1);
        EXPECT_EQ(vec2.size(), 3);
        EXPECT_EQ(vec2.capacity(), 3);
        EXPECT_DOUBLE_EQ(vec2[0], 1.1);
        EXPECT_DOUBLE_EQ(vec2[1], 2.2);
        EXPECT_DOUBLE_EQ(vec2[2], 3.3);
        EXPECT_EQ(vec1.size(), 0);
        EXPECT_EQ(vec1.capacity(), 0);
        EXPECT_EQ(vec1.checkElem(), nullptr);
    }

    TEST_F(GeneralVectorTest, EmptyVectorAccess_Int)
    {
        generalVector<int> vec;
        EXPECT_THROW(vec[0], std::out_of_range);
    }

    TEST_F(GeneralVectorTest, EmptyVectorAccess_Double)
    {
        generalVector<double> vec;
        EXPECT_THROW(vec[0], std::out_of_range);
    }

    TEST_F(GeneralVectorTest, ResizeSmaller_Int)
    {
        generalVector<int> vec = {1, 2, 3};
        vec.resize(2);
        EXPECT_EQ(vec.size(), 2);
        EXPECT_EQ(vec.capacity(), 3);
        EXPECT_EQ(vec[0], 1);
        EXPECT_EQ(vec[1], 2);
        EXPECT_THROW(vec[2], std::out_of_range);
    }

    TEST_F(GeneralVectorTest, ResizeLargerWithDefaultValue_Double)
    {
        generalVector<double> vec = {1.1, 2.2, 3.3};
        vec.resize(5);
        EXPECT_EQ(vec.size(), 5);
        EXPECT_EQ(vec.capacity(), 5);
        EXPECT_DOUBLE_EQ(vec[3], 0.0);
        EXPECT_DOUBLE_EQ(vec[4], 0.0);
    }

    TEST_F(GeneralVectorTest, ResizeZero_Double)
    {
        generalVector<double> vec = {1.1, 2.2, 3.3};
        vec.resize(0);
        EXPECT_EQ(vec.size(), 0);
        EXPECT_EQ(vec.capacity(), 3);
        EXPECT_THROW(vec[0], std::out_of_range);
    }

    TEST_F(GeneralVectorTest, ReserveZero_Int)
    {
        generalVector<int> vec = {1, 2, 3};
        vec.reserve(0);
        EXPECT_EQ(vec.size(), 3);
        EXPECT_EQ(vec.capacity(), 3);
    }

    TEST_F(GeneralVectorTest, PushBackBeyondInitialCapacity_Double)
    {
        generalVector<double> vec;
        for (int i = 0; i < 10; i++)
        {
            vec.push_back(i + 1);
        }
        EXPECT_EQ(vec.size(), 10);
        EXPECT_EQ(vec.capacity(), 16);
        for (int i = 0; i < 10; i++)
        {
            EXPECT_DOUBLE_EQ(vec[i], i + 1);
        }
    }

    TEST_F(GeneralVectorTest, CopyConstructorEmptyVector_Double)
    {
        generalVector<double> vec1;
        generalVector<double> vec2(vec1);
        EXPECT_EQ(vec1.size(), 0);
        EXPECT_EQ(vec1.capacity(), 0);
        EXPECT_EQ(vec2.size(), 0);
        EXPECT_EQ(vec2.capacity(), 0);
        EXPECT_EQ(vec1.checkElem(), nullptr);
        EXPECT_EQ(vec2.checkElem(), nullptr);
    }

    TEST_F(GeneralVectorTest, MoveConstructorEmptyVector_Int)
    {
        generalVector<int> vec1;
        generalVector<int> vec2(std::move(vec1));
        EXPECT_EQ(vec1.size(), 0);
        EXPECT_EQ(vec1.capacity(), 0);
        EXPECT_EQ(vec1.checkElem(), nullptr);
        EXPECT_EQ(vec2.size(), 0);
        EXPECT_EQ(vec2.capacity(), 0);
        EXPECT_EQ(vec2.checkElem(), nullptr);
    }

    TEST_F(GeneralVectorTest, MoveAssignmentEmptyVector_Double)
    {
        generalVector<double> vec1;
        generalVector<double> vec2;
        vec2 = std::move(vec1);
        EXPECT_EQ(vec1.size(), 0);
        EXPECT_EQ(vec1.capacity(), 0);
        EXPECT_EQ(vec1.checkElem(), nullptr);
        EXPECT_EQ(vec2.size(), 0);
        EXPECT_EQ(vec2.capacity(), 0);
        EXPECT_EQ(vec2.checkElem(), nullptr);
    }
}

