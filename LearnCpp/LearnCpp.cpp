#include <memory>

#pragma warning(push)
#pragma warning(disable:4189) // unused variables

int main() {
	// resources and smart ptrs

	int* a = new int; // like malloc but ye heap allocation of sizeof int; WARN: apparently bad practice should both fully initialize and even better use smart ptrs
	*a = 2; // set value at that addr
	delete a; // very manual i dont even think there's a standard defer

	// NOTE: holy crap ive come to the revelation that raii literally is a very general term; even heap memory is considered a resource just like file handles

	auto b = std::make_unique<int>(3); // unique ptr cool cuz raii; make unique cuz ergonomic; auto cuz feels too long and redunant and stdlib fn; also apparently if throws actually deallocs
	std::unique_ptr<int> c(new int(4)); // takes a ptr; WARN: dont do this cuz less ergonomic; also msvc has weird ahh error messages, it talks about a deleted copy constructor, like what?? it's deleted bruh but apparently has smth to do with overload resolution

	// NOTE: ok let's forget the semantics of other languages and accept the way u do in cpp cuz too mental
}

#pragma warning(pop)