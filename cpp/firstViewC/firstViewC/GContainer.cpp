
#ifndef GCONTAINER_CPP

#define GCONTAINER_CPP

#include<iostream>

template<typename G> class GContainer {
public:
	unsigned int size;
	G *items;

	GContainer(G items[], unsigned int size) {
		this->size = 0;
		this->items = this->reserve(size);
		this->push( items, size );
	}

	GContainer( int defaultSize ){
		this->size = 0;
		this->items = this->reserve(defaultSize);
	}

	void push(G item) {

		G* newPointer = this->reserve(this->size+1);

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
		G* newPointer = this->reserve(newSize);

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
		free(this->items);
	}

	G first() {
		return this->items[0];
	}

	G get(unsigned int index) {
		return this->items[index];
	}

	G* reserve(unsigned int size) {
		return (G*)malloc(size*sizeof(G));
	}

	unsigned int spaceUsed() {
		return this->size * sizeof(this->items);
	}
};


#endif // !GCONTAINER_CPP
