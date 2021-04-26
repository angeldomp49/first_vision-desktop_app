#include<iostream>

template<typename G> class GContainer {
public:
	unsigned int size;
	G *items;

	GContainer(unsigned int size, G* items) {
		this->size = size;
		this->items = items;
	}

	GContainer( int defaultSize ){
		this->size = 0;
		this->items = (G*)malloc(defaultSize);
	}

	void push(G item) {
		G* newPointer = (G*)malloc(this->size+1);

		if (0 == this->size) {
			this->items = newPointer;
			*(this->items) = item;
		}
		else {
			for (unsigned int i = 0; i < this->size; i++) {
				*(newPointer + i) = *(this->items + i);
			}
			this->items = newPointer;
			*(this->items + this->size) = item;
		}
		this->size++;
	}

	void push(G items[], unsigned int size) {
		unsigned int newSize = this->size + size;
		G* newPointer = (G*)malloc(newSize);

		if (0 == this->size) {
			this->items = newPointer;
			this->items = items;
		}
		else {
			for (unsigned int i = 0;i < this->size;i++ ) {
				*(newPointer + i) = *(this->items + i);
			}
			for (unsigned int i = this->size, k = 0; i <= newSize; i++, k++) {
				*(newPointer + i) = *(items + k);
			}
			this->items = newPointer;
		}
		this->size = newSize;
	}

	void flush() {
		this->items = nullptr;
	}

	G first() {
		return this->items[0];
	}

	void print() {
		std::cout << "[" << std::endl;

		for (unsigned int i = 0; i < this->size; i++) {
			std::cout << *(this->items + i) << ", ";
		}
		std::cout << std::endl << "]";
		std::cout << "with size: " << this->size<<std::endl;
	}
};
