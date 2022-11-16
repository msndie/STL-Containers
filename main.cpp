#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Stack.hpp"
#include "Map.hpp"
#include <stack>
#include <map>
#include <set>

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
//	Test() : x() {}
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

template <typename T>
std::vector<int> test3(std::vector<T> vector = std::vector<T>()) {
	std::vector<int> v;
	for (int i = 0; i < 9900 * 10000; ++i)
		vector.push_back(i);
	v.push_back(*(vector.erase(vector.begin() + 8 * 10000)));
	v.push_back(*(vector.begin() + 82 * 10000));
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}

template <typename T>
std::vector<int> test4(ft::vector<T> vector = ft::vector<T>()) {
	std::vector<int> v;
	for (int i = 0; i < 9900 * 10000; ++i)
		vector.push_back(i);
	v.push_back(*(vector.erase(vector.begin() + 8 * 10000)));
	v.push_back(*(vector.begin() + 82 * 10000));
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}

template <typename T>
std::vector<int> test5(std::vector<T> vector = std::vector<T>()) {
	std::vector<int> v;
	vector.assign(9900 * 10000, 1);
	vector.resize(5000 * 10000);
	vector.reserve(5000 * 10000);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	vector.resize(7000 * 10000);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	vector.resize(15300 * 10000, T());
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	v.push_back(vector[65]);
	return v;
}

template <typename T>
std::vector<int> test6(ft::vector<T> vector = ft::vector<T>()) {
	std::vector<int> v;
	vector.assign(9900 * 10000, 1);
	vector.resize(5000 * 10000);
	vector.reserve(5000 * 10000);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	vector.resize(7000 * 10000);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	vector.resize(15300 * 10000, T());
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	v.push_back(vector[65]);
	return v;
}

template <typename T>
std::vector<int> test7(std::vector<T> vector = std::vector<T>()) {
	std::vector<int> v;
	int _ratio = 10000;
	vector.assign(1100 * _ratio, 11);
	std::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	long *adr1 = reinterpret_cast<long *>(&vector);
	long *adr2 = reinterpret_cast<long *>(&tmp);
	vector.swap(tmp);
	if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
		v.push_back(1);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	vector.swap(tmp3);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	std::swap(vector, tmp2);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	std::swap(vector, tmp4);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}

template <typename T>
std::vector<int> test8(ft::vector<T> vector = ft::vector<T>()) {
	std::vector<int> v;
	int _ratio = 10000;
	vector.assign(1100 * _ratio, 11);
	ft::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	long *adr1 = reinterpret_cast<long *>(&vector);
	long *adr2 = reinterpret_cast<long *>(&tmp);
	vector.swap(tmp);
	if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
		v.push_back(1);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	vector.swap(tmp3);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	std::swap(vector, tmp2);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	std::swap(vector, tmp4);
	v.push_back(vector[2]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}

int main() {
	Test test(5);
	ft::map<int, Test> map;
	ft::stack<Test> s((ft::vector<Test>()));

	std::cout << s.size() << std::endl;
	map.insert(ft::make_pair(10, test));
}

//int main() {
//	std::vector<int> v1 = test7<int>();
//	std::cout << "1--------------------1" << std::endl;
//	std::vector<int> v2 = test8<int>();
//
//	std::cout << (v1 == v2) << std::endl;
//}

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
//	ft::vector<int> v;
//	v.assign(10, 1);
//	ft::vector<int>::iterator it = v.end();
//
//	it += 5;
//	v.erase(it);
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
//	it += 3;
//	v.insert(it, v2.begin(), v2.end());
//	it = v.begin();
//	ft::vector<int>::iterator it = v.begin();
//	while (it != v.end()) {
//		std::cout << it->x << std::endl;
//		++it;
//	}
//
//	std::cout << "capacity " << v.capacity() << std::endl;
//	std::cout << "size " << v.size() << std::endl;
//	while (it != v.end()) {
//		std::cout << it->x << std::endl;
//		++it;
//	}
//	std::cout << "insert called" << std::endl;
//	v.insert(it - 3, Test(10));
//	std::cout << "capacity " << v.capacity() << std::endl;
//	std::cout << "size " << v.size() << std::endl;
//	it = v.begin();
//	while (it != v.end()) {
//		std::cout << it->x << std::endl;
//		++it;
//	}

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
//}
