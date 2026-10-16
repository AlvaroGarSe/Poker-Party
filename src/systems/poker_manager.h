// Alvaro Garcia Serrano
#ifndef PPK_POKER_MANAGER
#define PPK_POKER_MANAGER

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include "poker_card.h"

using namespace godot;

class PokerManager : public Node {
    GDCLASS(PokerManager, Node);
public:

	Vector<PokerCard> poker_deck;


    void initialize_deck();

protected:
    static void _bind_methods() {

    }

};

#endif // !PPK_POKER_MANAGER
