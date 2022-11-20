#ifndef SET_HPP
#define SET_HPP

#include <functional>
#include "Tree.hpp"

namespace ft {
	template <class Key, class Compare>
	class _set_value_compare : private Compare {
	public:
		_set_value_compare() : Compare() {}
		_set_value_compare(Compare c) : Compare(c) {}
		const Compare& key_comp() const { return *this; }
		bool operator()(const Key& x, const Key& y) const { return static_cast<const Compare&>(*this)(x, y); }
		bool equal(const Key& x, const Key& y) { return x == y; }
		void swap(_set_value_compare&y) { std::swap(static_cast<Compare&>(*this), static_cast<Compare&>(y)); }
	};

	template<
			class Key,
			class Compare = std::less<Key>,
			class Allocator = std::allocator<Key>
	> class set {
	public:
		typedef Key					key_type;
		typedef key_type			value_type;
		typedef Compare				key_compare;
		typedef key_compare			value_compare;
		typedef Allocator			allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;

	private:
		typedef _set_value_compare<key_type, key_compare>						_vc;
		typedef typename Allocator::template rebind< node<value_type> >::other	_node_allocator;
		typedef tree<value_type, _vc, _node_allocator>							_base;
		typedef typename Allocator::template rebind<_base>::other				_tree_allocator;

		_base*			_tree;
		allocator_type	_alloc;
		value_compare	_comp;
		_tree_allocator	_tree_alloc;

	public:
		typedef typename _base::node_pointer			pointer;
		typedef typename _base::const_node_pointer 		const_pointer;
		typedef typename _base::size_type				size_type;
		typedef typename _base::difference_type 		difference_type;
		typedef typename _base::const_iterator 			iterator;
		typedef typename _base::const_iterator 			const_iterator;
		typedef typename _base::const_reverse_iterator	reverse_iterator;
		typedef typename _base::const_reverse_iterator	const_reverse_iterator;

		set() : _alloc(Allocator()), _comp(value_compare()) {
			_tree_alloc = _tree_allocator(_alloc);
			_tree = _tree_alloc.allocate(sizeof(_base));
			_tree_alloc.construct(_tree, _base(_vc(_comp), typename _base::allocator_type(_alloc)));
		}
		explicit set(const Compare& comp, const Allocator& alloc = Allocator())
					: _comp(comp), _alloc(alloc) {
			_tree_alloc = _tree_allocator(_alloc);
			_tree = _tree_alloc.allocate(sizeof(_base));
			_tree_alloc.construct(_tree, _base(_vc(_comp), typename _base::allocator_type(_alloc)));
		}
		template< class InputIt >
		set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _comp(comp), _alloc(alloc) {
			_tree_alloc = _tree_allocator(_alloc);
			_tree = _tree_alloc.allocate(sizeof(_base));
			_tree_alloc.construct(_tree, _base(_vc(_comp), typename _base::allocator_type(_alloc)));
			insert(first, last);
		}
		set(const set& other) : _alloc(other._alloc), _comp(other._comp), _tree_alloc(other._tree_alloc) {
			_tree = _tree_alloc.allocate(sizeof(_base));
			_tree_alloc.construct(_tree, _base(*other._tree));
		}
		~set() {
			_tree_alloc.destroy(_tree);
			_tree_alloc.deallocate(_tree, sizeof(_base));
		}
		set& operator=(const set& other) {
			if (&other != this) {
				if (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value) {
					_alloc = other._alloc;
					_tree_alloc = other._tree_alloc;
					_comp = other._comp;
				}
				*_tree = *other._tree;
			}
			return *this;
		}

		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return _comp; }
		allocator_type get_allocator() const { return _alloc; }
		iterator begin() { return iterator(_tree->begin()); }
		const_iterator begin() const { return const_iterator(_tree->begin()); }
		iterator end() { return iterator(_tree->end()); }
		const_iterator end() const { return const_iterator(_tree->end()); }
		reverse_iterator rbegin() { return reverse_iterator(iterator(_tree->last())); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(const_iterator(_tree->last())); }
		reverse_iterator rend() { return reverse_iterator(iterator(_tree->end())); }
		const_reverse_iterator rend() const { return const_reverse_iterator(const_iterator(_tree->end())); }
		bool empty() const { return _tree->size() == 0; }
		size_type size() const { return _tree->size(); }
		size_type max_size() const { return static_cast<size_type>(std::numeric_limits<difference_type>::max()); }
		void clear() { _tree->clear(); }

