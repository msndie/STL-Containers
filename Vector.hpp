#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "Iterator.hpp"

namespace ft {

	template< class T, class A = std::allocator<T> >
	class vector {
	public:
		typedef T					value_type;
		typedef A 					allocator_type;
		typedef std::size_t			size_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef T*					pointer;
		typedef const T*			const_pointer;

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

//		template< class InputIt >
//		vector(InputIt first, InputIt last, const A& alloc = A()) : _array(nullptr), _allocator(alloc), _size(0), _capacity(0) {
//
//		}

		~vector() {
			clear();
			_allocator.deallocate(_array, _capacity);
		}

		vector& operator=( const vector& other ) {
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
//				assign();
			}
			return *this;
		}

		const_reference operator[](size_type pos) {
			return _array[pos];
		}

		reference operator[](size_type pos) const {
			return _array[pos];
		}

		allocator_type get_allocator() const {
			return _allocator;
		}

		reference at(size_type pos) {
			if (pos >= _size) throw std::out_of_range("Vector");
			return _array[pos];
		}

		const_reference at(size_type pos) const {
			if (pos >= _size) throw std::out_of_range("Vector");
			return _array[pos];
		}

		reference front() {
			return _array[0];
		}

		const_reference front() const {
			return _array[0];
		}

		reference back() {
			return _array[_size - 1];
		}

		const_reference back() const {
			return _array[_size - 1];
		}

		pointer data() {
			return _array;
		}

		const_pointer data() const {
			return _array;
		}

		bool empty() const {
			return _size == 0;
		}

		size_type max_size() const {
			return std::min(static_cast<size_type>(std::numeric_limits<typename A::difference_type>::max()),
							_allocator.max_size());
		}

		size_type size() const {
			return _size;
		}

		size_type capacity() {
			return _capacity;
		}

		void clear() {
			for (size_type i = 0; i < _size; ++i) {
				_allocator.destroy(&_array[i]);
			}
			_size = 0;
		}

		void reserve(size_type new_cap) {
			if (new_cap > _capacity) {
				pointer tmp = _allocator.allocate(new_cap);
				std::memcpy(tmp, _array, sizeof(T) * _size);
				if (_array) {
					_allocator.deallocate(_array, _capacity);
				}
				_capacity = new_cap;
				_array = tmp;
			}
		}

		void push_back(const_reference value) {
			if (_size == _capacity) {
				!_capacity ? reserve(1) : reserve(_capacity * 2);
			}
			_array[_size++] = value;
		}
	};
}

#endif /*VECTOR_HPP*/
