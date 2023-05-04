#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const string faces[] = {"Hungry", "Thirsty", "Naked", "Homeless", "Sick", "Dead", "Prisoner", "Poor","Instruct"};

class Card {
    private:
        int face;
        int status;
    public:
        Card() {
            face = 0;
            status = 0;
        }
        Card(int f, int s) {
            face = f;
            status = s;
        }
        string toString() {
            if (status == 0) {
                return faces[face];
            } else {
                return faces[face] + "/" + faces[status] + " (" + to_string(1) + ")";
            }
        }
};

class Deck {
    public:
        vector<Card> deck1;
        vector<Card> deck2;
    Deck() {
        for (int i = 0; i < 36; i++) {
            deck1.push_back(Card(i % 9, 0));
        }
        for (int i = 0; i < 24; i++) {
            deck2.push_back(Card(rand() % 9, rand() % 9));
        }
    }
    void printDeck1() {
        for (int i = 0; i < deck1.size(); i++) {
            cout << deck1[i].toString() << endl;
        }
    }
    void printDeck2() {
        for (int i = 0; i < deck2.size(); i++) {
            cout << deck2[i].toString() << endl;
        }
    }
    void shuffleDeck2() {
        random_shuffle(deck2.begin(), deck2.end());
        printDeck2();
    }
};

class ActsHand {
    public:
        Card actsHand[4];
    // Constructor
    ActsHand(vector<Card> &deck1) {
        random_shuffle(deck1.begin(), deck1.end());
        for (int i = 0; i < 4; i++) {
            actsHand[i] = deck1[i];
        }
        sort(actsHand, actsHand + 4, [](Card a, Card b) { return a.toString() < b.toString(); });
    }
};

class NeighborHand {
    public:
        Card neighborHand[6];
    // Constructor
    NeighborHand(vector<Card> &deck2) {
        random_shuffle(deck2.begin(), deck2.end());
        for (int i = 0; i < 6; i++) {
            neighborHand[i] = deck2[i];
        }
        sort(neighborHand, neighborHand + 6, [](Card a, Card b) { return a.toString() < b.toString(); });
    }

    void displayCards(bool toggle) {
      if (toggle) {
          for (int i = 0; i < sizeof(neighborHand)/sizeof(neighborHand[0]); ++i) {
              cout << neighborHand[i].toString() << endl;
          }
      } else {
          cout << neighborHand[0].toString() + " (1)"<<endl;
      }
    }
};

int main() {
    srand(time(NULL));
    Deck d;
    cout << "Deck 1:" << endl;
    d.printDeck1();
    cout << endl << "Deck 2:" << endl;
    d.printDeck2();
    cout << endl << "Shuffled Deck 2:" << endl;
    d.shuffleDeck2();

    int numPlayers;
    cout << endl << "Enter the number of players (between 2 and 4): ";
    cin >> numPlayers;

    vector<ActsHand> actsHands(numPlayers, ActsHand(d.deck1));
    vector<NeighborHand> neighborHands(numPlayers, NeighborHand(d.deck2));

    for (int i = 0; i < numPlayers; ++i) {
      cout << endl << "Player " << i+1 << "'s Act Hand:" << endl;
      random_shuffle(actsHands[i].actsHand, actsHands[i].actsHand + 4);
      for (int j = 0; j < sizeof(actsHands[i].actsHand)/sizeof(actsHands[i].actsHand[0]); ++j) {
          cout << actsHands[i].actsHand[j].toString() << endl;
      }

      cout << endl << "Player " << i+1 << "'s Neighbor Hand:" << endl;
      neighborHands[i].displayCards(false);

      bool toggle = false;
      char input;
      while (true) {
          cout<<endl<<"Press 't' to toggle between displaying all cards in the neighbor's hand and displaying only the first card in the stack: ";
          cin >> input;

          if (input == 't') {
              toggle = !toggle;
              break;
          } else {
              cout<<endl<<"Invalid input. Please try again."<<endl;
          }
      }

      neighborHands[i].displayCards(toggle);

      cout<<endl<<"Press any key to continue"<<endl;
      cin.ignore();
      cin.get();
    }

    return 0;
}

