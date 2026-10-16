#ifndef PPK_RESOURCE
#define PPK_RESOURCE

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class PPK_Resouce : public Resource {
	GDCLASS(PPK_Resouce, Resource);
public:
	//Card() {}

	uint64_t PPK_id;
	StringName PPK_name;
	StringName PPK_desc;

protected:
	static void _bind_methods() {

	}

};


#endif // !PPK_RESOURCE
