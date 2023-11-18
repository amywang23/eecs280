#include "Player.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <array>

using namespace std;

class SimplePlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;
public:
    SimplePlayer(string name): name(name) {

    }
    const std::string & get_name() const {
        return name;
    }
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) {
        hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
    int round, Suit &order_up_suit) const {
        if (round == 1) {
            int countFaceTrumpCards = 0;
        for (int i = 0; i < hand.size(); i++) {
            if ((hand[i].is_face_or_ace() 
            || hand[i].is_left_bower(upcard.get_suit()) 
            || hand[i].is_right_bower(upcard.get_suit()))
            && hand[i].is_trump(upcard.get_suit())) {
                countFaceTrumpCards++;

            }
        }
        if (countFaceTrumpCards >= 2) {
            order_up_suit = upcard.get_suit();
            return true;
        }
        else {
            return false;
        }
    }
    else {
        Suit requiredSuit = Suit_next(upcard.get_suit());
        if (is_dealer) {
            order_up_suit = requiredSuit;
            return true;
        }
        else {
            int countFaceTrumpCards = 0;
        
            for (int i = 0; i < hand.size(); i++) {
            
            if ((hand[i].is_face_or_ace() 
            || hand[i].is_left_bower(requiredSuit) 
            || hand[i].is_right_bower(requiredSuit))
            && hand[i].is_trump(requiredSuit)) {
                countFaceTrumpCards++;
            }
            }
            if (countFaceTrumpCards >= 1) {
                order_up_suit = requiredSuit;
                return true;
            }
            else {
                return false;
            }


        }
        
    }

}
//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void add_and_discard(const Card &upcard) {
    hand.push_back(upcard);
    int indexLowest = 0;
    for (int i = 0; i < hand.size(); i++) {
        if (Card_less(hand[i], hand[indexLowest], upcard.get_suit())) {
            indexLowest = i;
        }
    }
    hand.erase(hand.begin()+indexLowest);

}

//REQUIRES Player has at least one card
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card lead_card(Suit trump) {
    bool allTrump = true;
    int highestTrump = -1;
    int highestNonTrump = -1;
// When a Simple Player leads a trick, they play the 
//highest non-trump card in their hand. 
// If they have only trump cards, they play the highest trump card 
//in their hand.
for (int i = 0; i < hand.size(); i++) {
    if (!hand[i].is_trump(trump)) {
        allTrump = false;
    }

    if (hand[i].is_trump(trump) && highestTrump == -1) {
        highestTrump = i;
    }

    else if (hand[i].is_trump(trump) && highestTrump != -1) {
        if (Card_less(hand[highestTrump], hand[i], trump)) {
            highestTrump = i;
        }
    }

    if (!hand[i].is_trump(trump) && highestNonTrump == -1) {
        highestNonTrump = i;
    }
    else if (!hand[i].is_trump(trump) && highestNonTrump != -1) {
        if (Card_less(hand[highestNonTrump], hand[i], trump)) {
            highestNonTrump = i;
        }
    }

}

if (allTrump) {
    Card highest = hand[highestTrump];
    hand.erase(hand.begin()+highestTrump);
    return highest;
}
else {
    Card highest = hand[highestNonTrump];
    hand.erase(hand.begin()+highestNonTrump);
    return highest;
}
}

Card play_card(const Card &led_card, Suit trump) {
int lowestCard = -1;
int highestSuitCard = -1;
//Suit ledCardRealSuit = led_card.get_suit();
for (int i = 0; i < hand.size(); i++) {
    if ((hand[i].get_suit(trump) 
    == led_card.get_suit(trump)) 
    && highestSuitCard == -1) {
        highestSuitCard = i;
    }
    else if ((hand[i].get_suit(trump) 
    == led_card.get_suit(trump)) 
    && highestSuitCard != -1) {
        if (Card_less(hand[highestSuitCard], 
        hand[i], led_card, trump)) {
            highestSuitCard = i;
        }
    }
    if ((hand[i].get_suit(trump) 
    != led_card.get_suit(trump)) 
    && lowestCard == -1) {
        lowestCard = i;
    }
    else if ((hand[i].get_suit(trump) 
    != led_card.get_suit(trump)) 
    && lowestCard != -1) {
    if (Card_less(hand[i], hand[lowestCard], 
        led_card, trump)) {
            lowestCard = i;
        }
    }
}
if (highestSuitCard == -1) {
    Card c = hand[lowestCard];
    hand.erase(hand.begin() + lowestCard);
    return c;
}
else {
    Card c = hand[highestSuitCard];
    hand.erase(hand.begin()+highestSuitCard);
    return c;

}
}


};

class HumanPlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;
    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";     
    }
public:
    HumanPlayer(string name) : name(name) { 
        
    }

    const std::string & get_name() const {
        return name;
    }
    
    void add_card(const Card &c) {
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }
    bool make_trump(const Card &upcard, bool is_dealer,
        int round, Suit &order_up_suit) const {

        print_hand();
        cout << "Human player " << name << 
        ", please enter a suit, or \"pass\":\n";
        string decision;
        cin >> decision;
        if(decision != "pass"){
            Suit ordered_up = string_to_suit(decision);
            order_up_suit = ordered_up;
            return true;
        }
        else{
            return false;
        }
    }

    void add_and_discard(const Card &upcard) {
        std::sort(hand.begin(), hand.end());
        print_hand();
        
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << 
        ", please select a card to discard:\n";
            
        int choice;
        cin >> choice;
        // cout << "\n" << "index: " << index << endl;
        
        if (choice != -1) { 
            
            // cout << "\n" << "index: " << index << endl;

            hand.erase(hand.begin()+choice);
            hand.push_back(upcard);

        }
        std::sort(hand.begin(), hand.end());

    }

    Card lead_card(Suit trump) {
        int index;
        std::sort(hand.begin(), hand.end());
        print_hand();
        cout << "Human player " << name << 
        ", please select a card:\n";

        
        cin >> index;

        Card c = hand[index];
        // cout << "\n" << "index: " << index << c << endl;
        hand.erase(hand.begin() + index);
        std::sort(hand.begin(), hand.end());
        return c;
    }

    Card play_card(const Card &led_card, Suit trump) {
        std::sort(hand.begin(), hand.end());
        return lead_card(trump);
    }



};

Player * Player_factory(const string &name, const string &strategy) {
// We need to check the value of strategy and return 
// the corresponding player type.
if (strategy == "Simple") {
// The "new" keyword dynamically allocates an object.
return new SimplePlayer(name);
}
else if (strategy == "Human"){
return new HumanPlayer(name);
}
// Repeat for each other type of Player

// Invalid strategy if we get here
return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
os << p.get_name();
return os;
}