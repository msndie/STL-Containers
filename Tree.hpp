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
		struct node*	parent;
		struct node*	left;
		struct node*	right;
		T				data;

//		node() : color(BLACK), nil(true), parent(nullptr), left(this), right(this), data() {}
//		node(const T& data) : color(BLACK), nil(false), parent(nullptr), left(this), right(this), data(data) {}
		node() : color(BLACK), nil(true), parent(nullptr), left(this), right(this), data() {}
		node(const T& data) : color(BLACK), nil(false), parent(nullptr), left(this), right(this), data(data) {}
		~node() {}
	};

	template <class T, class Compare, class Alloc>
	class tree {
	public:
		typedef T															value_type;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::difference_type					difference_type;
		typedef typename ft::node_iterator<node<T>*, T, difference_type>		iterator;
		typedef typename ft::node_iterator<const node<T>*, T, difference_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator >				const_reverse_iterator;

		node<T>			_sentinel;
		node<T>*		_root;
	private:
		allocator_type		_alloc;
		Compare				_comp;

	public:
		tree(const Compare& comp, const Alloc& alloc) : _root(NIL), _alloc(alloc), _comp(comp) {}
		tree(const tree& other) : _root(NIL), _alloc(other._alloc), _comp(other._comp) {
			iterator it = iterator(other.begin());
			iterator end = iterator(other.end());

			while (it != end) {
				insert_node(_root, it.base()->data);
				++it;
			}
		}
		~tree() {}

		node<value_type>* begin() const {
			node<value_type>* tmp = _root;

			while (tmp->left != NIL) {
				tmp = tmp->left;
			}
			return tmp;
		}

		node<value_type>* begin() {
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

		node<value_type>* last() {
			node<value_type>* tmp = _root;

			while (tmp->right != NIL) {
				tmp = tmp->right;
			}
			return tmp;
		}

		node<value_type>* end() {
			node<value_type>* tmp = _root;

			while (tmp != NIL) {
				tmp = tmp->right;
			}
			return tmp;
//			return &_sentinel;
		}

		node<value_type>* end() const {
			node<value_type>* tmp = _root;

			while (tmp != NIL) {
				tmp = tmp->right;
			}
			return tmp;
//			return NIL;
		}

		node<value_type>* findNode(const value_type& value) {
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
			return ft::make_pair< iterator, bool >(iterator(x),true);
		}

		void deleteNode(node<T>* z) {
			node<T>	*y, *x;

			if (!z || z == NIL) return;
			if (z->left == NIL || z->right == NIL) {
				y = z;
			} else {
				y = z->right;
				while (y->left != NIL) {
					y = y->left;
				}
			}
			if (y->left != NIL) {
				x = y->left;
			} else {
				x = y->right;
			}
			x->parent = y->parent;
			if (y->parent) {
				if (y == y->parent->left) {
					y->parent->left = x;
				} else {
					y->parent->right = x;
				}
			} else {
				_root = x;
			}
			if (y != z) {
				z->data = y->data;
			}
			if (y->color == BLACK) {
				deleteFixup(x);
			}
			_alloc.destruct(y);
			_alloc.deallocate(y);
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
			if (y->right != NIL) {
				y->right->parent = x;
			}
			if (y != NIL) {
				y->parent = x->parent;
			}
			if (x->parent) {
				if (x == x->parent->right) {
					x->parent->right = y;
				} else {
					x->parent->left = y;
				}
			} else {
				_root = y;
			}
			y->right = x;
			if (x != NIL) {
				x->parent = y;
			}
		}

		void rotateLeft(node<T>* x) {
			node<T>* y = x->right;

			x->right = y->left;
			if (y->left != NIL) {
				y->left->parent = x;
			}
			if (y != NIL) {
				y->parent = x->parent;
			}
			if (x->parent) {
				if (x == x->parent->left) {
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
			} else {
				_root = y;
			}
			y->left = x;
			if (x != NIL) {
				x->parent = y;
			}
		}

	};
}

#endif /*TREE_HPP*/
