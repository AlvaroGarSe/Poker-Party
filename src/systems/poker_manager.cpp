// Alvaro Garcia Serrano
#include "poker_manager.h"

void PokerManager::initialize_deck()
{
	poker_deck.clear();
	poker_deck.resize((int)PokerCard::Rank::COUNT * (int)PokerCard::Suit::COUNT);

	for (int i = (int) PokerCard::Rank::TWO; i < (int) PokerCard::Rank::COUNT; i++)
	{
		for (int j = 0; j < (int) PokerCard::Suit::COUNT; j++)
		{
			PokerCard card = PokerCard((PokerCard::Rank) j, (PokerCard::Suit) i);
			poker_deck.append(card);
		}
	}
}
