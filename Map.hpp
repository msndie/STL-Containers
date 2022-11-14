#include <functional>
#include "Utility.hpp"
#include "Tree.hpp"

#ifndef MAP_HPP
#define MAP_HPP

namespace ft {

	template <class Key, class T, class	Compare = std::less<Key>,
			class Allocator = std::allocator<pair<const Key, T> > >
	class map {
	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef typename Allocator::size_type		size_type;
		typedef typename Allocator::difference_type	difference_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

	private:
		allocator_type			_alloc;
		ft::tree<value_type>	_tree;

		void insert_node(const value_type& value) {
			ft::node<value_type>*	current, *parent, *x;

			current = _tree._root;
			parent = nullptr;
			while (current != &_tree._sentinel) {
				if (value.first == current->data.first) return;
				parent = current;
				current = _comp(value.first, current->data.first) ? current->left : current->right;
			}
			x = _alloc.allocate(sizeof(*x));
			_alloc.construct(x, value);
			x->color = RED;
			x->right = &_tree._sentinel;
			x->left = &_tree._sentinel;
			x->parent = parent;
			if (parent) {
				if (_comp(value.first, parent->data.first))
					parent->left = x;
				else
					parent->right = x;
			} else {
				_tree._root = x;
			}
			insertFixup(x);
		}
	};

}


#endif /*MAP_HPP*/
