#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include "Iterator.hpp"

namespace ft {

	template< class T, class A = std::allocator<T> >
	class vector {
	public:
		typedef T										value_type;
		typedef A 										allocator_type;
		typedef std::size_t								size_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef T*										pointer;
		typedef const T*								const_pointer;
		typedef ft::iterator<pointer>					iterator;
		typedef ft::iterator<const_pointer>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		T*				_array;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;

	public:

		explicit vector(const A& alloc = A()) : _array(nullptr), _allocator(alloc), _size(0), _capacity(0) {}

		explicit vector(size_type count, const_reference value = T(), const A& alloc = A()) : _size(count), _capacity(count), _array(nullptr), _allocator(alloc) {
			_array = _allocator.allocate(count);
			for (size_type i = 0; i < _size; ++i) {
				_array[i] = value;
			}
		}

		vector(const vector& other) {
			_capacity = other._capacity;
			_size = other._size;
			_allocator = other._allocator;
			_array = _allocator.allocate(_capacity);
			std::memcpy(_array, other._array, sizeof(T) * _size);
		}

		template<class InputIt>
		vector(InputIt first, InputIt last, const A& alloc = A(),
			   typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = nullptr)
			   : _array(nullptr), _allocator(alloc), _size(0), _capacity(0) {
			assign(first, last);
		}

		~vector() {
			clear();
			_allocator.deallocate(_array, _capacity);
		}

		vector& operator=(const vector& other) {
			if (&other != this) {
				if (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value) {
					if (_allocator != other._allocator) {
						clear();
						_allocator.deallocate(_array, _capacity);
						_capacity = 0;
						_array = nullptr;
					}
					_allocator = other._allocator;
				}
				assign(other.begin(), other.end());
			}
			return *this;
		}

