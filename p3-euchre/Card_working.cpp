#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

Card::Card(): 
  rank(TWO), suit(SPADES) {

}

Card::Card(Rank rank_in, Suit suit_in):
  rank(rank_in), suit(suit_in) {

}

Rank Card::get_rank() const {
  return rank;
}

Suit Card::get_suit() const {
  return suit;
}

//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
Suit Card::get_suit(Suit trump) const {
  if (is_left_bower(trump)) {
    return trump;
  }
  return suit;
}

bool Card::is_face_or_ace() const {
  return (rank == ACE || rank == KING || rank == QUEEN || rank == JACK);
}

bool Card::is_right_bower(Suit trump) const {
  return (rank == JACK && suit == trump);
}

bool Card::is_left_bower(Suit trump) const {
  return (rank == JACK && suit == Suit_next(trump));
}

bool Card::is_trump(Suit trump) const {
  return (suit == trump || is_left_bower(trump));
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit) {
  return Suit((suit+2) % 4);
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump) {
  
  // a is right bower
  if (a.is_right_bower(trump)) {
    return false;
  }
  // b is right bower
  else if (b.is_right_bower(trump)) {
    return true;
  }
  // a is left bower
  else if (a.is_left_bower(trump)) {
    return false;
  }
  // b is left bower
  else if (b.is_left_bower(trump)) {
    return true;
  }
  // a trump, and b not trump
  if (a.is_trump(trump) && !b.is_trump(trump)) {
    return false;
  }
  // b trump, and a not trump
  else if (b.is_trump(trump) && !a.is_trump(trump)) {
    return true;
  }
  // now deal with both are trumps (same suit de)
  else if (a.is_trump(trump) && b.is_trump(trump)) {
    if (a < b) {
      return true;
    }
    else {
      return false;
    }
  }

  // now deal with when they are not trumps (determine just by rank)
  else {
    if (a < b) {
      return true;
    }
    else {
      return false;
    }
  }
  
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) { //use previous card_less function in this one
  
  // a is right bower
  if (a.get_suit() == trump || b.get_suit() == trump) {
    return Card_less(a, b, trump);
  }
  // b is right bower
  else if (b.is_right_bower(trump)) {
    return true;
  }
  // a is left bower
  else if (a.is_left_bower(trump)) {
    return false;
  }
  // b is left bower
  else if (b.is_left_bower(trump)) {
    return true;
  }
  // a trump, and b not trump
  if (a.is_trump(trump) && !b.is_trump(trump)) {
    return false;
  }
  // b trump, and a not trump
  else if (b.is_trump(trump) && !a.is_trump(trump)) {
    return true;
  }
  // now deal with both are trumps (same suit de)
  else if (a.is_trump(trump) && b.is_trump(trump)) {
    if (a < b) {
      return true;
    }
    else {
      return false;
    }
  }

  // a led, b not led
  if (a.get_suit(trump) == led_card.get_suit(trump) && b.get_suit(trump) != led_card.get_suit(trump)) {
    return false;
  }

  // b led, a not led
  else if (b.get_suit(trump) == led_card.get_suit(trump) && a.get_suit(trump) != led_card.get_suit(trump)) {
    return true;
  }

  // a and b both led
  else if (a.get_suit(trump) == led_card.get_suit(trump) && b.get_suit(trump) == led_card.get_suit(trump)) {
    if (a < b) {
      return true;
    }
    else {
      return false;
    }
  }


  // now deal with when they are not trumps or led (determine just by rank)
  else {
    if (a < b) {
      return true;
    }
    else {
      return false;
    }
  }

}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card) {
  std::string holder;
  is >> card.rank >> holder >> card.suit;
  return is;
}

bool operator<(const Card& lhs, const Card& rhs) { //recode
    if (lhs.get_rank() == rhs.get_rank()) {
      return (lhs.get_suit() < rhs.get_suit());
    }
    else {
      return (lhs.get_rank() < rhs.get_rank());
    }

}

bool operator<=(const Card& lhs,const Card& rhs) {
    return (lhs < rhs || lhs == rhs);
}
bool operator>(const Card& lhs, const Card& rhs) { // not less than and not equal to
    return (!(lhs < rhs) && !(lhs == rhs));
}

bool operator>=(const Card& lhs, const Card& rhs) {
    return (lhs > rhs || lhs == rhs);
}

bool operator==(const Card& lhs, const Card& rhs) { //recode
    return ((lhs.get_rank() == rhs.get_rank()) && (lhs.get_suit() == rhs.get_suit()));
}
bool operator!=(const Card& lhs, const Card& rhs){
    return (!(lhs == rhs));
}