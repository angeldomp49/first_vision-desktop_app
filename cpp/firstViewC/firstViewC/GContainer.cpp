#include<iostream>

template<typename G> class GContainer {
public:
	unsigned int size;
	G* items[];

	GContainer(unsigned int size, G* items) {
		this->size = size;
		this->items = items;
	}

	GContainer(){
		this->size = 0;
		G items[100];
		*this->items = items;
	}

	void push(G item) {
		*(this->items) = &item;
		std::cout << "el valor es: " << *(this->items) << std::endl;
		this->size++;
	}

	void flush() {
		this->items = nullptr;
	}

	G first() {
		return this->items[0];
	}
};
