#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
	template<bool b, typename T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T> {
		typedef T type;
	};
}

#endif /*UTILS_HPP*/
