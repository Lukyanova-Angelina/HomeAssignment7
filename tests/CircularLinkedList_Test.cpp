/* Lukyanova Angelina st128743@student.spbu.ru
 * Home assignment 7 - Circular list
 */
#include "CircularLinkedList.h"
#include "gtest/gtest.h"
#include <vector>
#include <algorithm>

/// Test default constructor and basic properties of empty list
TEST(CircularLinkedList, DefaultConstructor) {
    CircularLinkedList<int> l;
    EXPECT_EQ(l.size(), 0);
    EXPECT_TRUE(l.empty());
    EXPECT_THROW(l.front(), std::out_of_range);
    EXPECT_THROW(l.back(), std::out_of_range);
}

/// Test copy constructor functionality
TEST(CircularLinkedList, CopyConstructor) {
    CircularLinkedList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);

    CircularLinkedList<int> l2(l1);
    EXPECT_EQ(l2.size(), 3);
    EXPECT_EQ(l2.front(), 1);
    EXPECT_EQ(l2.back(), 3);
    EXPECT_TRUE(l1 == l2);
    
    l1.pop_front();
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l2.size(), 3);
}

/// Test move constructor functionality
TEST(CircularLinkedList, MoveConstructor) {
    CircularLinkedList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    
    CircularLinkedList<int> l2(std::move(l1));
    EXPECT_EQ(l2.size(), 2);
    EXPECT_EQ(l2.front(), 1);
    EXPECT_EQ(l2.back(), 2);
    EXPECT_TRUE(l1.empty());
    EXPECT_EQ(l1.size(), 0);
}

/// Test copy assignment operator
TEST(CircularLinkedList, CopyAssignment) {
    CircularLinkedList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    
    CircularLinkedList<int> l2;
    l2 = l1;
    EXPECT_EQ(l2.size(), 2);
    EXPECT_EQ(l2.front(), 1);
    EXPECT_EQ(l2.back(), 2);
    EXPECT_TRUE(l1 == l2);
    
    l2 = l2;
    EXPECT_EQ(l2.size(), 2);
    EXPECT_EQ(l2.front(), 1);
    EXPECT_EQ(l2.back(), 2);
}

/// Test move assignment operator
TEST(CircularLinkedList, MoveAssignment) {
    CircularLinkedList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    
    CircularLinkedList<int> l2;
    l2 = std::move(l1);
    EXPECT_EQ(l2.size(), 2);
    EXPECT_EQ(l2.front(), 1);
    EXPECT_EQ(l2.back(), 2);
    EXPECT_TRUE(l1.empty());
    EXPECT_EQ(l1.size(), 0);
}

/// Test push_back method functionality
TEST(CircularLinkedList, PushBack) {
    CircularLinkedList<int> l;
    l.push_back(1);
    EXPECT_EQ(l.size(), 1);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 1);
    
    l.push_back(2);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 2);
    
    l.push_back(3);
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 3);
}

/// Test push_front method functionality
TEST(CircularLinkedList, PushFront) {
    CircularLinkedList<int> l;
    l.push_front(1);
    EXPECT_EQ(l.size(), 1);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 1);
    
    l.push_front(2);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.front(), 2);
    EXPECT_EQ(l.back(), 1);
    
    l.push_front(3);
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.front(), 3);
    EXPECT_EQ(l.back(), 1);
}

/// Test pop_back method functionality
TEST(CircularLinkedList, PopBack) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 3);
    
    l.pop_back();
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 2);
    
    l.pop_back();
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 1);
    
    l.pop_back();
    EXPECT_EQ(l.size(), 0);
    EXPECT_TRUE(l.empty());
    EXPECT_THROW(l.front(), std::out_of_range);
    EXPECT_THROW(l.back(), std::out_of_range);
    
    EXPECT_THROW(l.pop_back(), std::out_of_range);
}

/// Test pop_front method functionality
TEST(CircularLinkedList, PopFront) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 3);
    
    l.pop_front();
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.front(), 2);
    EXPECT_EQ(l.back(), 3);
    
    l.pop_front();
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.front(), 3);
    EXPECT_EQ(l.back(), 3);
    
    l.pop_front();
    EXPECT_EQ(l.size(), 0);
    EXPECT_TRUE(l.empty());
    EXPECT_THROW(l.front(), std::out_of_range);
    EXPECT_THROW(l.back(), std::out_of_range);
    
    EXPECT_THROW(l.pop_front(), std::out_of_range);
}

/// Test clear method functionality
TEST(CircularLinkedList, Clear) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 3);
    
    l.clear();
    EXPECT_EQ(l.size(), 0);
    EXPECT_TRUE(l.empty());
    EXPECT_THROW(l.front(), std::out_of_range);
    EXPECT_THROW(l.back(), std::out_of_range);
    
    l.clear();
    EXPECT_EQ(l.size(), 0);
    EXPECT_TRUE(l.empty());
}

