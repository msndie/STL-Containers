#include <iostream>
//#include <vector>
#include "Vector.hpp"

class Test {
public:
	int x;
	explicit Test(int x) : x(x) {}
	~Test() {
		std::cout << "destructor" << std::endl;
	}
};

int main() {
	ft::vector<Test> v;

	v.push_back(Test(1));
	v.push_back(Test(2));
	v.push_back(Test(3));
	v.push_back(Test(4));
	v.push_back(Test(5));
	v.push_back(Test(6));
	ft::vector<Test>::iterator it = v.begin();
//	it += 3;
//	v.insert(it, Test(5));
//	it = v.begin();
//	ft::vector<int>::iterator it = v.begin();
//	while (it != v.end()) {
//		std::cout << it->x << std::endl;
//		++it;
//	}
	std::cout << "capacity " << v.capacity() << std::endl;
	std::cout << "size " << v.size() << std::endl;
	while (it != v.end()) {
		std::cout << it->x << std::endl;
		++it;
	}
	std::cout << "insert called" << std::endl;
	v.insert(it - 3, Test(10));
	std::cout << "capacity " << v.capacity() << std::endl;
	std::cout << "size " << v.size() << std::endl;
	it = v.begin();
	while (it != v.end()) {
		std::cout << it->x << std::endl;
		++it;
	}
//
//	ft::vector<int> v_mine(v);
//	std::cout << v.capacity() << std::endl;
//	std::cout << v.size() << std::endl;
//	for (int i = 0; i < v.size(); ++i) {
//		std::cout << v[i].x << std::endl;
//	}
//	std::cout << "assign called" << std::endl;
//	v.assign(3, Test(0));
//	std::cout << v.capacity() << std::endl;
//	std::cout << v.size() << std::endl;
//	for (int i = 0; i < v.size(); ++i) {
//		std::cout << v[i].x << std::endl;
//	}
//	return 0;
}
