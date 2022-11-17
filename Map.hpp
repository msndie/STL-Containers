#include <functional>
#include "Utility.hpp"
#include "Tree.hpp"

#ifndef MAP_HPP
#define MAP_HPP

namespace ft {

	template <class Key, class P, class Compare>
	class map_value_compare : private Compare {
	public:
		map_value_compare() : Compare() {}

		map_value_compare(Compare c) : Compare(c) {}

		const Compare& key_comp() const { return *this; }

		bool operator()(const P& x, const P& y) const {
			return static_cast<const Compare&>(*this)(x.first, y.first);
		}

		bool operator()(const P& x, const Key& y) const {
			return static_cast<const Compare&>(*this)(x.first, y);
		}

		bool operator()(const Key& x, const P& y) const {
			return static_cast<const Compare&>(*this)(x, y.first);
		}

		void swap(map_value_compare&y) {
			std::swap(static_cast<Compare&>(*this), static_cast<Compare&>(y));
		}
	};

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
		typedef typename Allocator::template rebind< node<value_type> >::other	node_allocator;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
		private:
			key_compare	comp;
		public:
			value_compare(key_compare c) : comp(c) {}
			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

	private:
		typedef map_value_compare<key_type, value_type, key_compare>	vc;
		typedef tree<value_type, vc, node_allocator>					base;

		allocator_type			_alloc;
		base					_tree;
//		key_compare				_comp;

	public:
		typedef typename base::iterator					iterator;
		typedef typename base::const_iterator			const_iterator;
		typedef typename base::reverse_iterator 		reverse_iterator;
		typedef typename base::const_reverse_iterator	const_reverse_iterator;

		map() : _alloc(Allocator()), _tree(vc(key_compare()), typename base::allocator_type(_alloc)) {}

		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
				: _alloc(alloc), _tree(vc(comp), typename base::allocator_type(_alloc)) {}

		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _alloc(alloc), _tree(vc(comp), typename base::allocator_type(_alloc)) {
			insert(first, last);
		}
//
		map(const map& other) : _alloc(other._alloc), _tree(other._tree) {}

		~map() {}

		iterator begin() { return iterator(_tree.begin()); }
		const_iterator begin() const { return const_iterator(_tree.begin()); }
		iterator end() { return iterator(_tree.end()); }
		const_iterator end() const { return const_iterator(_tree.end()); }
		reverse_iterator rbegin() { return reverse_iterator(_tree.last()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree.last()); }
		reverse_iterator rend() { return reverse_iterator(_tree.end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_tree.end()); }


		pair<iterator, bool> insert(const value_type& value) {
			return _tree.insert_node(_tree._root, value);
		}

		template< class InputIt >
		void insert(InputIt first, InputIt last) {
			while (first != last) {
				_tree.insert_node(_tree._root, *first);
				++first;
			}
		}

		iterator insert(iterator pos, const value_type& value) {
			if (pos == end()) {
				return insertNode(_tree._root, value).first;
			} else {
				if (pos->first > value.first) {
					iterator prev = pos;
					--prev;
					while (prev != end() && prev->first >= value.first){
						--pos;
						--prev;
					}
				} else if (pos->first < value.first) {
					iterator next = pos;
					++next;
					while (next != end() && next->first <= value.first) {
						++pos;
						++next;
					}
				}
			}
			return insertNode(pos.base(), value).first;
		}

		void erase(iterator pos) {
			if (pos.base() != _tree._sentinel) {
				_tree.deleteNode(pos.base());
			}
		}

		void erase(iterator first, iterator last) {
			while (first != last) {
				_tree.deleteNode(first.base());
				++first;
			}
		}

		size_type erase(const Key& key) {
			node<value_type>* node = _tree.findNode();
			if (node) {
				_tree.deleteNode(node);
				return 1;
			}
			return 0;
		}

	};

}


#endif /*MAP_HPP*/