/// Test swap method functionality
TEST(CircularLinkedList, Swap) {
    CircularLinkedList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    
    CircularLinkedList<int> l2;
    l2.push_back(4);
    l2.push_back(5);
    l2.push_back(6);
    
    l1.swap(l2);
    
    EXPECT_EQ(l1.size(), 3);
    EXPECT_EQ(l1.front(), 4);
    EXPECT_EQ(l1.back(), 6);
    
    EXPECT_EQ(l2.size(), 3);
    EXPECT_EQ(l2.front(), 1);
    EXPECT_EQ(l2.back(), 3);
    
    CircularLinkedList<int> l3;
    l1.swap(l3);
    EXPECT_EQ(l1.size(), 0);
    EXPECT_TRUE(l1.empty());
    EXPECT_EQ(l3.size(), 3);
    EXPECT_EQ(l3.front(), 4);
    EXPECT_EQ(l3.back(), 6);
    
    CircularLinkedList<int> l4, l5;
    l4.swap(l5);
    EXPECT_TRUE(l4.empty());
    EXPECT_TRUE(l5.empty());
}

/// Test assign method functionality
TEST(CircularLinkedList, Assign) {
    CircularLinkedList<int> l;
    l.assign(3, 1);
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 1);
    
    l.assign(2, 2);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.front(), 2);
    EXPECT_EQ(l.back(), 2);
    
    l.assign(0, 5);
    EXPECT_EQ(l.size(), 0);
    EXPECT_TRUE(l.empty());
}

/// Test insert method functionality
TEST(CircularLinkedList, Insert) {
    CircularLinkedList<int> l;
    
    auto it = l.insert(l.end(), 1);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(*it, 1);
    
    it = l.insert(l.begin(), 0);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(l.front(), 0);
    
    auto mid = l.begin();
    ++mid;
    it = l.insert(mid, 5);
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(*it, 5);
    
    std::vector<int> result;
    auto current = l.begin();
    for (size_t i = 0; i < l.size(); ++i) {
        result.push_back(*current);
        ++current;
    }
    EXPECT_EQ(result, std::vector<int>({0, 5, 1}));
}

/// Test erase method functionality
TEST(CircularLinkedList, Erase) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    EXPECT_EQ(l.size(), 3);
    
    auto it = l.begin();
    ++it;
    it = l.erase(it);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(*it, 3);
    
    it = l.erase(l.begin());
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(l.front(), 3);
    EXPECT_EQ(l.back(), 3);
    
    it = l.erase(l.begin());
    EXPECT_EQ(l.size(), 0);
    EXPECT_TRUE(l.empty());
    
    EXPECT_THROW(l.erase(l.begin()), std::out_of_range);
    
    l.push_back(1);
    EXPECT_THROW(l.erase(l.end()), std::invalid_argument);
}

/// Test basic iterator functionality
TEST(CircularLinkedList, IteratorBasic) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    auto iter = l.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_TRUE(iter == l.end());
}

/// Test range-based for loop compatibility
TEST(CircularLinkedList, IteratorRangeBasedFor) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    std::vector<int> result;
    for (int value : l) {
        result.push_back(value);
    }
    
    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

/// Test iterator decrement operations
TEST(CircularLinkedList, IteratorDecrement) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    auto it = l.end();
    --it;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 2);
    --it;
    EXPECT_EQ(*it, 1);
    
    it = l.begin();
    --it;
    EXPECT_EQ(*it, 3);
}

/// Test iterator post-increment operations
TEST(CircularLinkedList, IteratorPostIncrement) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    auto it = l.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(it, l.end());
}

/// Test iterator post-decrement operations
TEST(CircularLinkedList, IteratorPostDecrement) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    auto it = l.end();
    it--;
    EXPECT_EQ(*it--, 3);
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(*it--, 2);
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it, l.begin());
}

/// Test comparison operators
TEST(CircularLinkedList, ComparisonOperators) {
    CircularLinkedList<int> a, b, c, d;
    a.push_back(1);
    a.push_back(2);
    b.push_back(1);
    b.push_back(2);
    c.push_back(2);
    c.push_back(3);
    d.push_back(1);
    
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(d < a);
    EXPECT_TRUE(a > d);
    
    CircularLinkedList<int> e, f;
    EXPECT_TRUE(e == f);
    EXPECT_FALSE(e != f);
    EXPECT_FALSE(e < f);
    EXPECT_FALSE(e > f);
    EXPECT_TRUE(e <= f);
    EXPECT_TRUE(e >= f);
}

/// Test const_iterator functionality
TEST(CircularLinkedList, ConstIterator) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    const CircularLinkedList<int>& cl = l;
    auto it = cl.cbegin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, cl.cend());
    
    static_assert(std::is_same<decltype(*it), const int&>::value, 
                  "const_iterator should return const reference");
}

/// Test reverse iterator functionality
TEST(CircularLinkedList, ReverseIterator) {
    CircularLinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    std::vector<int> result;
    for (auto rit = l.rbegin(); rit != l.rend(); ++rit) {
        result.push_back(*rit);
    }
    
    EXPECT_EQ(result, std::vector<int>({3, 2, 1}));
    
    CircularLinkedList<int> empty;
    EXPECT_TRUE(empty.rbegin() == empty.rend());
}

/// Test iterator behavior on empty list
TEST(CircularLinkedList, IteratorsOnEmpty) {
    CircularLinkedList<int> l;
    EXPECT_TRUE(l.begin() == l.end());
    EXPECT_TRUE(l.cbegin() == l.cend());
    EXPECT_TRUE(l.rbegin() == l.rend());
    EXPECT_TRUE(l.crbegin() == l.crend());
    
    auto it1 = l.begin();
    auto it2 = l.end();
    EXPECT_EQ(it1, it2);
}