#include <iostream>
#include"GContainer.cpp"

int main(void){

	int someValues[] = {
		100,
		200,
		300,
		400
	};

	GContainer<int>* intContainer = new GContainer<int>( someValues, 4 );

	intContainer->print();
}
