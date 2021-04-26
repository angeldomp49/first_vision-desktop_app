#include <iostream>
#include"GContainer.cpp"

int main(void){

	GContainer<int>* intContainer = new GContainer<int>( 100 );
	intContainer->push(11);
	intContainer->push(22);

	std::cout << "El contenido es: " << std::endl;
	intContainer->print();

	std::cout << "start with array:" << std::endl;

	int items[] = {
		121,
		122
	};

	intContainer->push(items, 2);

	std::cout << "El contenido es: " << std::endl;
	intContainer->print();
}
