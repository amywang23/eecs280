#include <iostream>
#include <fstream>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
using namespace std;

class Game {
    private:
        std::vector<Player*> players;
        Pack pack;
        int points_to_win;
        
        bool shuffle;

        int team1Points;
        int team2Points;
        int handNum;

        
        void deal() {
            int dealer = handNum % 4;
            cout << *players[dealer] << " deals\n";

            // 3 - 2 - 3 - 2
            for (int i = 0; i < 3; i++) {
                players[(dealer+1)%4]->add_card(pack.deal_one());
            }
            for (int i = 0; i < 2; i++) {
                players[(dealer+2)%4]->add_card(pack.deal_one());
            }
            for (int i = 0; i < 3; i++) {
                players[(dealer+3)%4]->add_card(pack.deal_one());
            }
            for (int i = 0; i < 2; i++) {
                players[dealer]->add_card(pack.deal_one());
            }

            // 2 - 3 - 2 - 3
            for (int i = 0; i < 2; i++) {
                players[(dealer+1)%4]->add_card(pack.deal_one());
            }
            for (int i = 0; i < 3; i++) {
                players[(dealer+2)%4]->add_card(pack.deal_one());
            }
            for (int i = 0; i < 2; i++) {
                players[(dealer+3)%4]->add_card(pack.deal_one());
            }
            for (int i = 0; i < 3; i++) {
                players[dealer]->add_card(pack.deal_one());
            }
            
            
        }

        void shuffleHand() {
            if (shuffle) {
                pack.shuffle();
            }
            else {
                pack.reset();
            }
        }

        Suit make_trump(Card& upcard, int& trumpMakingPlayer) {
            int dealerPos = handNum % 4;
            bool trumpMadeRound1 = false;
            Suit orderUpSuit;

            // round1 of making trump
            for (int i = (dealerPos+1) % 4; i < 
            ((dealerPos+1) % 4)+4 && !trumpMadeRound1; i++) {
                // dealer index
                if (i % 4 == dealerPos) {
                    trumpMadeRound1 = players[i%4]->make_trump(upcard, 
                    true, 1, orderUpSuit);
                }
                // non dealer index
                else {
                    trumpMadeRound1 = players[i%4]->make_trump(upcard, 
                    false, 1, orderUpSuit);
                }
                // print pass
                if (trumpMadeRound1 == false) {
                    cout << *players[i%4] << " passes\n";
                }
                // someone orders up
                else {
                    cout << *players[i%4] << " orders up " << 
                    orderUpSuit << endl << endl;
                    trumpMakingPlayer = i%4;
                    // first round if dealer wants to pick up the upcard
                    players[dealerPos] -> add_and_discard(upcard);
                    return orderUpSuit;
                }

            }

            // round2 of making trump given round 1 is not made
            if (!trumpMadeRound1) {
                for (int i = (dealerPos+1) % 4; i < ((dealerPos+1) % 4)+4 
                && !trumpMadeRound1; i++) {
                    // dealer index
                    if (i % 4 == dealerPos) {
                        trumpMadeRound1 = players[i%4]->make_trump(upcard, 
                        true, 2, orderUpSuit);
                    }
                    // non dealer index
                    else {
                        trumpMadeRound1 = players[i%4]->make_trump(upcard, 
                        false, 2, orderUpSuit);
                    }
                    // print pass
                    if (!trumpMadeRound1) {
                        cout << *players[i%4] << " passes\n";
                    }
                    // someone orders up
                    else {
                        cout << *players[i%4] << " orders up " << 
                        orderUpSuit << endl << endl;
                        trumpMakingPlayer = i%4;
                        return orderUpSuit;
                    }

                }

            }
            // should not get here
            return Suit(DIAMONDS);
        }

        void updateScore(int trumpMakingTeam, 
        int team1TrickWins, int team2TrickWins) {
            if (trumpMakingTeam == 1 && 
            (team1TrickWins == 3 || team1TrickWins == 4)) {
                team1Points++;
            }
            else if (trumpMakingTeam == 2 && 
            (team2TrickWins == 3 || team2TrickWins == 4)) {
                team2Points++;
            }
            else if (trumpMakingTeam == 1 && 
            team1TrickWins == 5) {
                team1Points += 2;
                cout << "march!\n";
            }
            else if (trumpMakingTeam == 2 && 
            team2TrickWins == 5) {
                team2Points += 2;
                cout << "march!\n";
            }
            else if (trumpMakingTeam == 1 && 
            (team2TrickWins == 3 || team2TrickWins == 4 
            || team2TrickWins == 5)) {
                team2Points += 2;
                cout << "euchred!\n";
            }
            else if (trumpMakingTeam == 2 && 
            (team1TrickWins == 3 || team1TrickWins == 4 
            || team1TrickWins == 5)) {
                team1Points += 2;
                cout << "euchred!\n";
            }
        }

