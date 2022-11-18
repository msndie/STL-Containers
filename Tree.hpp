#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <memory>
#include "Iterator.hpp"

#define RED true
#define BLACK false
#define COLOR bool
#define NIL &_sentinel

namespace ft {

	template <class T>
	struct node {
		COLOR			color;
		bool			nil;
		struct node*	begin;
		struct node*	parent;
		struct node*	left;
		struct node*	right;
		T				data;

		node() : color(BLACK), nil(true), begin(this), parent(nullptr), left(this), right(this), data() {}
		node(const T& data) : color(BLACK), nil(false), begin(this), parent(nullptr), left(this), right(this), data(data) {}
		~node() {}
	};

	template <class T, class Compare, class Alloc>
	class tree {
	public:
		typedef T															value_type;
		typedef ft::node<value_type>										node_type;
		typedef node_type*													node_pointer;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::difference_type					difference_type;
		typedef typename ft::node_iterator<node<T>*, T, difference_type>		iterator;
		typedef typename ft::node_iterator<const node<T>*, T, difference_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef std::size_t														size_type;

		node_type 			_sentinel;
		node_pointer 		_root;
	private:
		allocator_type		_alloc;
		Compare				_comp;
		size_type			_size;


	public:
		tree(const Compare& comp, const Alloc& alloc) : _root(NIL), _alloc(alloc), _comp(comp), _size(0) {}
		tree(const tree& other) : _root(NIL), _alloc(other._alloc), _comp(other._comp), _size(0) {
			iterator it = iterator(other.begin());
			iterator end = iterator(other.end());

			while (it != end) {
				insert_node(_root, it.base()->data);
				++it;
			}
		}
		~tree() { clear(_root); }
		tree& operator=(const tree& other) {
			if (&other != this) {
				_size = 0;
				clear(_root);
				_root = NIL;
				if (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value) {
					_alloc = other._alloc;
				}
				iterator it = iterator(other.begin());
				iterator end = iterator(other.end());
				while (it != end)
					insert_node(_root, *it++);
			}
			return *this;
		}

		size_type size() const {
			return _size;
		}

		void clear(node_pointer tmp) {
			if (tmp == NIL) return;
			if (tmp->left != NIL) clear(tmp->left);
			if (tmp->right != NIL) clear(tmp->right);
			_alloc.destroy(tmp);
			_alloc.deallocate(tmp, sizeof(node_type));
		}

		node<value_type>* begin() const {
			node<value_type>* tmp = _root;

			while (tmp->left != NIL) {
				tmp = tmp->left;
			}
			return tmp;
		}

		node<value_type>* last() const {
			node<value_type>* tmp = _root;

			while (tmp->right != NIL) {
				tmp = tmp->right;
			}
			return tmp;
		}

		node<value_type>* end() const {
			node<value_type>* tmp = _root;

			while (tmp->right != NIL) {
				tmp = tmp->right;
			}
			return tmp->right;
		}

		node<value_type>* find_node(const value_type& value) {
			node<value_type> *current = _root;

			while(current != NIL) {
				if(value == current->data)
					return current;
				else
					current = _comp(value, current->data) ? current->left : current->right;
			}
			return nullptr;
		}

		pair<iterator, bool> insert_node(node<value_type> *hint, const value_type& value) {
			node<value_type>	*current, *parent, *x;

			current = hint;
			parent = nullptr;
			while (current != NIL) {
				if (value.first == current->data.first) return ft::make_pair(iterator(current),false);
				parent = current;
				current = _comp(value, current->data) ? current->left : current->right;
			}
			x = _alloc.allocate(sizeof(*x));
			_alloc.construct(x, node<value_type>(value));
			x->color = RED;
			x->right = NIL;
			x->left = NIL;
			x->parent = parent;
			if (parent) {
				if (_comp(value, parent->data)) parent->left = x;
				else parent->right = x;
			} else {
				_root = x;
			}
			insertFixup(x);
			if (x == last()) _sentinel.parent = x;
			if (x == begin()) _sentinel.begin = x;
			++_size;
			return ft::make_pair< iterator, bool >(iterator(x),true);
		}

