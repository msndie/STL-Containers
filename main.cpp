#include <iostream>
//#include <vector>
#include "Vector.hpp"

int main() {
	ft::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	ft::vector<int> v_mine(v);
	std::cout << v.capacity() << std::endl;
	std::cout << v.size() << std::endl;
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << std::endl;
	}
	return 0;
}