        void play_hand(Suit& trumpSuit, int trumpMakingPlayer) {
            // function to simulate playing one hand (5 tricks)

            int trumpMakingTeam = 1;
            if (trumpMakingPlayer == 1 || trumpMakingPlayer == 3) {
                trumpMakingTeam = 2;
            }

            // handNum % 4 = dealerIndex
            int leader = ((handNum+1) % 4); 
            // after first round becomes winner of previous trick
            int team1TrickWins = 0; 
            // player 0 and player 2
            int team2TrickWins = 0; 
            // player 1 and player 3
            for (int trick = 0; trick < 5; trick++) {
                Card cards[4]; 
                // indexes corresponding to player0,1,2,3 and the cards they played
                Card leadCard;
                int winningCardIndex = 0; // also winning player index
                
                for (int person = leader; person < leader+4; person++) {
                    int player = person%4;
                    if (player == leader) {
                        leadCard = players[player]->lead_card(trumpSuit);
                        cards[player] = leadCard;
                        cout << leadCard << " led by " << *players[player] << endl;
                    }
                    else {
                        cards[player] = players[player]->play_card(leadCard, 
                        trumpSuit);
                        cout << cards[player] << " played by " 
                        << *players[player] << endl;

                    }
                }
                // by this point all 4 choices of cards played by the 4 players is stored in the cards array
                // time for comparison to see who played the highest card

                // comparing player0 to player1's card
                if (Card_less(cards[0], cards[1], 
                leadCard, trumpSuit)) {
                    winningCardIndex = 1;
                }

                // comparing the highest card so far to player2's card
                if (Card_less(cards[winningCardIndex], 
                cards[2], leadCard, trumpSuit)) {
                    winningCardIndex = 2;
                }

                // comparing the highest card so far to player3's card
                if (Card_less(cards[winningCardIndex], 
                cards[3], leadCard, trumpSuit)) {
                    winningCardIndex = 3;
                    // winningCardIndex now contains the player's index with the most valuable card (the winner for this trick)
                }
                
                // figuring out if team1 or team2 won the trick based on winningCardIndex
                if (winningCardIndex == 0 || winningCardIndex == 2) {
                    team1TrickWins++;
                }
                else {
                    team2TrickWins++;
                }
                cout << *players[winningCardIndex] << " takes the trick\n\n";
                leader = winningCardIndex;
                
            }
            // at this point 5 tricks are complete, hence 1 hand is complete, printing winner of hand now
            if (team1TrickWins > team2TrickWins) {
                cout << *players[0] << " and " << 
                *players[2] << " win the hand" << endl;
            }
            else {
                cout << *players[1] << " and " <<
                *players[3] << " win the hand" << endl;
            }
            // calling updateScore function to update team scores and determine whether there is a march, euchre
            updateScore(trumpMakingTeam, team1TrickWins, team2TrickWins);
            
            

        }

 public:
  Game(string playerNames[], string playerTypes[], 
  int points_to_win, string shuffleDecision, istream& packFile): 
    pack(packFile), points_to_win(points_to_win), 
    team1Points(0), team2Points(0), handNum(0) {
    
    for (int i = 0; i < 4; i++) {
        players.push_back(Player_factory(playerNames[i], 
        playerTypes[i]));
    }

    shuffle = (shuffleDecision == "shuffle") ? true : false;
  }
  void play() {
    cout << endl;
    while (team1Points < points_to_win && team2Points < points_to_win) {
        // start of a hand
        shuffleHand();
        
        cout << "Hand " << handNum << "\n";
        deal();
        Card upcard = pack.deal_one();
        cout << upcard << " turned up\n";
        
        // who called Trump
        int trumpMakingPlayer;

        Suit trumpSuit = make_trump(upcard, trumpMakingPlayer);

        

        // play 1 hand (5 tricks)
        play_hand(trumpSuit, trumpMakingPlayer);
        cout << *players[0] << " and " << *players[2] << 
        " have " << team1Points << " points" << endl;
        cout << *players[1] << " and " << *players[3] << 
        " have " << team2Points << " points" << endl << endl;

        handNum++;
    }

    // someone has won and while loop has exited
    if (team1Points > team2Points) {
        cout << *players[0] << " and " << *players[2] << " win!\n";
    }
    else {
        cout << *players[1] << " and " << *players[3] << " win!\n";
    }


  }
  ~Game() {
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }

  }

 
};


int main(int argc, char* argv[]) {
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        return -1;
    }

    int points_to_win = atoi(argv[3]);
    string shuffleDecision(argv[2]);
    

    if (points_to_win < 1 || points_to_win > 100 || 
    (shuffleDecision != "shuffle" && shuffleDecision != "noshuffle")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        return -1;
    }

    string name0(argv[4]), type0(argv[5]), name1(argv[6]), 
    type1(argv[7]), name2(argv[8]), type2(argv[9]), name3(argv[10]), 
    type3(argv[11]);
    


    if ((type0 != "Human" && type0 != "Simple") || 
    (type1 != "Human" && type1 != "Simple") || 
    (type2 != "Human" && type2 != "Simple") 
    || (type3 != "Human" && type3 != "Simple")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        return -1;
    }

    string playerNames[4];
    string playerTypes[4];

    playerNames[0] = name0;
    playerTypes[0] = type0;

    playerNames[1] = name1;
    playerTypes[1] = type1;

    playerNames[2] = name2;
    playerTypes[2] = type2;

    playerNames[3] = name3;
    playerTypes[3] = type3;


    string pack_filename(argv[1]);
    std::ifstream packFile(argv[1]);
    if (!packFile.is_open()) {
        cout << "Error opening " << pack_filename << endl;
        return -1;
    }

    for (int i = 0; i < 12; i++) {
        cout << argv[i] << " ";
    }

    // Read command line args and check for errors
    Game game(playerNames, playerTypes, 
    points_to_win, shuffleDecision, packFile);
    game.play();
    return 0;

}