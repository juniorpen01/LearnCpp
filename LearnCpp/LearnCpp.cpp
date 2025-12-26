#include <memory>
#include <vector>
#include <array>
#include <string_view>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <ranges>

#pragma warning(push)
#pragma warning(disable:4189) // unused variables

// put classes above main to not deal with forward decl typa shi
class Widget { // apparently just pascalcase class names
private: // apparently private before public
	std::unique_ptr<std::array<int, 1'000'000>> data; // std array has size and safer; what cpp uses 's instead of _s
public:
	Widget() : data(std::make_unique<std::array<int, 1'000'000>>()) {} // btw for some reason u still have to explicitly type the generic for make unique

	// ok so i have to explicitly delete some constructors
	Widget(const Widget&) = delete;
	Widget& operator=(const Widget&) = delete;
}; // ok so im an idiot and just found out that im supposed to use a size arg to determine size of the data, so therefore i should be using vector, but i already wrote a lot so why not

// NOTE: revelation 2: memory leak just basically when a process takes up memory (perhaps more accurately so-called "resources"?) up until it exits, leaving it unavaiable to other processes; perhaps to add it's when a "resource" truly not needed anymore is not released

class Widget2 { // let's implement with vector this time
private:
	std::vector<int> data;
public:
	// let's do size_t instead
	Widget2(size_t size) // btw i dont wanna do const int in func params for to the eyes of the end user it truly doesnt matter; i believe it matters for references tho using my intuition
	{
		data.reserve(size); // reserve actually does preallocation
	} // data(size) means allocating all zeroed out of that size, not preallocation
};


int main() {
	// resources and smart ptrs

	int* a = new int; // like malloc but ye heap allocation of sizeof int; WARN: apparently bad practice should both fully initialize and even better use smart ptrs
	*a = 2; // set value at that addr
	delete a; // very manual i dont even think there's a standard defer

	// NOTE: holy crap ive come to the revelation that raii literally is a very general term; even heap memory is considered a resource just like file handles

	auto b = std::make_unique<int>(3); // unique ptr cool cuz raii; make unique cuz ergonomic; auto cuz feels too long and redunant and stdlib fn; also apparently if throws actually deallocs
	std::unique_ptr<int> c(new int(4)); // takes a ptr; WARN: dont do this cuz less ergonomic; also msvc has weird ahh error messages, it talks about a deleted copy constructor, like what?? it's deleted bruh but apparently has smth to do with overload resolution

	// NOTE: ok let's forget the semantics of other languages and accept the way u do in cpp cuz too mental

	// btw there shared and weak ptrs

	// ok this time let's give more sensical names, otherwise if so primitive

	Widget widget;
	Widget2 widget2(1'000'000);

	// ok so we'll be defaulting to brace initialization from now on

	// string and string view also allow for some cool methods

	std::string_view sv{ "this is sv" }; // apparently just a fat ptr
	std::wstring_view wsv{ L"what is wide" }; // for wide characters

	std::string s{ "hello " };
	s.append(sv);

	std::wstring ws{ L"but " };
	ws.append(wsv);

	std::vector<std::string> apples{}; // also good the know that primitives aint have default constructors unlike these; but yes let's still use braces
	apples.push_back("granny smith");

	std::map<std::string, std::string> apple_color{}; // i dont think this is a hashmap, more like an rbtree or smth
	apple_color["Granny Smith"] = "Green"; // overwrites if already exists
	auto result1 = apple_color.insert({ "Gala","Red" }); // doesnt overwrite; also apparently returns iterator and bool; NOTE: idk what a "gala" even is just a vague memory
	auto result2 = apple_color.emplace("Fuji", "Red"); // constructs value in place; apparently if u already have in object do insert, otherwise if literal emplace

	// there are also unordered map, which is a hashmap, set, multimap, and multiset

	// as ive been told, when talking to c style apis, use stl containers, not c arrays

	std::for_each(apple_color.begin(), apple_color.end(), [](auto& pair) { // takes a begin and end
		auto& [k, v] = pair;
		std::cerr << k << v << '\n';
		});

	//for (std::vector<std::string>::iterator it = apples.begin(), int i = 0; it != apples.end(); ++i, ++it) {
	//}

	std::map<int, std::string> not_array{};
	for (auto [i, it] = std::pair{ 0,apples.begin() }; it != apples.end(); ++i, ++it) {
		not_array[i] = *it;
	} // idk men just feels weird i should just use ranges at this point, maybe i get to hack better

	//std::transform(apples.begin(), apples.end(), );

	auto it = std::views::iota(0, static_cast<int>(apples.size())) | std::views::transform([&](int i) {return std::pair{ static_cast<size_t>(i), apples[static_cast<size_t>(i)] }; });
	std::map<size_t, std::string> not_array2{ it.begin(),it.end() }; // ranges
}

#pragma warning(pop)