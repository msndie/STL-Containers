#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft {

	template < class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::size_type			size_type;

	protected:
		container_type c;

	public:
		explicit stack(const Container& container = Container()) : c(container) {}
		stack(const stack& other) : c(other.c) {}
		~stack() {}
		stack& operator=(const stack& other) {
			c = other.c;
			return *this;
		}

		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }
		void push(const value_type& v) { c.push_back(v); }
		void pop() { c.pop_back(); }

		template<class T1, class C>
		friend bool operator==(const stack<T1, C>& x, const stack<T1, C>& y);
		template<class T1, class C>
		friend bool operator<(const stack<T1, C>& x, const stack<T1, C>& y);
	};

	template<class T1, class C>
	bool operator==(const stack<T1, C>& x, const stack<T1, C>& y) {
		return x.c == y.c;
	}

	template<class T1, class C>
	bool operator<(const stack<T1, C>& x, const stack<T1, C>& y) {
		return x.c < y.c;
	}

	template<class T1, class C>
	bool operator!=(const stack<T1, C>& x, const stack<T1, C>& y) {
		return !(x == y);
	}

	template<class T1, class C>
	bool operator>(const stack<T1, C>& x, const stack<T1, C>& y) {
		return y < x;
	}

	template<class T1, class C>
	bool operator>=(const stack<T1, C>& x, const stack<T1, C>& y) {
		return !(x < y);
	}

	template<class T1, class C>
	bool operator<=(const stack<T1, C>& x, const stack<T1, C>& y) {
		return !(y < x);
	}
}

#endif /*STACK_HPP*/
