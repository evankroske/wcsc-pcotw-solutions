#include <iostream>
#include <string>
#include <list>
#include <map>

class Card {
public:
	Card (char num, char suit);

	bool operator< (Card const & other);
private:
	static const std::string VALUE;
	char num, suit;

	int val () const;
	friend std::ostream & operator<< (std::ostream & out, Card const & card);
};

typedef std::list<Card> Hand;
typedef std::pair<Hand,Hand> Round;
/*
class HandType {
public:
	void add};

class Flush: public HandType {
public:
	void add(Card const &) {
};
*/
