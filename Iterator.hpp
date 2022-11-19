#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Utility.hpp"

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
		iterator operator++(int) { iterator tmp(*this); ++_value; return tmp; }
		iterator operator--(int) { iterator tmp(*this); --_value; return tmp; }
		iterator operator-(difference_type n) const { return *this + (-n); }
		iterator& operator-=(difference_type n) { *this += -n; return *this; }
		iterator operator+(difference_type n) const { iterator tmp(*this); tmp += n; return tmp; }
		iterator& operator+=(difference_type n) { _value += n; return (*this); }
		reference operator*() const { return *_value; }
		pointer operator->() const { return &(*_value); }
		reference operator[](difference_type n) { return _value[n]; }
		iterator_type base() const { return _value; }
	};

	template <class Node, class Pair, class DiffType>
	class node_iterator {
	private:
		Node _node;
	public:
		typedef Node															iterator_type;
		typedef Pair			value_type;
		typedef DiffType													difference_type;
		typedef Pair&			reference;
		typedef const Pair& 											const_reference;
		typedef Pair*			pointer;
		typedef const Pair* 												const_pointer;
		typedef std::random_access_iterator_tag	iterator_category;

		node_iterator() : _node() {}
		explicit node_iterator(Node value) : _node(value) {}
		template <class N, class P, class D>
		node_iterator(const node_iterator<N, P, D>& other,
					  typename ft::enable_if<std::is_convertible<N, Node>::value>::type* = 0)
				: _node(other.base()) {}
		~node_iterator() {}

		iterator_type base() const { return _node; }
		node_iterator &operator=(const node_iterator &other) { _node = other._node; return *this; }
		node_iterator operator++(int) { node_iterator tmp(*this); next(); return tmp; }
		node_iterator &operator++() { next(); return *this; }
		node_iterator operator--(int) { node_iterator tmp(*this); prev(); return tmp; }
		node_iterator &operator--() { prev(); return *this; }
		reference operator*() { return _node->data; }
		const_reference operator*() const { return _node->data; }
		pointer operator->() { return &_node->data; }
		const_pointer operator->() const { return &_node->data; }
		bool operator==(node_iterator const &obj) const { return _node == obj._node; }
		bool operator!=(node_iterator const &obj) const { return _node != obj._node; }
		bool operator>(node_iterator const &obj) const { return _node->data > obj._node->data; }
		bool operator<(node_iterator const &obj) const { return obj._node->data > _node->data; }
		bool operator<=(node_iterator const &obj) const { return _node->data <= obj._node->data; }
		bool operator>=(node_iterator const &obj) const { return _node->data >= obj._node->data; }
	private:
		void next() {
			if (_node->nil && _node->begin != _node) _node = _node->begin;
			else if (!_node->right->nil) {
				_node = _node->right;
				while (!_node->left->nil)
					_node = _node->left;
			} else {
				Node current = _node;
				Node tmp = _node;
				_node = _node->parent;
				if (!_node) { _node = current->right; return; }
				while (_node->left != tmp) {
					if (!_node->parent) { _node = current->right; break; }
					tmp = _node;
					_node = _node->parent;
				}
			}
		}

		void prev() {
			if (_node->nil) _node = _node->parent;
			else if (!_node->left->nil) {
				_node = _node->left;
				while (!_node->right->nil)
					_node = _node->right;
			} else {
				Node tmp = _node;
				_node = _node->parent;
				while (_node->right != tmp) {
					tmp = _node;
					if (!_node->parent) { _node = tmp->left - 1; break; }
					_node = _node->parent;
				}
			}
		}
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

		reference operator*() { return *_value; }

		pointer operator->() { return &operator*(); }

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
