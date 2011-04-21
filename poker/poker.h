#include <iostream>
#include <string>
#include <list>
#include <map>

using std::ostream;
using std::list;
using std::map;
using std::pair;
using std::string;

class Card {
public:
	char num, suit;

	Card ();
	Card (char num, char suit);
	bool operator< (Card const & other);
	Card succ ();
	bool operator== (Card const & other);
private:
	static const string VALUE;

	int val () const;
	friend ostream & operator<< (ostream & out, Card const & card);
};

typedef list<Card> Cards;
ostream & operator<< (ostream & out, Cards const & cards);

class Hand {
public:
	enum Value {NoHand, OnePair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush};

	Hand ();
	void add(Card const & card);
	Cards straight () const;
	Cards flush () const;
private:
	Cards cards;
	map<char,Cards> suitsToCards;
	map<char,Cards> numsToCards;

	friend ostream & operator<< (ostream & out, Hand const & hand);
};

typedef pair<Hand,Hand> Round;
