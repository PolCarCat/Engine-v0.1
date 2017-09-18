#ifndef __Utilities__
#define __Utilities__
#include <stdlib.h>

typedef unsigned short usint;

template <class TYPE>
class DynamicList {
private:

	struct Item {
		TYPE* _pointer = nullptr;
		Item* _prev = nullptr, *_next = nullptr;
	};

	usint _array_length = 0;
	Item* _first = nullptr;

	Item& get(const usint pos) {
		Item* current = _first;
		for (usint i = 0; i < pos && current != nullptr; i++) {
			current = current->_next;
		}
		if (current == nullptr) exit(-1);
		return *current;
	}

	Item& getLast() {
		Item* current = _first;
		while (current != nullptr && current->_next != nullptr) {
			current = current->_next;
		}
		return *current;
	}

	Item& getFirst() {
		if (_first == nullptr) exit(-1);
		return *_first;
	}

public:
	TYPE& operator [](const usint position) {
		return *get(position)._pointer;
	}

	TYPE& at(const usint position) {
		return *get(position)._pointer;
	}

	void push(TYPE object) {
		Item *current = &getLast();
		if (current == nullptr) {
			_first = new Item;
			_first->_pointer = new TYPE(object);
		}
		else {
			current->_next = new Item;
			current->_next->_pointer = new TYPE(object);
			current->_next->_prev = current;
		}
		_array_length++;
	}

	TYPE& pop() {
		Item *current = &getLast();
		current->_prev->_next = nullptr;
		_array_length--;
		return current;
	}

	DynamicList() {

	}

	/*DynamicArray(usint length) {
		_array_length = length;
		for (usint i = 0; i < _array_length; i++) {
			_array[i] = nullptr;
		}
	}*/

	~DynamicList() {

	}
};

#endif
