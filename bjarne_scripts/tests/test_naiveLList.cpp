#include <gtest/gtest.h>
#include "../src/naiveLList.hpp"

// Test fixture for the Link class
class LinkTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Initialize test data
        link1 = new Link("Link 1");
        link2 = new Link("Link 2");
        link3 = new Link("Link 3");

        // Set up the linked list
        link1->add(link2);
        link2->add(link3);
    }

    void TearDown() override
    {
        // Clean up
        delete link1;
        delete link2;
        delete link3;
    }

    // Test objects
    Link *link1;
    Link *link2;
    Link *link3;
};

// Test case for insert and add methods
TEST_F(LinkTest, InsertAndAdd)
{
    Link *link4 = new Link("Link 4");
    Link *link5 = new Link("Link 5");

    // Insert link4 before link2
    link2->insert(link4);
    EXPECT_EQ(link4->getPrevious(), link1);
    EXPECT_EQ(link4->getNext(), link2);

    // Add link5 after link3
    link3->add(link5);
    EXPECT_EQ(link5->getPrevious(), link3);
    EXPECT_EQ(link5->getNext(), nullptr);

    // Verify the updated linked list
    EXPECT_EQ(link1->getNext(), link4);
    EXPECT_EQ(link4->getNext(), link2);
    EXPECT_EQ(link2->getNext(), link3);
    EXPECT_EQ(link3->getNext(), link5);

    delete link4;
    delete link5;
}

// Test case for erase method
TEST_F(LinkTest, Erase)
{
    // Erase link2 from the list
    Link* link2Next = link2->erase();
    EXPECT_EQ(link1->getNext(), link3);
    EXPECT_EQ(link3->getPrevious(), link1);
    EXPECT_EQ(link2Next, link3);
}

// Test case for find method
TEST_F(LinkTest, Find)
{
    // Find "Link 2" in the list
    const Link *foundLink = link1->find("Link 2");
    EXPECT_EQ(foundLink, link2);

    // Find "Link 4" which is not in the list
    foundLink = link1->find("Link 4");
    EXPECT_EQ(foundLink, nullptr);
}

// Test case for advance method
TEST_F(LinkTest, Advance)
{
    // Advance 2 positions from link1
    Link *advancedLink = link1->advance(2);
    EXPECT_EQ(advancedLink, link3);

    // Advance -1 position from link3
    advancedLink = link3->advance(-1);
    EXPECT_EQ(advancedLink, link2);
}

// Test case for const find method
TEST_F(LinkTest, ConstFind)
{
    const Link *constLink1 = link1;
    const Link *constLink2 = link2;
    const Link *constLink3 = link3;

    // Find "Link 1" in the const list
    const Link *foundLink = constLink1->find("Link 1");
    EXPECT_EQ(foundLink, constLink1);

    // Find "Link 3" in the const list
    foundLink = constLink1->find("Link 3");
    EXPECT_EQ(foundLink, constLink3);

    // Find "Link 2" in the const list
    foundLink = constLink1->find("Link 2");
    EXPECT_EQ(foundLink, constLink2);

    // Find "Link 4" which is not in the const list
    foundLink = constLink1->find("Link 4");
    EXPECT_EQ(foundLink, nullptr);
}
