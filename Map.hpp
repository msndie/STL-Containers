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
		typedef map_value_compare<key_type, value_type, key_compare> vc;
		typedef tree<value_type, vc, node_allocator>	base;

		allocator_type			_alloc;
//		node_allocator 			_alloc_for_node;
		base					_tree;
		key_compare				_comp;

	public:
		map() : _alloc(Allocator()), _tree(vc(key_compare()), typename base::allocator_type(_alloc)) {}

		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
				: _alloc(alloc), _comp(comp), _tree(vc(comp), typename base::allocator_type(_alloc)) {}

//		template< class InputIt >
//		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
//			: _alloc(alloc), _comp(comp), _tree(tree< value_type >(std::allocator<node<value_type > >())) {}
//
//		map(const map& other) {}

		void insert(const value_type& v) {
			_tree.insert_node(v);
		}

	};

}


#endif /*MAP_HPP*/
