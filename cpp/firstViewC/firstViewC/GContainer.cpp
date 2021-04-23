#include<iostream>

template<typename G> class GContainer {
public:
	unsigned int size;
	G *items;

	GContainer(unsigned int size, G* items) {
		this->size = size;
		this->items = items;
	}

	GContainer(){
		this->size = 0;
		this->items = (G*)malloc(101);
	}

	void push(G item) {
		G* newPointer = (G*)malloc(this->size+1);

		if (0 == this->size) {
			this->items = newPointer;
		}
		else {
			for (unsigned int i = 0; i <= this->size; i++) {
				*(newPointer + i) = *(this->items + i);
			}
			this->items = newPointer;
		}

		*(this->items + this->size) = item;
		std::cout << "el valor en: " << this->size << " es: " << *(this->items + this->size) << std::endl;
		this->size++;
	}

	void flush() {
		this->items = nullptr;
	}

	G first() {
		return this->items[0];
	}
};
