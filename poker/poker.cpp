#include "poker.h"

const string Card::VALUE("23456789TJQKA");

Card::Card ():
	num(0),
	suit(0) {}

Card::Card (char num, char suit):
	num(num),
	suit(suit) {}

Card Card::succ () {
	if (num == 'A') {
		throw "No successor";
	}
	return Card(VALUE[val()+1], suit);
}

int Card::cmp (Card const & other) const {
	int a = val(), b = other.val();
	if (a < b) {
		return -1;
	} else if (a > b) {
		return 1;
	} else {
		return 0;
	}
}

bool Card::operator< (Card const & other) {
	return cmp(other) < 0;
}

bool Card::operator== (Card const & other) {
	return cmp(other) == 0;
}

bool Card::operator> (Card const & other) {
	return cmp(other) > 0;
}

int Card::val () const {
	return VALUE.find(num);
}

ostream & operator<< (ostream & out, Card const & card) {
	out << card.num << card.suit;
	return out;
}

ostream & operator<< (ostream & out, Cards const & cards) {
	Cards::const_iterator it = cards.begin();
	while (it != cards.end()) {
		Card card = *it;
		it++;
		if (it != cards.end()) {
			out << card << " ";
		} else {
			out << card;
			break;
		}
	}
	return out;
}

const vector<string> Hand::rankToString = Hand::createRankNameVector();

Hand::Hand (Cards cards_):
	cards(cards_),
	deciders(),
	suitsToCards(),
	numsToCards(),
	straight(true),
	rank(NoHand) {
	cards.sort();

	Cards::iterator it;
	Card lastCard;
	for (it = cards.begin(); it != cards.end(); it++) {
		Card card = *it;
		numsToCards[card.num].push_back(card);
		suitsToCards[card.suit].push_back(card);

		if (straight && it != cards.begin()) {
			try {
				straight = (lastCard.succ() == card);
			} catch (char const * msg) {
				straight = false;
			}
		}
		lastCard = *it;
	}

	if (straightFlush()) {
		rank = StraightFlush;
		deciders.push_back(cards.back());
	} else if (fourOfAKind()) {
		rank = FourOfAKind;
		map<char,Cards>::const_iterator it;
		for (it = numsToCards.begin(); it != numsToCards.end(); it++) {
			if (it->second.size() == 4) {
				deciders.push_back(it->second.back());
			} else if (it->second.size() == 1) {
				deciders.push_back(it->second.back());
			}
		}
	} else if (flush()) {
		rank = Flush;
		deciders = cards;
		deciders.reverse();
	} else if (straight) {
		rank = Straight;
		deciders.push_back(cards.back());
	}
}

int Hand::cmp (Hand const & other) const {
	if (rank < other.rank) {
		return -1;
	} else if (rank > other.rank) {
		return 1;
	} else {
		Cards::const_iterator a, b;
		for (a = cards.begin(), b = other.cards.begin();
			a != cards.end(), b != other.cards.end();
			a++, b++) {
			Card cardA = *a;
			Card cardB = *b;
			if (cardA < cardB) {
				return -1;
			} else if (cardA > cardB) {
				return 1;
			}
		}
		if (b != other.cards.end()) {
			return -1;
		} else if (a != cards.end()) {
			return 1;
		} else {
			return 0;
		}
	}
}

bool Hand::operator< (Hand const & other) const {
	return cmp(other) < 0;
}

bool Hand::operator> (Hand const & other) const {
	return cmp(other) > 0;
}

bool Hand::operator== (Hand const & other) const {
	return cmp(other) == 0;
}

bool Hand::straightFlush () const {
	return straight && flush();
}

int Hand::numNOfAKind (int n) const {
	int count = 0;
	map<char,Cards>::const_iterator it;
	for (it = numsToCards.begin(); it != numsToCards.end(); it++) {
		if (it->second.size() == n) {
			count++;
		}
	}
	return count;
}

bool Hand::fourOfAKind () const {
	return numNOfAKind(4) > 0;
}

bool Hand::flush () const {
	map<char,Cards>::const_iterator it;
	for (it = suitsToCards.begin(); it != suitsToCards.end(); it++) {
		Cards cardsWithThisSuit = it->second;
		if (cardsWithThisSuit.size() == 5) {
			return true;
		}
	}
	return false;
}

vector<string> Hand::createRankNameVector () {
	vector<string> rankNameVector;
	rankNameVector.push_back("No hand");
	rankNameVector.push_back("One pair");
	rankNameVector.push_back("Two pairs");
	rankNameVector.push_back("Three of a kind");
	rankNameVector.push_back("Straight");
	rankNameVector.push_back("Flush");
	rankNameVector.push_back("Full house");
	rankNameVector.push_back("Four of a kind");
	rankNameVector.push_back("Straight flush");
	return rankNameVector;
}

ostream & operator<< (ostream & out, Hand const & hand) {
	string rankName = Hand::rankToString[hand.rank];
	out << rankName << " ";
	Cards const & cards = hand.cards;
	out << cards;
	return out;
}
