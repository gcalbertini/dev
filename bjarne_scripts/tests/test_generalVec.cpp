#include <gtest/gtest.h>
#include "../src/generalVec.cpp"

// Test fixture for generalVec class
template <typename T>
class GeneralVecTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test case for default constructor
TYPED_TEST_SUITE_P(GeneralVecTest);
TYPED_TEST_P(GeneralVecTest, DefaultConstructor)
{
    generalVec<TypeParam> vec;
    EXPECT_EQ(0, vec.capacity());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(nullptr, vec.getElem());
}

// Test case for size_t constructor
TYPED_TEST_P(GeneralVecTest, SizeConstructor)
{
    size_t size = 5;
    generalVec<int> vec(size);

    EXPECT_EQ(size, vec.size());

    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(0, vec[i]);
    }
    EXPECT_NE(nullptr, vec.getElem());
}

// Test case for initializer list constructor
TYPED_TEST_P(GeneralVecTest, InitListConstructor)
{
    std::initializer_list<TypeParam> lst = {1, 2, 3, 4, 5};
    generalVec<TypeParam> vec(lst);
    EXPECT_EQ(lst.size(), vec.size());
    EXPECT_EQ(8, vec.capacity());
    EXPECT_NE(nullptr, vec.getElem());

    // Verify the elements
    size_t i = 0;
    for (const auto &elem : lst)
    {
        EXPECT_EQ(elem, vec[i]);
        ++i;
    }
}

// Test case for copy constructor
TYPED_TEST_P(GeneralVecTest, CopyConstructor)
{
    generalVec<TypeParam> vec1 = {1, 2, 3, 4, 5};
    generalVec<TypeParam> vec2(vec1);
    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_EQ(vec1.capacity(), vec2.capacity());
    EXPECT_NE(vec1.getElem(), vec2.getElem());

    // Verify the elements
    for (size_t i = 0; i < vec1.size(); ++i)
    {
        EXPECT_EQ(vec1[i], vec2[i]);
    }
}

// Test case for push_back method
TYPED_TEST_P(GeneralVecTest, PushBack)
{
    generalVec<TypeParam> vec;
    EXPECT_EQ(0, vec.size());

    vec.push_back(1);
    EXPECT_EQ(8, vec.size());
    EXPECT_EQ(1, vec[0]);

    // Verify the elements
    for (size_t i = 1; i < vec1.capacity(); ++i)
    {
        vec.push_back(i);
    }
    EXPECT_EQ(8, vec.capacity());

    vec.push_back(100);
    EXPECT_EQ(100, vec[8]);
    EXPECT_EQ(16, vec.capacity());
}

// Test case for reserve method
TYPED_TEST_P(GeneralVecTest, Reserve)
{
    generalVec<TypeParam> vec;
    EXPECT_EQ(0, vec.capacity());

    vec.reserve(2);
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(2, vec.capacity());

    vec.reserve(1); // Should not change the capacity
    EXPECT_EQ(2, vec.capacity());

    vec.push_back(1); //test this alone
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(4, vec.capacity());
    EXPECT_EQ(3, vec.size());
}

// Test case for resize method
TYPED_TEST_P(GeneralVecTest, Resize)
{
    generalVec<TypeParam> vec;
    EXPECT_EQ(0, vec.capacity());
    EXPECT_EQ(0, vec.size());

    vec.resize(5);
    EXPECT_EQ(5, vec.size());
     EXPECT_EQ(8, vec.capacity());

    vec.resize(20, 7);
    EXPECT_EQ(20, vec.size());
    EXPECT_EQ(20, vec.capacity());
    for (size_t i = 5; i < vec.capacity(); ++i)
    {
        EXPECT_EQ(7, vec[i]);
    }

    vec.resize(3);
    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(16, vec.capacity());
}

// Test case for at method
TYPED_TEST_P(GeneralVecTest, At)
{
    generalVec<TypeParam> vec = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < vec.capacity(); ++i)
    {
        EXPECT_EQ(vec[i], vec.at(i));
    }

    EXPECT_THROW(vec.at(10), std::out_of_range);
}

// Test case for [] operator
TYPED_TEST_P(GeneralVecTest, SubscriptOperator)
{
    generalVec<TypeParam> vec = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < vec.capacity(); ++i)
    {
        EXPECT_EQ(vec[i], vec[i]);
    }
}

// Register the additional test cases
REGISTER_TYPED_TEST_SUITE_P(GeneralVecTest, DefaultConstructor, SizeConstructor, InitListConstructor, CopyConstructor, PushBack, Reserve, Resize, At, SubscriptOperator);

// Define the types to be tested
typedef ::testing::Types<int, float> MyTypes;

INSTANTIATE_TYPED_TEST_SUITE_P(My, GeneralVecTest, MyTypes);

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
