#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_add_card) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c(TEN, SPADES);
    alice -> add_card(c);
    Suit trump = SPADES;

    ASSERT_EQUAL(alice -> play_card(c, trump), Card(TEN, SPADES));

    delete alice;
}

// Add more tests here
TEST(test_player_operator) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c(TEN, CLUBS);
    alice ->add_card(c);
    ostringstream os;
    os << alice->get_name();
    ASSERT_EQUAL(os.str(), "Alice");

    delete alice;
}

TEST(test_make_trump) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(QUEEN, SPADES));
    alice ->add_card(Card(KING, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, true, 1, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump2) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(SEVEN, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, true, 1, trump);
    ASSERT_EQUAL(orderup, false);

    delete alice;
}

TEST(test_make_trump3) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card jack_spades(JACK, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(jack_spades, true, 1, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump4) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, HEARTS));
    alice ->add_card(Card(JACK, CLUBS));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, true, 1, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump5) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, HEARTS));
    alice ->add_card(Card(JACK, CLUBS));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, false, 1, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump6) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, HEARTS));
    alice ->add_card(Card(JACK, CLUBS));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(FIVE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, false, 1, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}


TEST(test_make_trump7) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(SEVEN, CLUBS));
    alice ->add_card(Card(JACK, HEARTS));

    Card nine_spades(NINE, CLUBS);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, true, 2, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump8) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(SEVEN, CLUBS));
    alice ->add_card(Card(SIX, HEARTS));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, false, 2, trump);
    ASSERT_EQUAL(orderup, false);

    delete alice;
}

TEST(test_make_trump9) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(JACK, CLUBS));
    alice ->add_card(Card(SIX, HEARTS));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = alice ->make_trump(nine_spades, false, 2, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump10) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(JACK, CLUBS));
    alice ->add_card(Card(SIX, HEARTS));

    Card nine_spades(NINE, CLUBS);
    Suit trump = CLUBS;
    bool orderup = alice ->make_trump(nine_spades, false, 2, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump11) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(SEVEN, CLUBS));
    alice ->add_card(Card(SIX, HEARTS));

    Card nine_spades(NINE, CLUBS);
    Suit trump = CLUBS;
    bool orderup = alice ->make_trump(nine_spades, true, 2, trump);
    ASSERT_EQUAL(orderup, true);

    delete alice;
}

TEST(test_make_trump12) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(SEVEN, CLUBS));
    alice ->add_card(Card(SIX, HEARTS));

    Card nine_spades(NINE, CLUBS);
    Suit trump = CLUBS;
    bool orderup = alice ->make_trump(nine_spades, false, 2, trump);
    ASSERT_EQUAL(orderup, false);

    delete alice;
}

TEST(test_add_and_discard) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));

    alice -> add_and_discard(Card(TEN, SPADES));
    Suit trump = SPADES;

    ASSERT_EQUAL(alice->play_card(Card(NINE, SPADES), trump), Card(TEN, SPADES));
    delete alice;
}

TEST(test_lead_card) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(SEVEN, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    Card temp = alice -> lead_card(trump);
    Card t(ACE, SPADES);
    ASSERT_EQUAL(temp, t);
    delete alice;
}

TEST(test_lead_card2) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = DIAMONDS;
    Card temp = alice -> lead_card(trump);
    Card t(ACE, SPADES);
    ASSERT_EQUAL(temp, t);
    delete alice;
}

TEST(test_lead_card3) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, CLUBS));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, CLUBS));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    Card temp = alice -> lead_card(trump);
    Card t(NINE, CLUBS);
    ASSERT_EQUAL(temp, t);
    delete alice;
}

TEST(test_play_card) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, SPADES));
    alice ->add_card(Card(EIGHT, SPADES));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    Card temp = alice->play_card(nine_spades, trump);
    Card t(JACK, SPADES);
    ASSERT_EQUAL(temp, t);
    delete alice;
}

TEST(test_play_card2) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, DIAMONDS));
    alice ->add_card(Card(EIGHT, HEARTS));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card c(NINE, HEARTS);
    Suit trump = CLUBS;
    Card temp = alice->play_card(c, trump);
    Card t(EIGHT, HEARTS);
    ASSERT_EQUAL(temp, t);
    delete alice;
}

TEST(test_play_card3) {
    Player * alice = Player_factory("Alice", "Simple");
    alice ->add_card(Card(NINE, SPADES));
    alice ->add_card(Card(TEN, DIAMONDS));
    alice ->add_card(Card(EIGHT, HEARTS));
    alice ->add_card(Card(JACK, SPADES));
    alice ->add_card(Card(ACE, SPADES));

    Card c(NINE, HEARTS);
    Suit trump = HEARTS;
    Card temp = alice->play_card(c, trump);
    Card t(EIGHT, HEARTS);
    ASSERT_EQUAL(temp, t);
    delete alice;
}

TEST_MAIN()