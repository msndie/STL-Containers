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
		typedef Key																key_type;
		typedef T																mapped_type;
		typedef pair<const key_type, mapped_type>								value_type;
		typedef typename Allocator::size_type									size_type;
		typedef typename Allocator::difference_type								difference_type;
		typedef Compare															key_compare;
		typedef Allocator														allocator_type;
		typedef value_type&														reference;
		typedef const value_type&												const_reference;
		typedef typename Allocator::pointer										pointer;
		typedef typename Allocator::const_pointer								const_pointer;
		typedef typename Allocator::template rebind< node<value_type> >::other	allocator_node;

	private:
		allocator_type			_alloc;
		allocator_node			_alloc_for_node;
		ft::tree<value_type>	_tree;
		key_compare				_comp;

	public:
		map() : _alloc(Allocator()), _tree(tree<value_type>(_alloc_for_node)) {}

		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
				: _alloc(alloc), _comp(comp), _tree(tree<value_type>(_alloc_for_node)) {}

		void insert_node(const value_type& value) {
			ft::node<value_type>	*current, *parent, *x;

			current = _tree._root;
			parent = nullptr;
			while (current != &_tree._sentinel) {
				if (value.first == current->data->first) return;
				parent = current;
				current = _comp(value.first, current->data->first) ? current->left : current->right;
			}
			x = _alloc_for_node.allocate(sizeof(*x));
			_alloc_for_node.construct(x, node<value_type>(value));
			x->color = RED;
			x->right = &_tree._sentinel;
			x->left = &_tree._sentinel;
			x->parent = parent;
			if (parent) {
				if (_comp(value.first, parent->data->first)) parent->left = x;
				else parent->right = x;
			} else {
				_tree._root = x;
			}
			_tree.insertFixup(x);
//			return;
		}


//		template< class InputIt >
//		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
//			: _alloc(alloc), _comp(comp), _tree(tree< value_type >(std::allocator<node<value_type > >())) {}
//
//		map(const map& other) {}

	};

}


#endif /*MAP_HPP*/
