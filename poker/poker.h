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
	Card succ ();
	int cmp(Card const & other) const;
	bool operator< (Card const & other);
	bool operator== (Card const & other);
	bool operator> (Card const & other);
private:
	static const string VALUE;

	int val () const;
	friend ostream & operator<< (ostream & out, Card const & card);
};

typedef list<Card> Cards;
ostream & operator<< (ostream & out, Cards const & cards);

class Hand {
public:
	enum Rank {NoHand, OnePair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush};

	Hand (Cards cards_);
	int cmp (Hand const & other) const;
	bool operator< (Hand const & other) const;
	bool operator> (Hand const & other) const;
	bool operator== (Hand const & other) const;
private:
	Cards cards;
	Cards deciders;
	map<char,Cards> suitsToCards;
	map<char,Cards> numsToCards;
	bool straight;
	Rank rank;
	static const map<Rank,string> rankToString;

	bool straightFlush () const;
	bool flush () const;
	static map<Rank,string> createMap ();

	friend ostream & operator<< (ostream & out, Hand const & hand);
};

typedef pair<Hand,Hand> Round;
