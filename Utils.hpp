#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
	template<bool b, typename T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant {
		typedef T value_type;
		typedef integral_constant<T,v> type;
		static const T value = v;
		operator T() { return value; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename T> struct is_integral : public false_type {};
	template<> struct is_integral<bool> : public true_type {};
	template<> struct is_integral<char> : public true_type {};
	template<> struct is_integral<char16_t> : public true_type {};
	template<> struct is_integral<char32_t> : public true_type {};
	template<> struct is_integral<signed char> : public true_type {};
	template<> struct is_integral<unsigned char> : public true_type {};
	template<> struct is_integral<wchar_t> : public true_type {};
	template<> struct is_integral<short> : public true_type {};
	template<> struct is_integral<unsigned short> : public true_type {};
	template<> struct is_integral<int> : public true_type {};
	template<> struct is_integral<unsigned int> : public true_type {};
	template<> struct is_integral<long> : public true_type {};
	template<> struct is_integral<unsigned long> : public true_type {};
	template<> struct is_integral<long long> : public true_type {};
	template<> struct is_integral<unsigned long long> : public true_type {};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, (void) ++first2) {
			if (!pred(*first1, *first2))
				return false;
		}
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, (void) ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2, Compare comp) {
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}

#endif /*UTILS_HPP*/
