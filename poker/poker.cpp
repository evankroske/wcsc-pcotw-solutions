#include "poker.h"

const std::string Card::VALUE("23456789TJQKA");

Card::Card ():
	num(0),
	suit(0) {}

Card::Card (char num, char suit):
	num(num),
	suit(suit) {}

bool Card::operator< (Card const & other) {
	return val() < other.val();
}

Card Card::succ () {
	if (num == 'A') {
		throw "No successor";
	}
	return Card(VALUE[val()+1], suit);
}

bool Card::operator== (Card const & other) {
	return num == other.num;
}

int Card::val () const {
	return VALUE.find(num);
}

std::ostream & operator<< (std::ostream & out, Card const & card) {
	out << card.num << card.suit;
	return out;
}

std::ostream & operator<< (std::ostream & out, Cards const & cards) {
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

Hand::Hand ():
	cards(),
	suitsToCards(),
	numsToCards() {}

void Hand::add (Card const & card) {
	cards.push_back(card);
	cards.sort();
	numsToCards[card.num].push_back(card);
	suitsToCards[card.suit].push_back(card);
}

Cards Hand::straight () const {
	bool isStraight = true;
	Card lastCard;
	Cards::const_iterator it;
	for (it = cards.begin(); isStraight && it != cards.end(); it++) {
		Card card = *it;
		if (it != cards.begin()) {
			try {
				isStraight = (lastCard.succ() == card);
			} catch (char const * msg) {
				isStraight = false;
			}
		}
		lastCard = *it;
	}
	Cards deciders;
	if (isStraight) {
		deciders.push_back(lastCard);
	}
	return deciders;
}

Cards Hand::flush () const {
	map<char,Cards>::const_iterator it;
	for (it = suitsToCards.begin(); it != suitsToCards.end(); it++) {
		Cards cardsWithThisSuit = it->second;
		if (cardsWithThisSuit.size() == 5) {
			Cards deciders = cards;
			deciders.reverse();
			return deciders;
		}
	}
	return Cards();
}

std::ostream & operator<< (std::ostream & out, Hand const & hand) {
	std::list<Card> const & cards = hand.cards;
	out << cards;
	return out;
}
