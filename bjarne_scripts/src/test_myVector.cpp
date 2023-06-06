#include <gtest/gtest.h>
#include "myVector.hpp"

// Test fixture
class BabyVectorTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Common setup logic for each test case
    }

    void TearDown() override
    {
        // Common cleanup logic for each test case
    }

    // Define any helper functions specific to the test fixture
};

// Test case for the constructor with size parameter
TEST_F(BabyVectorTest, ConstructorWithSize)
{
    myNaive::babyVector v(3);

    // Perform assertions to check the state of the vector
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 3);
    EXPECT_DOUBLE_EQ(v[0], 0.0);
    EXPECT_DOUBLE_EQ(v[1], 0.0);
    EXPECT_DOUBLE_EQ(v[2], 0.0);
}

// Test case for the constructor with initializer list
TEST_F(BabyVectorTest, ConstructorWithInitializerList)
{
    myNaive::babyVector v{1.0, 2.0, 3.0};

    // Perform assertions to check the state of the vector
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 3);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

// Test case for the copy constructor
TEST_F(BabyVectorTest, CopyConstructor)
{
    myNaive::babyVector v1{1.0, 2.0, 3.0};
    myNaive::babyVector v2(v1);

    // Perform assertions to check the state of the new vector
    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2.capacity(), v1.capacity());
    for (std::size_t i = 0; i < v1.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(v2[i], v1[i]);
    }
}

// Test case for the move constructor
TEST_F(BabyVectorTest, MoveConstructor)
{
    myNaive::babyVector v1{1.0, 2.0, 3.0};
    myNaive::babyVector v2(std::move(v1));

    // Perform assertions to check the state of the new vector
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    EXPECT_DOUBLE_EQ(v2[0], 1.0);
    EXPECT_DOUBLE_EQ(v2[1], 2.0);
    EXPECT_DOUBLE_EQ(v2[2], 3.0);

    // v1 should be in a valid but unspecified state after the move
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 0);
    EXPECT_EQ(v1.data(), nullptr);
}

// Test case for copy assignment operator
TEST_F(BabyVectorTest, CopyAssignmentOperator)
{
    myNaive::babyVector v1{1.0, 2.0, 3.0};
    myNaive::babyVector v2;
    v2 = v1;

    // Perform assertions to check the state of the new vector
    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2.capacity(), v1.capacity());
    for (std::size_t i = 0; i < v1.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(v2[i], v1[i]);
    }
}

// Test case for move assignment operator
TEST_F(BabyVectorTest, MoveAssignmentOperator)
{
    myNaive::babyVector v1{1.0, 2.0, 3.0};
    myNaive::babyVector v2;
    v2 = std::move(v1);

    // Perform assertions to check the state of the new vector
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    EXPECT_DOUBLE_EQ(v2[0], 1.0);
    EXPECT_DOUBLE_EQ(v2[1], 2.0);
    EXPECT_DOUBLE_EQ(v2[2], 3.0);

    // v1 should be in a valid but unspecified state after the move
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 0);
    EXPECT_EQ(v1.data(), nullptr);
}

// Test case for accessing elements of a const vector using the const version of the subscript operator
TEST_F(BabyVectorTest, SubscriptOperatorConst)
{
    const myNaive::babyVector v{1.0, 2.0, 3.0};

    // Perform assertions to check the values returned by the subscript operator
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

// Test case for accessing elements of a non-const vector using the non-const version of the subscript operator
TEST_F(BabyVectorTest, SubscriptOperatorNonConst)
{
    myNaive::babyVector v{1.0, 2.0, 3.0};

    // Modify the elements using the subscript operator
    v[0] = 10.0;
    v[2] = 30.0;

    // Perform assertions to check the modified values
    EXPECT_DOUBLE_EQ(v[0], 10.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 30.0);
}

// Test case for resizing the vector
TEST_F(BabyVectorTest, Resize)
{
    myNaive::babyVector v{1.0, 2.0, 3.0};
    v.resize(5);

    // Perform assertions to check the new size and default-initialized elements
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 0.0);
    EXPECT_DOUBLE_EQ(v[4], 0.0);
}

// Test case for reserving capacity in the vector
TEST_F(BabyVectorTest, Reserve)
{
    myNaive::babyVector v{1.0, 2.0, 3.0};
    v.reserve(8);
    // Perform assertions to check the new capacity
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 8);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

// Test case for pushing elements to the back of the vector
TEST_F(BabyVectorTest, PushBack)
{
    myNaive::babyVector v;
    v.push_back(1.0);
    v.push_back(2.0);
    v.push_back(3.0);

    // Perform assertions to check the size, capacity, and elements
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 3);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

// Test case for the destructor
TEST_F(BabyVectorTest, Destructor)
{
    myNaive::babyVector *v = new myNaive::babyVector{1.0, 2.0, 3.0};

    // Perform assertions to check the state before destruction
    EXPECT_EQ(v->size(), 3);
    EXPECT_EQ(v->capacity(), 3);
    EXPECT_DOUBLE_EQ((*v)[0], 1.0);
    EXPECT_DOUBLE_EQ((*v)[1], 2.0);
    EXPECT_DOUBLE_EQ((*v)[2], 3.0);

    delete v;

    // After destruction, accessing the elements should not be possible
    // The following assertions are expected to fail and demonstrate that accessing deleted memory is undefined behavior
    // Uncomment them to observe the behavior

    // EXPECT_EQ(v->size(), 0);
    // EXPECT_EQ(v->capacity(), 0);
    // EXPECT_DOUBLE_EQ((*v)[0], 0.0);
    // EXPECT_DOUBLE_EQ((*v)[1], 0.0);
    // EXPECT_DOUBLE_EQ((*v)[2], 0.0);
}

// Main function to run the tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
