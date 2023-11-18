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
            for (int i = (dealerPos+1) % 4; i < ((dealerPos+1) % 4)+4 && !trumpMadeRound1; i++) {
                // dealer index
                if (i % 4 == dealerPos) {
                    trumpMadeRound1 = players[i%4]->make_trump(upcard, true, 1, orderUpSuit);
                }
                // non dealer index
                else {
                    trumpMadeRound1 = players[i%4]->make_trump(upcard, false, 1, orderUpSuit);
                }
                // print pass
                if (trumpMadeRound1 == false) {
                    cout << *players[i%4] << " passes\n";
                }
                // someone orders up
                else {
                    cout << *players[i%4] << " orders up " << orderUpSuit << endl;
                    trumpMakingPlayer = i%4;
                    // first round if dealer wants to pick up the upcard
                    players[dealerPos] -> add_and_discard(upcard);
                    return orderUpSuit;
                }

            }

            // round2 of making trump given round 1 is not made
            if (!trumpMadeRound1) {
                for (int i = (dealerPos+1) % 4; i < ((dealerPos+1) % 4)+4 && !trumpMadeRound1; i++) {
                    // dealer index
                    if (i % 4 == dealerPos) {
                        trumpMadeRound1 = players[i%4]->make_trump(upcard, true, 1, orderUpSuit);
                    }
                    // non dealer index
                    else {
                        trumpMadeRound1 = players[i%4]->make_trump(upcard, false, 1, orderUpSuit);
                    }
                    // print pass
                    if (!trumpMadeRound1) {
                        cout << *players[i%4] << " passes\n";
                    }
                    // someone orders up
                    else {
                        cout << *players[i%4] << " orders up " << orderUpSuit << endl;
                        trumpMakingPlayer = i%4;
                        return orderUpSuit;
                    }

                }

            }
            // should not get here
            return Suit(DIAMONDS);
        }

        void play_hand(Card &led_card, Suit trump) { //code
            int dealerPos = handNum % 4;
            int round = 1;
            if(round == 1){
                for(int i = dealerPos+1; i < (dealerPos+1)+4; ++i){
                    players[i%4]->play_card(led_card, trump);
                }
            }
        }

 public:
  Game(string playerNames[], string playerTypes[], int points_to_win, string shuffleDecision, istream& packFile): 
    pack(packFile), points_to_win(points_to_win), team1Points(0), team2Points(0), handNum(0) {
    
    for (int i = 0; i < 4; i++) {
        players.push_back(Player_factory(playerNames[i], playerTypes[i]));
    }

    shuffle = (shuffleDecision == "shuffle") ? true : false;
  }
  void play() {
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
        cout << trumpSuit;

        // int numTricksTeam1 = 0;
        // int numTricksTeam2 = 0;

        // play 1 hand (5 tricks)
        //for loop
        play_hand(upcard, trumpSuit);
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
    

    if (points_to_win < 1 || points_to_win > 100 || (shuffleDecision != "shuffle" && shuffleDecision != "noshuffle")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        return -1;
    }

    string name0(argv[4]), type0(argv[5]), name1(argv[6]), type1(argv[7]), name2(argv[8]), type2(argv[9]), name3(argv[10]), type3(argv[11]);
    


    if ((type0 != "Human" && type0 != "Simple") || (type1 != "Human" && type1 != "Simple") || (type2 != "Human" && type2 != "Simple") || (type3 != "Human" && type3 != "Simple")) {
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
    Game game(playerNames, playerTypes, points_to_win, shuffleDecision, packFile);
    game.play();


}