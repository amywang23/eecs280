#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_empty) {
    List<int> l;
    ASSERT_EQUAL(l.empty(), true);
}

TEST(test_size) {
    List<int> l;
    l.push_back(4);
    ASSERT_EQUAL(l.size(), 1);
}

TEST(test_pushback) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 2);
}

TEST(test_pushfront) {
    List<int> l;
    l.push_front(1);
    l.push_front(2);
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 1);
}

TEST(test_popfront) {
    List<int> l;
    l.push_front(1);
    l.push_front(2);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 1);
}

TEST(test_popback) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.pop_back();
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 1);
}

TEST(simple_manipulation) {
    List<int> a;
    List<int> b(a);
    
    ASSERT_TRUE(a.size() == b.size());
    a.push_back(7);
    a.push_front(6);
    a.push_back(5);
    ASSERT_EQUAL(a.back(), 5);
    ASSERT_EQUAL(a.front(), 6);
    b = a;
    ASSERT_EQUAL(b.front(), 6);
    ASSERT_EQUAL(b.back(), 5);
    ASSERT_EQUAL(a.size(), b.size());

    a.insert(++++a.begin(), 4);
    ASSERT_EQUAL(a.size(), 4);
    a.pop_back();
    ASSERT_EQUAL(a.back(), 4);

    a.clear();
    ASSERT_EQUAL(a.size(), 0);
    b.erase(++b.begin());
    ASSERT_EQUAL(b.back(), 5);
    ASSERT_EQUAL(b.front(), 6);
    b.pop_front();
    ASSERT_EQUAL(b.front(), b.back());
    b.pop_back();
    ASSERT_EQUAL(b.size(), 0);

}

TEST(test_erase3) {
     List<int> l;
     l.push_back(1);
     l.push_back(2);
     l.insert(l.begin(), 3);
     l.erase(++++l.begin());
     ASSERT_EQUAL(l.size(), 2);
     ASSERT_EQUAL(l.front(), 3);
     ASSERT_EQUAL(l.back(), 1);
 }

TEST(test_erase4) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(l.begin(), 3);
    l.erase(++(++l.begin()));
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 3);
    ASSERT_EQUAL(l.back(), 1);
}

TEST(test_clearing) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(l.begin(), 3);
    l.clear();
    ASSERT_EQUAL(l.size(), 0);
}

TEST(test_insert) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(l.begin(), 3);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 3);
}

TEST(test_insert2) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(++l.begin(), 3);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 1);
}

TEST(test_insert3) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(l.end(), 3);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.back(), 3);
}

TEST(test_opequal) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(l.begin(), 3);
    List<int> l2;
    l2.operator=(l);
    ASSERT_EQUAL(l.size(), l2.size());
    ASSERT_EQUAL(l.front(), l2.front());
    ASSERT_EQUAL(l.back(), l2.back());
}

TEST(test_erase) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(l.begin(), 3);
    l.erase(++l.begin());
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 3);
    ASSERT_EQUAL(l.back(), 2);
}

TEST(test_erase2) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.insert(l.begin(), 3);
    l.erase(l.begin());
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 2);
}

TEST(insertEnd) {
    List<string> t;
    t.push_back("hello");
    t.insert(t.end(), "china");
    ASSERT_EQUAL(t.back(), "china");

    ASSERT_EQUAL(*++t.begin(), "china");
    ASSERT_EQUAL(*t.begin(), "hello");
    
}

TEST(booleanEval) {
    List<double> lol;
    lol.push_back(100);

    lol.push_back(200);
    lol.push_back(400);

    List<double> lol2(lol);

    ASSERT_EQUAL(*lol.begin(), *lol2.begin());
    ASSERT_TRUE(*++++lol.begin() == *++++lol2.begin());

    ASSERT_TRUE(*++++lol.begin() != *++lol2.begin());
}

TEST_MAIN()