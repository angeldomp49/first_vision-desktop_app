
#ifndef GCONTAINER_CPP

#define GCONTAINER_CPP

#include<iostream>

template<typename G> class GContainer {
public:
	unsigned int size;
	G *items;

	GContainer(G items[], unsigned int size) {
		this->size = 0;
		this->items = (G*)malloc(size* sizeof(G));
		this->push( items, size );
	}

	GContainer( int defaultSize ){
		this->size = 0;
		this->items = (G*)malloc(defaultSize* sizeof(G));
	}

	void push(G item) {
		G* newPointer = (G*)malloc((this->size+1)* sizeof(G));

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
		G* newPointer = (G*)malloc(newSize*sizeof(G));

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

	G get(unsigned int index) {
		return *(this->items + index);
	}
};


#endif // !GCONTAINER_CPP
