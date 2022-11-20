#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Stack.hpp"
#include "Map.hpp"
#include "Set.hpp"
#include <stack>
#include <map>
#include <set>
#include <string>

#define _ratio 1
#define _map ft::map
#define _set ft::set
#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {
		std::cout << "constructor B" << std::endl;
	};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
		std::cout << "constructor B" << std::endl;
	};
	virtual ~B() {
		std::cout << "destructor B" << std::endl;
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){
		std::cout << "constructor A" << std::endl;
	};
	A(const B* ex){
		std::cout << "constructor A" << std::endl;
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		std::cout << "destructor B" << std::endl;
		delete this->l;
		this->l = nullptr;
	};
};

class Test {
public:
	int x;
	Test() : x() {}
	explicit Test(int x) : x(x) {std::cout << "constructor" << std::endl;}
	~Test() {
		std::cout << "destructor" << std::endl;
	}
};