#include <iostream>
#include <string>
#include <list>
#include <map>

class Card {
public:
	char num, suit;

	Card ();
	Card (char num, char suit);
	bool operator< (Card const & other);
	Card succ ();
	bool operator== (Card const & other);
private:
	static const std::string VALUE;

	int val () const;
	friend std::ostream & operator<< (std::ostream & out, Card const & card);
};

typedef std::list<Card> Hand;
typedef std::pair<Hand,Hand> Round;
