// Alvaro Garcia Serrano
#include "poker_card.h"

PokerCard::PokerCard(Rank _rank, Suit _suit)
{
	suit = _suit;
	rank = _rank;

	// Will need to be hashed to be unique
	id = (uint64_t)rank * 10 + (uint64_t)suit;

	const StringName suit_names[] = { "Spade", "Club", "Heart", "Diamond" };
	const StringName rank_names[] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	name = StringName("PokerCard_" + rank_names[(int)rank - 2] + "_" + suit_names[(int) suit]);
}
