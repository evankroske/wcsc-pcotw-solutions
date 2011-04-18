#include <iostream>
#include <list>


using namespace std;

class Card;
typedef list<Card> Hand;
typedef pair< Hand, Hand > Round;

class Card {
public:
	Card (char num, char suit);
	char num, suit;
};

Card::Card (char num, char suit):
	num(num),
	suit(suit) {}

list< Round > rounds;

ostream & operator<< (ostream & out, Card const & card) {
	out << card.num << card.suit;
	return out;
}

ostream & operator<< (ostream & out, Hand const & hand) {
	Hand::const_iterator it = hand.begin();
	while (true) {
		Card card = *it;
		it++;
		if (it != hand.end()) {
			out << card << " ";
		} else {
			out << card;
			break;
		}
	}
	return out;
}

Hand getHand () {
	list< Card > hand;
	for (int i = 0; i < 5; i++) {
		string cardString;
		cin >> cardString;
		Card card(cardString[0], cardString[1]);
		hand.push_back(card);
	}
	return hand;
}

pair< Hand, Hand > getHands () {
	Hand black = getHand();
	Hand white = getHand();
	return pair< Hand, Hand >(black, white);
}

int main () {
	while (true) {
		pair< Hand, Hand > round = getHands();
		if (cin.good()) {			
			rounds.push_back(round);
		} else {
			break;
		}
	}

	list< Round >::iterator it;
	for (it = rounds.begin(); it != rounds.end(); it++) {
		Round round = *it;
		cout << "Black's hand: " << round.first << endl;
		cout << "White's hand: " << round.second << endl;
	}
	return 0;
}
