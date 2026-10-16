// Alvaro Garcia Serrano
#ifndef PPK_POKER_CARD
#define PPK_POKER_CARD

#include "../PPK_resource.h"

using namespace godot;

class PokerCard {

public:
    enum class Suit : int {
        SPADE,
        CLUB,
        HEART,
        DIAMOND,
        COUNT
    };

    enum class Rank : int {
        TWO = 2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,
		COUNT
	};


    Suit suit;
    Rank rank;

    uint64_t id;
    StringName name;

    PokerCard(Rank rank, Suit suit);
	PokerCard() {}

};

#endif // !PPK_POKER_CARD
