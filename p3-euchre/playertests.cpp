TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

// Add more tests here

TEST(all_trumps) {
  Player * bob = Player_factory("Bob", "Simple");
  ASSERT_EQUAL(bob->get_name(), "Bob");

  Card one(Card::RANK_NINE, Card::SUIT_SPADES);
  Card two(Card::RANK_TEN, Card::SUIT_SPADES);
  Card three(Card::RANK_QUEEN, Card::SUIT_SPADES);
  Card four(Card::RANK_KING, Card::SUIT_SPADES);
  Card five(Card::RANK_ACE, Card::SUIT_SPADES);

  bob->add_card(one);
  bob->add_card(two);
  bob->add_card(three);
  bob->add_card(four);
  bob->add_card(five);

  Card upcard(Card::RANK_JACK, Card::SUIT_SPADES);
  string trump;
  ASSERT_FALSE(bob->make_trump(upcard, false, 2, trump));
  //ASSERT_EQUAL(trump, Card::SUIT_SPADES);
  ASSERT_TRUE(bob->make_trump(upcard, true, 2, trump));
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
  ASSERT_TRUE(bob->make_trump(upcard, false, 1, trump));
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);
  ASSERT_TRUE(bob->make_trump(upcard, true, 1, trump));
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  bob->add_and_discard(upcard);
  ASSERT_EQUAL(bob->lead_card(trump), upcard);
  ASSERT_EQUAL(bob->play_card(upcard, trump), five);
  ASSERT_EQUAL(bob->play_card(upcard, trump), four);
  ASSERT_EQUAL(bob->play_card(upcard, trump), three);
  ASSERT_EQUAL(bob->play_card(upcard, trump), two);

  delete bob;
}


TEST_MAIN()
