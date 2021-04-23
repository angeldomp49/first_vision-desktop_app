#include <iostream>
#include"GContainer.cpp"

int main(void){
	int x[10] = { 1 };
	int* y = x;
	y[1] = 10;
	std::cout << "el contenido en y[0] es: " << y[0] << std::endl;
	std::cout << "el contenido en y[1] es: " << y[1] << std::endl;

	GContainer<int>* intContainer = new GContainer<int>();
	intContainer->push(11);
	intContainer->push(22);

}