		ft::pair<iterator, bool> insert(const value_type& value) {
			return _tree->insert_node(_tree->_root, value);
		}

		iterator insert(iterator pos, const value_type& value) {
			if (pos == end()) {
				return _tree->insert_node(_tree->_root, value).first;
			} else {
				if (!_comp(*pos, value)) {
					iterator prev = pos;
					--prev;
					while (prev != end() && (*prev == value || !_comp(*prev, value))){
						--pos;
						--prev;
					}
				} else if (_comp(*pos, value)) {
					iterator next = pos;
					++next;
					while (next != end() && (*next == value || _comp(*next, value))) {
						++pos;
						++next;
					}
				}
			}
			return _tree->insert_node(const_cast< node<value_type>* >(pos.base()), value).first;
		}

		template< class InputIt >
		void insert(InputIt first, InputIt last) {
			iterator it = begin();
			while (first != last) {
				it = insert(it, *first);
				++first;
			}
		}

		void erase(iterator pos) {
			if (pos.base() != &_tree->_sentinel) {
				_tree->delete_node(const_cast< node<value_type>* >(pos.base()));
			}
		}

		void erase(iterator first, iterator last) {
			iterator tmp;

			while (first != last) {
				tmp = first++;
				_tree->delete_node(const_cast< node<value_type>* >(tmp.base()));
			}
		}

		size_type erase(const Key& key) {
			iterator it = find(key);
			if (it != end()) {
				_tree->delete_node(const_cast< node<value_type>* >(it.base()));
				return 1;
			}
			return 0;
		}

		size_type count( const Key& key ) const {
			return find(key) == end() ? 0 : 1;
		}

		iterator find(const Key& key) {
			return _find_helper(key);
		}

		const_iterator find(const Key& key) const {
			return _find_helper(key);
		}

		ft::pair<iterator,iterator> equal_range(const Key& key) {
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const {
			return equal_range(key);
		}

		const_iterator lower_bound(const Key& key) const { return lower_bound(key); }
		iterator lower_bound(const Key& key) {
			node<value_type> *current = _tree->_root;

			while (!current->nil) {
				if (key == current->data)
					return iterator(current);
				else {
					if (_comp(key, current->data)) {
						if (!current->left->nil)
							current = current->left;
						else
							return iterator(current);
					}
					else {
						if (!current->right->nil)
							current = current->right;
						else
							return ++iterator(current);
					}
				}
			}
			return end();
		}

		const_iterator upper_bound(const Key& key) const { return upper_bound(key); }
		iterator upper_bound(const Key& key) {
			iterator tmp = lower_bound(key);

			return (tmp == end()) ? tmp : (_comp(key, *tmp)) ? tmp : ++tmp;
		}

		void swap(set& other) {
			std::swap(_tree, other._tree);
			std::swap(_tree_alloc, other._tree_alloc);
			std::swap(_comp, other._comp);
			std::swap(_alloc, other._alloc);
		}

	private:
		iterator _find_helper(const Key& key) const {
			node<value_type> *current = _tree->_root;

			while (!current->nil) {
				if (key == current->data)
					return iterator(current);
				else
					current = _comp(key, current->data) ? current->left : current->right;
			}
			return end();
		}
	};

	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
					 const ft::set<Key,Compare,Alloc>& rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
					 const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
					 const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return rhs < lhs;
	}

	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
					 const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}
}

namespace std {
	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key,Compare,Alloc>& lhs,
			   ft::set<Key,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif /*SET_HPP*/
