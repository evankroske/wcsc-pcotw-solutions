#include "poker.h"

const std::string Card::VALUE("23456789TJQKA");

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

bool Card::operator< (Card const & other) {
	return val() < other.val();
}

bool Card::operator== (Card const & other) {
	return num == other.num;
}

bool Card::operator> (Card const & other) {
	return val() > other.val();
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

const map<Hand::Rank,string> Hand::typeName = Hand::createMap();

Hand::Hand (Cards cards_):
	cards(cards_),
	deciders(),
	suitsToCards(),
	numsToCards(),
	straight(true) {
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
	} else if (flush()) {
		rank = Flush;
		deciders = cards;
		deciders.reverse();
	} else if (straight) {
		rank = Straight;
		deciders.push_back(cards.back());
	}
}

bool Hand::operator< (Hand const & other) const {
	if (rank < other.rank) {
		return true;
	} else if (rank > other.rank) {
		return false;
	} else {
		Cards::const_iterator a;
		Cards::const_iterator b;
		for (a = cards.begin(), b = other.cards.begin();
			a != cards.end(), b != other.cards.end();
			a++, b++) {
			Card cardA = *a;
			Card cardB = *b;
			if (cardA < cardB) {
				return true;
			} else if (cardA > cardB) {
				return false;
			}
		}
		if (b != other.cards.end()) {
			return true;
		} else {
			return false;
		}
	}
}

bool Hand::straightFlush () const {
	return straight && flush();
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

map<Hand::Rank,string> Hand::createMap () {
	map<Hand::Rank,string> valueMap;
	valueMap[Hand::StraightFlush] = "Straight flush";
	valueMap[Hand::FourOfAKind] = "Four of a kind";
	valueMap[Hand::FullHouse] = "Full house";
	valueMap[Hand::Flush] = "Flush";
	valueMap[Hand::Straight] = "Straight";
	valueMap[Hand::ThreeOfAKind] = "Three of a kind";
	valueMap[Hand::TwoPair] = "Two pairs";
	valueMap[Hand::OnePair] = "One pair";
	valueMap[Hand::NoHand] = "No hand";
}

std::ostream & operator<< (std::ostream & out, Hand const & hand) {
	std::list<Card> const & cards = hand.cards;
	out << cards;
	return out;
}
