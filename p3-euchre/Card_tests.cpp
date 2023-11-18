#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_cor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_card_operators) {
    Card c = Card(THREE, SPADES);
    ASSERT_FALSE(c < c);
    ASSERT_TRUE(c <= c);
    ASSERT_FALSE(c > c);
    ASSERT_TRUE(c >= c);
    ASSERT_TRUE(c == c);
    ASSERT_FALSE(c != c);
}

TEST(test_card_operators2) {
    Card c = Card(THREE, SPADES);
    Card d = Card(TWO, DIAMONDS);
    ASSERT_FALSE(c < d);
    ASSERT_FALSE(c <= d);
    ASSERT_TRUE(c > d);
    ASSERT_TRUE(c >= d);
    ASSERT_FALSE(c == d);
    ASSERT_TRUE(c != d);
}

TEST(test_card_operators3) {
    Card c = Card(THREE, SPADES);
    Card d = Card(THREE, DIAMONDS);
    ASSERT_TRUE(c < d);
    ASSERT_TRUE(c <= d);
    ASSERT_FALSE(c > d);
    ASSERT_FALSE(c >= d);
    ASSERT_FALSE(c == d);
    ASSERT_TRUE(c != d);
}

TEST(test_card_operators4) {
    Card c = Card(TWO, SPADES);
    Card d = Card(THREE, SPADES);
    ASSERT_TRUE(c < d);
    ASSERT_TRUE(c <= d);
    ASSERT_FALSE(c > d);
    ASSERT_FALSE(c >= d);
    ASSERT_FALSE(c == d);
    ASSERT_TRUE(c != d);
}

TEST(test_cardless){
    Card a(JACK, CLUBS);
    Card b(JACK, SPADES);
    ASSERT_EQUAL(Card_less(a, b, SPADES), true);
}

TEST(test_cardless2){
    Card a(JACK, CLUBS);
    Card b(JACK, SPADES);
    ASSERT_EQUAL(Card_less(a, b, CLUBS), false);
}

TEST(test_cardless3){
    Card a(JACK, CLUBS);
    Card b(QUEEN, SPADES);
    ASSERT_EQUAL(Card_less(a, b, SPADES), false);
}

TEST(test_cardless7){
    Card a(QUEEN, CLUBS);
    Card b(QUEEN, SPADES);
    ASSERT_EQUAL(Card_less(a, b, SPADES), true);
}

TEST(test_cardless4){
    Card a(TEN, SPADES);
    Card b(QUEEN, SPADES);
    ASSERT_EQUAL(Card_less(a, b, SPADES), true);
}

TEST(test_cardless5){
    Card a(QUEEN, CLUBS);
    Card b(QUEEN, SPADES);
    ASSERT_EQUAL(Card_less(a, b, CLUBS), false);
}

TEST(test_cardless6){
    Card a(JACK, DIAMONDS);
    Card b(QUEEN, SPADES);
    ASSERT_EQUAL(Card_less(a, b, CLUBS), true);
}

TEST(test_cardless8){
    Card led(TEN, HEARTS);
    Card a(JACK, HEARTS);
    Card b(QUEEN, SPADES);
    ASSERT_EQUAL(Card_less(a, b, led, CLUBS), false);
}

TEST(test_cardless9){
    Card led(TEN, HEARTS);
    Card a(KING, SPADES);
    Card b(QUEEN, HEARTS);
    ASSERT_EQUAL(Card_less(a, b, led, CLUBS), true);
}

TEST(test_cardless10){
    Card led(TEN, HEARTS);
    Card a(JACK, HEARTS);
    Card b(QUEEN, HEARTS);
    ASSERT_EQUAL(Card_less(a, b, led, CLUBS), true);
}


TEST(test_getsuit){
    Card a(KING, HEARTS);
    ASSERT_EQUAL(a.get_suit(), HEARTS);
}

TEST(test_getsuitt) {
    Card a(JACK, SPADES);
    ASSERT_EQUAL(a.get_suit(CLUBS), CLUBS);
}

TEST(test_getrank){
    Card a(KING, HEARTS);
    ASSERT_EQUAL(a.get_rank(), KING);
}

TEST(test_isfaceorace){
    Card a(KING, HEARTS);
    ASSERT_EQUAL(a.is_face_or_ace(), true);
}

TEST(test_isfaceorace2){
    Card a(ACE, HEARTS);
    ASSERT_EQUAL(a.is_face_or_ace(), true);
}

TEST(test_isfaceorace3){
    Card a(TEN, HEARTS);
    ASSERT_EQUAL(a.is_face_or_ace(), false);
}

TEST(test_isrightbower){
    Card a(JACK, HEARTS);
    ASSERT_EQUAL(a.is_right_bower(HEARTS), true);
}

TEST(test_isrightbower2){
    Card a(JACK, HEARTS);
    ASSERT_EQUAL(a.is_right_bower(DIAMONDS), false);
}

TEST(test_isleftbower){
    Card a(JACK, HEARTS);
    ASSERT_EQUAL(a.is_left_bower(DIAMONDS), true);
}


TEST(test_isleftbower2){
    Card a(JACK, HEARTS);
    ASSERT_EQUAL(a.is_left_bower(DIAMONDS), true);
}

TEST(test_istrump){
    Card a(JACK, HEARTS);
    ASSERT_EQUAL(a.is_trump(HEARTS), true);
}

TEST(test_istrump2){
    Card a(JACK, HEARTS);
    ASSERT_EQUAL(a.is_trump(DIAMONDS), true);
}

TEST(test_istrump3){
    Card a(TEN, CLUBS);
    ASSERT_EQUAL(a.is_trump(SPADES), false);
}

TEST(test_suitnext){
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}

TEST(test_suitnext2){
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
}

TEST(test_outoperator){
    Card a(JACK, SPADES);
    ostringstream os;
    os << a;
    ASSERT_EQUAL(os.str(), "Jack of Spades");
}

TEST(test_inoperator) {
    istringstream is("Jack of Spades");
    Card c;
    is >> c;
    ASSERT_EQUAL(c, Card(JACK, SPADES));
}

TEST_MAIN()