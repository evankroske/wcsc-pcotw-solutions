#include <iostream>
#include <list>
#include <map>
#include "poker.h"

using namespace std;

Hand getHand () {
	Hand hand;
	for (int i = 0; i < 5; i++) {
		string cardString;
		cin >> cardString;
		Card card(cardString[0], cardString[1]);
		hand.push_back(card);
	}
	hand.sort();
	return hand;
}

Round getRound () {
	Hand black = getHand();
	Hand white = getHand();
	return Round(black, white);
}

void check (Hand const & hand) {
	bool straight = true;
	Card lastCard;

	bool flush;
	map<char,int> suits;

	Hand::const_iterator it;
	for (it = hand.begin(); it != hand.end(); it++) {
		Card card = *it;

		if (it != hand.begin() && straight) {
			straight = (lastCard.succ() == card);
		}

		if (suits.find(card.suit) != suits.end()) {
			suits[card.suit]++;
		} else {
			suits[card.suit] = 1;
		}
		lastCard = *it;
	}

	flush = (suits.size() == 1);

	if (straight) {
		cout << "Straight\n";
	}
	if (flush) {
		cout << "Flush\n";
	}
}

int main () {
	list<Round> rounds;
	while (true) {
		Round round = getRound();
		if (cin.good()) {			
			rounds.push_back(round);
		} else {
			break;
		}
	}

	list< Round >::iterator it;
	for (it = rounds.begin(); it != rounds.end(); it++) {
		Round round = *it;
		cout << "Black's hand: " << endl;
		check(round.first);
		cout << "White's hand: " << endl;
		check(round.second);
	}
	return 0;
}
