#include "poker.h"

const std::string Card::VALUE("23456789TJQKA");

Card::Card (char num, char suit):
	num(num),
	suit(suit) {}

bool Card::operator< (Card const & other) {
	return val() < other.val();
}

int Card::val () const {
	return VALUE.find(num);
}

std::ostream & operator<< (std::ostream & out, Card const & card) {
	out << card.num << card.suit;
	return out;
}

std::ostream & operator<< (std::ostream & out, Hand const & hand) {
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
