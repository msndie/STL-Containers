#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Utils.hpp"

namespace ft {

	template<class Iter>
	struct iterator_traits {
	public:
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<typename T>
	struct iterator_traits<T*> {
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T*> {
	public:
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator {
	private:
		T	_value;
	public:
		typedef T															iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

		iterator() : _value() {}

		iterator(iterator_type value) : _value(value) {}

		template< class U >
		iterator(const iterator<U>& other)
				 : _value(other.base()) {}

		~iterator() {}

		template< class U >
		iterator& operator=( const iterator<U>& other ) { _value = other._value; return *this; }

		iterator& operator++() { ++_value; return *this; }

		iterator& operator--() { --_value; return *this; }

		iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }

		iterator operator--(int) { iterator tmp(*this); --(*this); return tmp; }

		iterator operator-(difference_type n) const { return *this + (-n); }

		iterator& operator-=(difference_type n) { *this += -n; return *this; }

		iterator operator+(difference_type n) const { iterator tmp(*this); tmp += n; return tmp; }

		iterator& operator+=(difference_type n) { _value += n; return (*this); }

		reference operator*() const { return *_value; }

		pointer operator->() const { return &(*_value); }

		reference operator[](difference_type n) { return _value[n]; }

		iterator_type base() const { return _value; }
	};

	template <class T>
	class reverse_iterator {
	private:
		T _value;
	public:
		typedef T															iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

		reverse_iterator() : _value() {}

		reverse_iterator(iterator_type x) : _value(x) {}

		template<class U>
		reverse_iterator(const reverse_iterator<U>& u) : _value(u.base()) {}

		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& u) { _value = u.base(); return  *this; }

		iterator_type base() const { return _value; }

		reference operator*() const { iterator_type  tmp = _value; return *--tmp; }

		pointer operator->() const { return &operator*(); }

		reverse_iterator& operator++() { --_value; return *this; }

		reverse_iterator operator++(int) { reverse_iterator tmp(*this); --_value; return tmp; }

		reverse_iterator& operator--() { ++_value; return *this; }

		reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++_value; return tmp; }

		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_value - n); }

		reverse_iterator& operator+=(difference_type n) { _value -= n; return *this; }

		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_value + n); }

		reverse_iterator& operator-=(difference_type n) { _value += n; return *this; }

		reference operator[](difference_type n) const { return *(*this + n); }
	};

	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2> y) {
		return x.base() == y.base();
	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2> y) {
		return x.base() > y.base();
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2> y) {
		return x.base() >= y.base();
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2> y) {
		return x.base() != y.base();
	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2> y) {
		return x.base() < y.base();
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2> y) {
		return x.base() <= y.base();
	}

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type
	operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) {
		return y.base() - x.base();
	}

	template<class Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n,
			   const reverse_iterator<Iter>& it) {
		return reverse_iterator<Iter>(it.base() - n);
	}

	template <class Iter1, class Iter2>
	bool operator==(const iterator<Iter1>& x, const iterator<Iter2>& y) {
		return x.base() == y.base();
	}

	template <class Iter1, class Iter2>
	bool operator<(const iterator<Iter1>& x, const iterator<Iter2>& y) {
		return x.base() < y.base();
	}

	template <class Iter1, class Iter2>
	bool operator!=(const iterator<Iter1>& x, const iterator<Iter2>& y) {
		return !(x == y);
	}

	template <class Iter1, class Iter2>
	bool operator>(const iterator<Iter1>& x, const iterator<Iter2>& y) {
		return y < x;
	}

	template <class Iter1, class Iter2>
	bool operator>=(const iterator<Iter1>& x, const iterator<Iter2>& y) {
		return !(x < y);
	}

	template <class Iter1, class Iter2>
	bool operator<=(const iterator<Iter1>& x, const iterator<Iter2>& y) {
		return !(y < x);
	}

	template <class Iter1>
	bool operator!=(const iterator<Iter1>& x, const iterator<Iter1>& y) {
		return !(x == y);
	}

	template <class Iter1>
	bool operator>(const iterator<Iter1>& x, const iterator<Iter1>& y) {
		return y < x;
	}

	template <class Iter1>
	bool operator>=(const iterator<Iter1>& x, const iterator<Iter1>& y) {
		return !(x < y);
	}

	template <class Iter1>
	bool operator<=(const iterator<Iter1>& x, const iterator<Iter1>& y) {
		return !(y < x);
	}

	template <class Iter1, class Iter2>
	typename iterator<Iter1>::difference_type operator-(const iterator<Iter1>& x, const iterator<Iter2>& y) {
		return x.base() - y.base();
	}

	template <class Iter>
	iterator<Iter> operator+(typename iterator<Iter>::difference_type n,
			iterator<Iter> x) {
		x += n;
		return x;
	}
}

#endif /*ITERATOR_HPP*/
