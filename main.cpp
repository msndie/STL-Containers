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
#include <list>

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

template <typename T>
class foo {
public:
	typedef T	value_type;

	foo(void) : value(), _verbose(false) { };
	foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
	foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
	~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
	void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
	void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
	foo &operator=(value_type src) { this->value = src; return *this; };
	foo &operator=(foo const &src) {
		if (this->_verbose || src._verbose)
			std::cout << "foo::operator=(foo) CALLED" << std::endl;
		this->value = src.value;
		return *this;
	};
	value_type	getValue(void) const { return this->value; };
	void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

	operator value_type(void) const {
		return value_type(this->value);
	}
private:
	value_type	value;
	bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

#define _ratio 1
#define _map ft::map
#define _set ft::set
#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
#define _pair TESTED_NAMESPACE::pair
#define T1 char
#define T2 int
typedef _pair<const T1, T2> T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator ft_iterator;
typedef TESTED_NAMESPACE::map<T1, T2>::const_iterator ft_const_iterator;
static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true)
{
	std::cout << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		std::cout << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('a' + i, (i + 1) * 7));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<T1, T2>::iterator it_ = mp.begin();
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator it(it_), ite;
	printSize(mp);

	std::cout << (it_ == it.base()) << std::endl;
	std::cout << (it_ == dec(it, 3).base()) << std::endl;

	printPair(it.base());
	printPair(inc(it.base(), 1));

	std::cout << "TEST OFFSET" << std::endl;
	--it;
	printPair(it);
	printPair(it.base());

	it = mp.rbegin(); ite = mp.rend();
	int n = 0;
	while (it != ite)
	{
		++n;
		if (n == 5) {
			std::cout << "kek" << std::endl;
		}
		std::cout << "[rev] " << printPair(it++, false) << std::endl;
	}

	return (0);
}
