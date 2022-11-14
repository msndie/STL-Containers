#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>

#define RED true
#define BLACK false
#define COLOR bool

namespace ft {

	template <class T>
	struct node {
		COLOR			color;
		bool			NIL;
		struct node*	parent;
		struct node*	left;
		struct node*	right;
		T				data;

		node() : color(BLACK), NIL(true), parent(nullptr), left(this), right(this), data(nullptr) {}
		node(const T& data) : color(BLACK), NIL(false), parent(nullptr), left(this), right(this), data(data) {}
		~node() {}
	};

	template <class T>
	class tree {
	public:
		typedef T			value_type;

		node<T>			_sentinel;
		node<T>*		_root;
		size_t			_size;
//	private:
	public:
		tree() : _root(&_sentinel), _size(0) {}
		~tree() {}

		void insertFixup(node<T>* x) {
			node<T>*	y;

			while (x != _root && x->parent->color == RED) {
				if (x->parent == x->parent->parent->left) {
					y = x->parent->parent->left
				}
			}
		}

	};
}

#endif /*TREE_HPP*/
