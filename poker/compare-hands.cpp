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
	Card lastCard;
	map<char,list<Card> > suitsToCards;
	map<char,list<Card> > numsToCards;

	bool straight = true;
	Hand::const_iterator it;
	for (it = hand.begin(); it != hand.end(); it++) {
		Card card = *it;

		if (it != hand.begin() && straight) {
			try {
				straight = (lastCard.succ() == card);
			} catch (char const * msg) {
				straight = false;
			}
		}
		suitsToCards[card.suit].push_back(card);
		numsToCards[card.num].push_back(card);
		lastCard = *it;
	}

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
