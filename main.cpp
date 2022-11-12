#include <iostream>
#include <vector>
#include "Vector.hpp"

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
	explicit Test(int x) : x(x) {std::cout << "constructor" << std::endl;}
	~Test() {
		std::cout << "destructor" << std::endl;
	}
};

template <typename T>
std::vector<int> test1(std::vector<T> vector= std::vector<T>()) {
	std::vector<int> v;
	std::vector<int> tmp;
	tmp.assign(2600 * 10000, 1);
	vector.assign(4200 * 10000, 1);
	vector.insert(vector.end() - 1000 * 10000, tmp.begin(), tmp.end());
	v.push_back(vector[3]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());

	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	std::vector<A> vv;
	std::vector<B*> v1;

	v1.push_back(&(*k2));
	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
	catch (...) {
		v.push_back(vv.size());
		v.push_back(vv.capacity());
	}

	return v;
}

template <typename T>
std::vector<int> test2(ft::vector<T> vector = ft::vector<T>()) {
	std::vector<int> v;
	ft::vector<int> tmp;
	tmp.assign(2600 * 10000, 1);
	vector.assign(4200 * 10000, 1);
	vector.insert(vector.end() - 1000 * 10000, tmp.begin(), tmp.end());
	v.push_back(vector[3]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());

	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	ft::vector<A> vv;
	ft::vector<B*> v1;

	v1.push_back(&(*k2));
	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
	catch (...) {
		v.push_back(vv.size());
		v.push_back(vv.capacity());
	}

	return v;
}

int main() {
	std::vector<int> v1 = test1<int>();
	std::cout << "--------------------" << std::endl;
	std::vector<int> v2 = test2<int>();

	std::cout << (v1 == v2) << std::endl;
}

//int main() {
//	std::vector<int> v_std;
//	std::vector<int> v_ft;
//	std::vector<int> v_std_tmp;
//	std::vector<int> v_ft_tmp;
//	ft::vector<int> ft;
//	std::vector<int> std;
//
//	v_std_tmp.assign(2600 * 10000, 1);
//	std.assign(4200 * 10000, 7);
//	std.insert(std.begin(), v_std_tmp.begin(), v_std_tmp.end());
//	for (ssize_t i = 0; i < v_std_tmp.size(); ++i) {
//		v_std.push_back(std[i]);
//	}
//	v_std.push_back(std.size());
//	v_std.push_back(std.capacity());
//
//	v_ft_tmp.assign(2600 * 10000, 1);
//	ft.assign(4200 * 10000, 7);
//	ft.insert(ft.begin(), v_ft_tmp.begin(), v_ft_tmp.end());
//	for (ssize_t i = 0; i < v_ft_tmp.size(); ++i) {
//		v_ft.push_back(std[i]);
//	}
//	v_ft.push_back(ft.size());
//	v_ft.push_back(ft.capacity());
//
//	std::cout << (v_std == v_ft) << std::endl;
//}

//int main() {
//	std::vector<int> v_std;
//	std::vector<int> v_ft;
//	ft::vector<int> ft;
//	std::vector<int> std;
//
//	ft.assign(2600 * 10000, 1);
//	v_ft.push_back(*(ft.insert(ft.end() - 800 * 10000, 44)));
//	v_ft.push_back(ft.size());
//	v_ft.push_back(ft.capacity());
//
//	std.assign(2600 * 10000, 1);
//	v_std.push_back(*(std.insert(std.end() - 800 * 10000, 44)));
//	v_std.push_back(std.size());
//	v_std.push_back(std.capacity());
//
//	std::cout << (v_std == v_ft) << std::endl;
//}

//int main() {
//	std::vector<int> v_std;
//	std::vector<int> v_ft;
//	ft::vector<int> ft;
//	std::vector<int> std;
//
//	ft.assign(1000, 1);
//	ft.insert(ft.end() - 50, 4200 * 10000 , 2);
//	v_ft.push_back(ft[2121]);
//	v_ft.push_back(ft.size());
//	v_ft.push_back(ft.capacity());
//
//	std.assign(1000, 1);
//	std.insert(std.end() - 50, 4200 * 10000 , 2);
//	v_std.push_back(std[2121]);
//	v_std.push_back(std.size());
//	v_std.push_back(std.capacity());
//
//	std::cout << (v_std == v_ft) << std::endl;
//}

//int main() {
//	ft::vector<Test> v;
//	ft::vector<Test> v2;
//
//	v2.push_back(Test(11));
//	v2.push_back(Test(21));
//	v2.push_back(Test(31));
//	v2.push_back(Test(41));
//	v2.push_back(Test(51));
//	v2.push_back(Test(61));
//
//	v.push_back(Test(1));
//	v.push_back(Test(2));
//	v.push_back(Test(3));
//	v.push_back(Test(4));
//	v.push_back(Test(5));
//	v.push_back(Test(6));
//	ft::vector<Test>::iterator it = v.end();
////	it += 3;
//	v.insert(it, v2.begin(), v2.end());
//	it = v.begin();
////	ft::vector<int>::iterator it = v.begin();
//	while (it != v.end()) {
//		std::cout << it->x << std::endl;
//		++it;
//	}
//
//	std::cout << "capacity " << v.capacity() << std::endl;
//	std::cout << "size " << v.size() << std::endl;
////	while (it != v.end()) {
////		std::cout << it->x << std::endl;
////		++it;
////	}
////	std::cout << "insert called" << std::endl;
////	v.insert(it - 3, Test(10));
////	std::cout << "capacity " << v.capacity() << std::endl;
////	std::cout << "size " << v.size() << std::endl;
////	it = v.begin();
////	while (it != v.end()) {
////		std::cout << it->x << std::endl;
////		++it;
////	}
//
////
////	ft::vector<int> v_mine(v);
////	std::cout << v.capacity() << std::endl;
////	std::cout << v.size() << std::endl;
////	for (int i = 0; i < v.size(); ++i) {
////		std::cout << v[i].x << std::endl;
////	}
////	std::cout << "assign called" << std::endl;
////	v.assign(3, Test(0));
////	std::cout << v.capacity() << std::endl;
////	std::cout << v.size() << std::endl;
////	for (int i = 0; i < v.size(); ++i) {
////		std::cout << v[i].x << std::endl;
////	}
////	return 0;
//}
