// Alvaro Garcia Serrano
#ifndef PKP_CARD_H
#define PKP_CARD_H

//#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class Card : public Resource {
	GDCLASS(Card, Resource);
public:
	//Card() {}

	uint64_t PPK_id;
	StringName PPK_name;
	StringName PPK_desc;

protected:
	static void _bind_methods() {

	}

};



#endif // !PKP_CARD_H