		void delete_node(node<T>* z) {
			node<T>	*y, *x;

			if (!z || z == NIL) return;
			if (z->left == NIL || z->right == NIL) y = z;
			else {
				y = z->right;
				while (y->left != NIL) y = y->left;
			}
			if (y->left != NIL) x = y->left;
			else x = y->right;
			x->parent = y->parent;
			if (y->parent) {
				if (y == y->parent->left) y->parent->left = x;
				else y->parent->right = x;
			} else _root = x;
			if (y != z) copy_data_to_node(z, y->data);
			if (y->color == BLACK) deleteFixup(x);
			_alloc.destroy(y);
			_alloc.deallocate(y, sizeof(node_type));
			_sentinel.parent = last();
			_sentinel.begin = begin();
			--_size;
		}

		void deleteFixup(node<T>* x) {
			node<T>*	w;

			while (x != _root && x->color == BLACK) {
				if (x == x->parent->left) {
					w = x->parent->right;
					if (w->color == RED) {
						w->color = BLACK;
						w->parent->color = RED;
						rotateLeft(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK) {
						w->color = RED;
						x = x->parent;
					} else {
						if (w->right->color == BLACK) {
							w->left->color = BLACK;
							w->color = BLACK;
							rotateRight(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						rotateLeft(x->parent);
						x = _root;
					}
				} else {
					w = x->parent->left;
					if (w->color == RED) {
						w->color = BLACK;
						w->parent->color = RED;
						rotateRight(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK) {
						w->color = RED;
						x = x->parent;
					} else {
						if (w->left->color == BLACK) {
							w->right->color = BLACK;
							w->color = RED;
							rotateLeft(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						w->parent->color = BLACK;
						w->left->color = BLACK;
						rotateRight(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}

		void insertFixup(node<T>* x) {
			node<T>*	y;

			while (x != _root && x->parent->color == RED) {
				if (x->parent == x->parent->parent->left) {
					y = x->parent->parent->right;
					if (y->color == RED) {
						x->parent->color = BLACK;
						y->color = BLACK;
						x->parent->parent->color = RED;
						x = x->parent->parent;
					} else {
						if (x == x->parent->right) {
							x = x->parent;
							rotateLeft(x);
						}
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						rotateRight(x->parent->parent);
					}
				} else {
					y = x->parent->parent->left;
					if (y->color == RED) {
						x->parent->color = BLACK;
						y->color = BLACK;
						x->parent->parent->color = RED;
						x = x->parent->parent;
					} else {
						if (x == x->parent->left) {
							x = x->parent;
							rotateRight(x);
						}
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						rotateLeft(x->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		}

		void rotateRight(node<T>* x) {
			node<T>* y = x->left;

			x->left = y->right;
			if (y->right != NIL) y->right->parent = x;
			if (y != NIL) y->parent = x->parent;
			if (x->parent) {
				if (x == x->parent->right) x->parent->right = y;
				else x->parent->left = y;
			} else _root = y;
			y->right = x;
			if (x != NIL) x->parent = y;
		}

		void rotateLeft(node<T>* x) {
			node<T>* y = x->right;

			x->right = y->left;
			if (y->left != NIL) y->left->parent = x;
			if (y != NIL) y->parent = x->parent;
			if (x->parent) {
				if (x == x->parent->left) x->parent->left = y;
				else x->parent->right = y;
			} else _root = y;
			y->left = x;
			if (x != NIL) x->parent = y;
		}

		void copy_data_to_node(node<value_type>* n, const value_type& v) {
			node<value_type> *child_l, *child_r, *parent;

			child_l = n->left;
			child_r = n->right;
			parent = n->parent;
			_alloc.destroy(n);
			_alloc.construct(n, node<value_type>(v));
			n->left = child_l;
			n->right = child_r;
			n->parent = parent;
		}

	};
}

#endif /*TREE_HPP*/
