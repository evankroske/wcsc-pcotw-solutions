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

void check (Hand const & hand) {
	/*

	bool straight = true;
	Hand::const_iterator it;

	bool flush = (suitsToCards.size() == 1);

	list<Card> fourTuples;
	map<char,list<Card> >::iterator numAndCards;
	for (numAndCards = numsToCards.begin(); numAndCards != numsToCards.end(); numAndCards++) {
		char num = numAndCards->first;
		list<Card> cards = numAndCards->second;
		if (cards.size() == 4) {
			fourTuples.push_back(cards.front());
		}
	}

	if (straight) {
		cout << "Straight\n";
	}
	if (flush) {
		cout << "Flush\n";
	}
	if (!fourTuples.empty()) {
		cout << "Four of a kind\n";
	}
	*/
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
		/*
		cout << "Straight: " << b.straight() << endl;
		cout << "Flush: " << b.flush() << endl;
		cout << "Straight: " << w.straight() << endl;
		cout << "Flush: " << w.flush() << endl;
		*/
	}
	return 0;
}
