#ifndef PKP_CARD_H
#define PKP_CARD_H

#include <godot_cpp/classes/object.hpp>

using namespace godot;

class Card : public Object {
	GDCLASS(Card, Object);
public:
	Card() {}

protected:
	static void _bind_methods() {

	}

};



#endif // !PKP_CARD_H
