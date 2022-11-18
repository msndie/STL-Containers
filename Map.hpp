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
		bool operator()(const P& x, const P& y) const { return static_cast<const Compare&>(*this)(x.first, y.first); }
		bool operator()(const P& x, const Key& y) const { return static_cast<const Compare&>(*this)(x.first, y); }
		bool operator()(const Key& x, const P& y) const { return static_cast<const Compare&>(*this)(x, y.first); }
		void swap(map_value_compare&y) { std::swap(static_cast<Compare&>(*this), static_cast<Compare&>(y)); }
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

		key_compare				_comp;
		allocator_type			_alloc;
		base					_tree;

	public:
		typedef typename base::iterator					iterator;
		typedef typename base::const_iterator			const_iterator;
		typedef typename base::reverse_iterator 		reverse_iterator;
		typedef typename base::const_reverse_iterator	const_reverse_iterator;

		map() : _comp(key_compare()), _alloc(Allocator()), _tree(vc(_comp), typename base::allocator_type(_alloc)) {}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
				: _alloc(alloc), _comp(comp), _tree(vc(comp), typename base::allocator_type(_alloc)) {}
		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _comp(comp), _alloc(alloc), _tree(vc(comp), typename base::allocator_type(_alloc)) {
			insert(first, last);
		}
		map(const map& other) : _comp(other._comp), _alloc(other._alloc), _tree(other._tree) {}
		~map() {}

		map& operator=(const map& other) {
			if (&other != this) {
				if (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value) {
					_alloc = other._alloc;
				}
				_tree = other._tree;
			}
			return *this;
		}

		allocator_type get_allocator() const { return _alloc; }
		size_type size() const { return _tree.size(); }
		bool empty() const { return _tree.size() == 0; }
		size_type max_size() const { return static_cast<size_type>(std::numeric_limits<difference_type>::max()); }
		iterator begin() { return iterator(_tree.begin()); }
		const_iterator begin() const { return const_iterator(_tree.begin()); }
		iterator end() { return iterator(_tree.end()); }
		const_iterator end() const { return const_iterator(_tree.end()); }
		reverse_iterator rbegin() { return reverse_iterator(iterator(_tree.last())); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(const_iterator(_tree.last())); }
		reverse_iterator rend() { return reverse_iterator(iterator(_tree.end())); }
		const_reverse_iterator rend() const { return const_reverse_iterator(const_iterator(_tree.end())); }
		T& at(const Key& key) {
			iterator it = find(key);

			if (it == end()) throw std::out_of_range("key not found");
			return it->second;
		}
		const T& at(const Key& key) const {
			iterator it = find(key);

			if (it == end()) throw std::out_of_range("key not found");
			return it->second;
		}

		T& operator[](const Key& key) {
			return insert(ft::make_pair(key, T())).first->second;
		}

		iterator find(const Key& key) {
			node<value_type> *current = _tree._root;

			while (!current->nil) {
				if (key == current->data.first)
					return iterator(current);
				else
					current = _comp(key, current->data.first) ? current->left : current->right;
			}
			return end();
		}

		const_iterator find(const Key& key) const {
			node<value_type> *current = _tree._root;

			while (!current->nil) {
				if (key == current->data.first)
					return iterator(current);
				else
					current = _comp(key, current->data.first) ? current->left : current->right;
			}
			return end();
		}

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
				return _tree.insert_node(_tree._root, value).first;
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
			return _tree.insert_node(pos.base(), value).first;
		}

		void erase(iterator pos) {
			if (pos.base() != &_tree._sentinel) {
				_tree.delete_node(pos.base());
			}
		}

		void erase(iterator first, iterator last) {
			iterator tmp;

			while (first != last) {
				tmp = first++;
				_tree.delete_node(tmp.base());
			}
		}

		size_type erase(const Key& key) {
			iterator it = find(key);
			if (it != end()) {
				_tree.delete_node(it.base());
				return 1;
			}
			return 0;
		}

	};

}


#endif /*MAP_HPP*/
