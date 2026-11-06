// Alvaro Garcia Serrano
#include "poker_manager.h"
#include <godot_cpp/classes/engine.hpp>

void PokerManager::initialize_deck(){
	const int suits = (int)PokerCard::Suit::COUNT;
	const int ranks = (int)PokerCard::Rank::COUNT - (int)PokerCard::Rank::TWO;

	poker_deck.clear();
	poker_deck.resize(suits * ranks);

	int idx = 0;
	for (int s = 0; s < suits; s++) {
		for (int r = (int)PokerCard::Rank::TWO; r < (int)PokerCard::Rank::COUNT; r++) {
			poker_deck.set(idx, PokerCard((PokerCard::Rank)r, (PokerCard::Suit)s));
			idx++;
		}
	}
}

void PokerManager::_ready() {
	//UtilityFunctions::print("PokerManager listo AAAAA");
	UtilityFunctions::print("PokerManager listo BBBB");
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	initialize_deck();
	UtilityFunctions::print("Cartas en la baraja: ", (int)poker_deck.size());


	/*for (int i = 0; i < poker_deck.size(); i++)
	{
		String name = poker_deck[i].name;

		printf("%s", name);
	}*/

}