		const_reference operator[](size_type pos) { return _array[pos]; }
		reference operator[](size_type pos) const { return _array[pos]; }
		allocator_type get_allocator() const { return _allocator; }
		reference front() { return _array[0]; }
		const_reference front() const { return _array[0]; }
		reference back() { return _array[_size - 1]; }
		const_reference back() const { return _array[_size - 1]; }
		pointer data() { return _array; }
		const_pointer data() const { return _array; }
		bool empty() const { return _size == 0; }
		size_type size() const { return _size; }
		size_type capacity() { return _capacity; }
		iterator begin() { return iterator(_array); }
		const_iterator begin() const { return const_iterator(_array); }
		iterator end() { return iterator(&_array[_size]); }
		const_iterator end() const { return const_iterator(&_array[_size]); }
		reverse_iterator rbegin() { return reverse_iterator(--end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(--end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
		size_type max_size() const {
			return std::min(static_cast<size_type>(std::numeric_limits<typename A::difference_type>::max()),
							_allocator.max_size());
		}

		reference at(size_type pos) {
			if (pos >= _size) throw std::out_of_range("vector");
			return _array[pos];
		}

		const_reference at(size_type pos) const {
			if (pos >= _size) throw std::out_of_range("vector");
			return _array[pos];
		}

		void assign(size_type count, const_reference value) {
			if (count <= _capacity) {
				size_type s = _size;
				std::fill_n(begin(), std::min(s, count), value);
				if (count > s)
					construct_at_end(count - s, value);
				else
					destruct_at_end(&_array[count]);
			} else {
				clear();
				reserve(count);
				construct_at_end(count, value);
			}
		}

		template<class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
		assign(InputIt first, InputIt last) {
			size_type new_size = std::distance(first, last);
			if (new_size <= _capacity) {
				size_type s = _size;
				for (size_type i = 0; i < std::min(s, new_size); ++i) {
					_array[i] = *first++;
				}
				if (new_size > s) {
					for (size_type j = 0; j < new_size - s; ++j, ++_size) {
						_allocator.construct(&_array[_size], *first++);
					}
				} else {
					destruct_at_end(&_array[new_size]);
				}
			} else {
				clear();
				reserve(new_size);
				for (size_type j = 0; j < new_size; ++j, ++_size) {
					_allocator.construct(&_array[_size], *first++);
				}
			}
		}

		iterator insert(const_iterator pos, const_reference value) {
			return insert_helper(pos, 1, value, false);
		}

		iterator insert(const_iterator pos, size_type count, const_reference value) {
			return insert_helper(pos, count, value, true);
		}

//		TODO try to increase performance
		template<class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last,
						typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = nullptr) {
			size_type dist = std::distance(first, last);
			pointer p = _array + (pos - begin());

			if (first == last) return iterator(p);
			validate_iterator_values(first, last, dist);
			if (_size + dist - 1 < _capacity) {
				if (p == &_array[_size]) {
					construct_at_end(first, last);
				} else {
					move_part_of_array(p + dist, p, (&_array[_size] - p) * sizeof(value_type));
					pointer tmp = p;
					for (; first != last; ++first, ++tmp, ++_size) {
						_allocator.construct(tmp, *first);
					}
				}
			} else {
				size_type tmp_capacity = _capacity;
				while (_capacity < _size + dist)
					_capacity = _capacity ? _capacity * 2 : 1;
				pointer tmp = _allocator.allocate(_capacity);
				pointer tmp_pointer = p;

				for (size_type i = 0, j = 0; j < _size + dist; ++j) {
					if (&_array[i] == tmp_pointer && j - i < dist) {
						_allocator.construct(&tmp[j], *first++);
						if (tmp_pointer == p) p = &tmp[j];
						continue;
					} else {
						_allocator.construct(&tmp[j], _array[i]);
						_allocator.destroy(&_array[i++]);
					}
				}
				if (_array) _allocator.deallocate(_array, tmp_capacity);
				_array = tmp;
				_size += dist;
			}
			return iterator(p);
		}

		iterator erase(iterator pos) {
			pointer p = _array + (pos - begin());

			if (p == &_array[_size]) return end();
			_allocator.destroy(p);
			move_part_of_array(p + 1, p, (&_array[_size--] - p) * sizeof(value_type));
			return iterator(p);
		}

//		TODO try to increase performance
		iterator erase(iterator first, iterator last) {
			pointer p = _array + (first - begin());
			size_type dist = std::distance(first, last);

			if (first != last) {
				while (first != last) {
					_allocator.destroy(first.base());
					++first;
				}
				move_part_of_array(p + dist, p, (&_array[_size] - p) * sizeof(value_type));
				_size -= dist;
			}
			return iterator(p);
		}

		void clear() {
			destruct_all(_array, _size);
			_size = 0;
		}

		void reserve(size_type new_cap) {
			if (new_cap > _capacity) {
				pointer tmp = _allocator.allocate(new_cap);
				for (size_type i = 0; i < _size; ++i) {
					_allocator.construct(&tmp[i], _array[i]);
					_allocator.destroy(&_array[i]);
				}
				if (_array) _allocator.deallocate(_array, _capacity);
				_capacity = new_cap;
				_array = tmp;
			}
		}

		void resize(size_type count, T value = T()) {
			size_type diff = count - _size;

			if (_size < count) {
				if (_capacity - _size < diff) {
					size_type new_cap = _capacity;
					if (new_cap >= max_size() / 2) {
						new_cap = max_size();
					}
					reserve(std::max(2 * new_cap, _size + diff));
				}
				construct_at_end(count - _size, value);
			} else if (_size > count) {
				destruct_at_end(_array + count);
			}
		}

		void push_back(const_reference value) {
			if (_size == _capacity) {
				!_capacity ? reserve(1) : reserve(_capacity * 2);
			}
			construct_at_end(1, value);
		}

		void pop_back() {
			destruct_at_end(&_array[_size - 1]);
		}

		void swap(vector& other) {
			std::swap(_array, other._array);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_allocator, other._allocator);
		}

	private:

		void move_part_of_array(pointer from, pointer to, size_t len) {
			std::memmove(static_cast<void *>(to), static_cast<void *>(from), len);
		}

		void construct_at_end(size_type n, const_reference v) {
			for (size_type j = 0; j < n; ++j, ++_size) {
				_allocator.construct(&_array[_size], v);
			}
		}

		template <class InputIter>
		typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type
		construct_at_end(InputIter first, InputIter last) {
			while (first != last) {
				_allocator.construct(&_array[_size++], *first++);
			}
		}

		void destruct_at_end(pointer new_end) {
			pointer old_end = &_array[_size];
			while (new_end != old_end) {
				_allocator.destroy(--old_end);
				--_size;
			}
		}

		iterator insert_helper(const_iterator pos, size_type count, const_reference value, bool fill) {
			pointer p = _array + (pos - begin());

			if (count == 0) return iterator(p);
			if (_size + count - 1 < _capacity) {
				if (p == &_array[_size]) {
					construct_at_end(count, value);
				} else {
					move_part_of_array(p + count, p, (&_array[_size] - p) * sizeof(value_type));
					pointer tmp = p;
					for (size_type i = 0; i < count; ++i, ++tmp) {
						_allocator.construct(tmp, value);
						++_size;
					}
				}
			} else {
				size_type tmp_capacity = _capacity;
				if (fill) {
					_capacity += count;
				} else {
					while (_capacity < _size + count)
						_capacity = _capacity ? _capacity * 2 : 1;
				}
				pointer tmp = _allocator.allocate(_capacity);
				pointer tmp_pointer = p;
				for (size_type i = 0, j = 0; j < _size + count; ++j) {
					if (&_array[i] == tmp_pointer && j - i < count) {
						_allocator.construct(&tmp[j], value);
						if (tmp_pointer == p) p = &tmp[j];
						continue;
					} else {
						_allocator.construct(&tmp[j], _array[i]);
						_allocator.destroy(&_array[i++]);
					}
				}
				if (_array) _allocator.deallocate(_array, tmp_capacity);
				_array = tmp;
				_size += count;
			}
			return iterator(p);
		}

		void destruct_all(pointer where, size_type how_many) {
			for (size_type i = 0; i < how_many; ++i) {
				_allocator.destroy(&where[i]);
			}
		}

		template<class InputIt>
		void validate_iterator_values(InputIt first, InputIt last, size_t range,
									  typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = nullptr) {
			pointer buffer = _allocator.allocate(range);

			for (size_type i = 0; first != last; ++first, ++i) {
				try {
					_allocator.construct(&buffer[i], *first);
				} catch (...) {
					destruct_all(buffer, i);
					_allocator.deallocate(buffer, range);
					throw;
				}
			}
			destruct_all(buffer, range);
			_allocator.deallocate(buffer, range);
		}
	};

	template< class T, class A >
	bool operator==( const ft::vector<T,A>& lhs, const ft::vector<T,A>& rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class T, class A >
	bool operator!=( const ft::vector<T,A>& lhs, const ft::vector<T,A>& rhs ) {
		return !(lhs == rhs);
	}

	template< class T, class A >
	bool operator<( const ft::vector<T,A>& lhs, const ft::vector<T,A>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class A >
	bool operator>( const ft::vector<T,A>& lhs, const ft::vector<T,A>& rhs ) {
		return rhs < lhs;
	}

	template< class T, class A >
	bool operator>=( const ft::vector<T,A>& lhs, const ft::vector<T,A>& rhs ) {
		return !(lhs < rhs);
	}

	template< class T, class A >
	bool operator<=( const ft::vector<T,A>& lhs, const ft::vector<T,A>& rhs ) {
		return !(rhs < lhs);
	}

}

namespace std {
	template< class T, class A >
	void swap(ft::vector<T,A>& x, ft::vector<T,A>& y) {
		x.swap(y);
	}
}

#endif /*VECTOR_HPP*/
