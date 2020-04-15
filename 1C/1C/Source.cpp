#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

struct NumberNode {		//Node struct; contains current character and pointers to next nodes;
public:
	//constructors TODO: add other constructors
	NumberNode() :
		_character(0), _is_end_of_number(false), _next_node(10, nullptr), _previous_node(nullptr) {  }
	NumberNode(char character, NumberNode* previous) :
		_character(character), _is_end_of_number(false), _next_node(10, nullptr), _previous_node(previous) {}
	NumberNode(char character, const std::string& surname, NumberNode* previous) :
		_character(character), _is_end_of_number(true), _surname(surname), _next_node(10, nullptr), _previous_node(previous) {}

	//There is no destructor here. However, it should be added later (just in case)


	//getters
	char get_character() const { return _character; };
	NumberNode* get_next_node(char character) const { return _next_node[character - '0']; };
	NumberNode* get_previous_node() const { return _previous_node; };
	std::string get_surname() const { return _surname; };
	bool is_leaf() const { return _is_end_of_number; };


	//setters
	void add_node(char character);
	void add_node(char character, const std::string& surname);
private:
	char _character;
	bool _is_end_of_number;
	std::string _surname;
	std::vector<NumberNode*> _next_node;
	NumberNode* _previous_node;
};

void NumberNode::add_node(char character) {
	if (_next_node[character - '0'] == nullptr)
		_next_node[character - '0'] = new NumberNode(character, this);	//TODO smart pointers
}

void NumberNode::add_node(char character, const std::string& surname) {
	if (_next_node[character - '0'] == nullptr)
		_next_node[character - '0'] = new NumberNode(character, surname, this);	//TODO smart pointers
}







class NumberTree {	//Main tree class; contains root node and main functions
public:
	//constructors	TODO add copy, move and r value constructor
	NumberTree() : _root() {}


	//destructor
	~NumberTree();	//Needed because of usage of raw pointers to dynamic memory


	//getters	TODO make it const (problem is BFS though)
	std::vector<std::string> get_surnames_by_suffix(const std::string& suffix);
	std::string get_number(const std::string& surname);


	//setters
	void add_contact(const std::string& number, const std::string& surname);

private:
	std::unordered_map<std::string, std::string> _name_x_number;
	template <typename Func>
	void universal_bfs(NumberNode* start_node, Func process);	//template BFS for service needs (i.e. for searching) TODO add const version
	NumberNode _root;
};

void NumberTree::add_contact(const std::string& number, const std::string& surname) {	//Adds contact; Checks basic requierments
	if (number.size() < 1) {
		std::cerr << "Empty Number. No actions done." << std::endl;
		return;
	}
	if (surname.size() < 1) {
		std::cerr << "Empty Surname. No actions done." << std::endl;
		return;
	}
	_name_x_number.insert({ surname, number });
	NumberNode* current_node = &_root;
	for (int i = 0; i < number.size() - 1; i++) {
		current_node->add_node(number[i]);
		current_node = current_node->get_next_node(number[i]);
	}
	current_node->add_node(number[number.size() - 1], surname);
}

std::vector<std::string> NumberTree::get_surnames_by_suffix(const std::string& suffix) {	//uses BFS for searching after last digit
	NumberNode* current_node = &_root;
	for (int i = 0; i < suffix.size(); i++) {
		if (current_node->get_next_node(suffix[i]) == nullptr)
			return {};
		current_node = current_node->get_next_node(suffix[i]);
	}

	std::vector<std::string> suitable_surnames;
	auto process_node = [&suitable_surnames](NumberNode* node) -> void {	//lambda that is used in BFS
		if (node->is_leaf())
			suitable_surnames.push_back(node->get_surname());
	};

	universal_bfs(current_node, process_node);
	return suitable_surnames;
}

std::string NumberTree::get_number(const std::string& surname) {
	std::string number;
	auto process_node = [surname, &number](NumberNode* node) -> void {	//lambda that is used in BFS
		if (node->is_leaf() && node->get_surname() == surname) {
			while (node->get_previous_node() != nullptr) {
				number += node->get_character();
				node = node->get_previous_node();
			}
		}
	};
	universal_bfs(&_root, process_node);
	std::reverse(number.begin(), number.end());
	return number;
}

template <typename Func>
void NumberTree::universal_bfs(NumberNode* start_node, Func process) {	//Template BFS	TODO work on process function call order
	std::queue<NumberNode*> next_nodes;
	next_nodes.push(start_node);
	NumberNode* current_node;
	while (!next_nodes.empty()) {
		current_node = next_nodes.front();
		next_nodes.pop();
		for (int i = 0; i < 10; i++) {
			char character = '0' + i;
			if (current_node->get_next_node(character) != nullptr)
				next_nodes.push(current_node->get_next_node(character));
		}
		process(current_node);
	}
}

NumberTree::~NumberTree() {	//Destroys every node
	NumberNode* root_node = &_root;

	auto destroy_node = [&root_node](NumberNode* node) -> void {	//lambda that is used in BFS
		if (node != root_node) {
			delete node;
		}
	};

	universal_bfs(&_root, destroy_node);
}


int main() {
	system("pause");
}