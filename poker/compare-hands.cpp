#include <iostream>
#include <list>
#include <map>
#include "poker.h"

using namespace std;

Hand getHand () {
	Cards cards;
	for (int i = 0; i < 5; i++) {
		string cardString;
		cin >> cardString;
		Card card(cardString[0], cardString[1]);
		cards.push_back(card);
	}
	return Hand(cards);
}

Round getRound () {
	Hand black = getHand();
	Hand white = getHand();
	return Round(black, white);
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
		Hand b = it->first;
		Hand w = it->second;
		cout << "Black's hand: " << b << endl;
		cout << "White's hand: " << w << endl;
	}
	return 0;
}
