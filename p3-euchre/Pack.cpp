#include "Pack.hpp"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this functio
constexpr const char *const RANK_NAMES[] = {
    "Two", // TWO
    "Three", // THREE
    "Four", // FOUR
    "Five", // FIVE
    "Six", // SIX 
    "Seven", // SEVEN
    "Eight", // EIGHT
    "Nine", // NINE
    "Ten", // TEN
    "Jack", // JACK
    "Queen", // QUEEN
    "King", // KING
    "Ace" // ACE
};

constexpr const char *const SUIT_NAMES[] = {
    "Spades", // SPADES
    "Hearts", // HEARTS
    "Clubs", // CLUBS
    "Diamonds", // DIAMONDS
};

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack(): next(0) {
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        Suit suit(string_to_suit(SUIT_NAMES[s]));
        for (int r = NINE; r<= ACE; ++r) {
            Rank rank(string_to_rank(RANK_NAMES[r]));
            Card c(rank, suit);         
            cards[next++] = c;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input): next(0) {
    std::string rank;
    std::string of;
    std::string suit;
    for (int i = 0; i < 24; i++) {
        pack_input >> rank >> of >> suit;
        Rank r = string_to_rank(rank);
        Suit s = string_to_suit(suit);
        Card c(r, s);
        cards[i] = c;
    }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    return cards[next++];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void shuffleHelper(std::array<Card, 24>& cards) {
    std::array<Card, 24> cardsNew;
    // deal with placing 0-11 at the second position after bottom deck
    int indexOG = 0;
    for (int c = 1; c < 24; c+=2) {
        cardsNew[c] = cards[indexOG];
        cardsNew[c-1] = cards[indexOG+12];
        indexOG++;
    }
    cards = cardsNew;
}

void Pack::shuffle() {
    for (int s = 0; s < 7; s++) {
        shuffleHelper(cards);
    }
    reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
 return (next > 23);
}