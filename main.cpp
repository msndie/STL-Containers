#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Map.hpp"
#include "Set.hpp"
#include <map>
#include <set>
#include <sys/time.h>

#define TESTED_TYPE int
#define ratio 10000

time_t timer() {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}

std::vector<TESTED_TYPE> vector_erase_test_ft() {
	time_t t1;
	time_t t2;
	std::vector<int> v;

	t1 = timer();
	ft::vector<int> vector;
	for (int i = 0; i < 9900 * ratio; ++i)
		vector.push_back(i);
	v.push_back(*(vector.erase(vector.begin() + 8 * ratio, vector.end() - 1500 * ratio)));
	v.push_back(*(vector.begin() + 82 * ratio));
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	t2 = timer();

	std::cout << "vector \x1B[33merase\033[0m test \x1B[32mft\033[0m " << (t2 - t1) << std::endl;
	return v;
}

std::vector<TESTED_TYPE> vector_erase_test_std() {
	time_t t1;
	time_t t2;
	std::vector<int> v;

	t1 = timer();
	std::vector<int> vector;
	for (int i = 0; i < 9900 * ratio; ++i)
		vector.push_back(i);
	v.push_back(*(vector.erase(vector.begin() + 8 * ratio, vector.end() - 1500 * ratio)));
	v.push_back(*(vector.begin() + 82 * ratio));
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	t2 = timer();

	std::cout << "vector \x1B[33merase\033[0m test \x1B[34mstd\033[0m " << (t2 - t1) << std::endl;
	return v;
}

std::vector<TESTED_TYPE> vector_assign_test_ft() {
	time_t t1;
	time_t t2;
	std::vector<int> v;
	ft::vector<int> tmp, tmp1, tmp2;

	t1 = timer();
	tmp1.assign(3, 3);
	tmp.assign(4000 * ratio, 1);
	tmp2.assign(4 * ratio, 1);
	tmp1.assign(tmp.begin(), tmp.end());
	v.push_back(tmp1[1]);
	v.push_back(tmp1.size());
	v.push_back(tmp1.capacity());
	tmp1.assign(tmp2.begin(), tmp2.end());
	v.push_back(tmp1[444]);
	v.push_back(tmp1.size());
	v.push_back(tmp1.capacity());
	t2 = timer();

	std::cout << "vector \x1B[33massign\033[0m test \x1B[32mft\033[0m " << (t2 - t1) << std::endl;
	return v;
}

std::vector<TESTED_TYPE> vector_assign_test_std() {
	time_t t1;
	time_t t2;
	std::vector<int> v;
	std::vector<int> tmp, tmp1, tmp2;

	t1 = timer();
	tmp1.assign(3, 3);
	tmp.assign(4000 * ratio, 1);
	tmp2.assign(4 * ratio, 1);
	tmp1.assign(tmp.begin(), tmp.end());
	v.push_back(tmp1[1]);
	v.push_back(tmp1.size());
	v.push_back(tmp1.capacity());
	tmp1.assign(tmp2.begin(), tmp2.end());
	v.push_back(tmp1[444]);
	v.push_back(tmp1.size());
	v.push_back(tmp1.capacity());
	t2 = timer();

	std::cout << "vector \x1B[33massign\033[0m test \x1B[34mstd\033[0m " << (t2 - t1) << std::endl;
	return v;
}

std::vector<TESTED_TYPE> vector_constructor_test_ft() {
	time_t t1;
	time_t t2;
	std::vector<int> v;

	t1 = timer();
	ft::vector<int> tmp(1000 * ratio, 4), tmp2(1000 * ratio, 5);
	ft::vector<int> tmp0(tmp);
	tmp = tmp2;
	ft::vector<int> tmp4(tmp.begin(), tmp.end());
	v.push_back(tmp4.size());
	v.push_back(tmp4.capacity());
	v.push_back(tmp[2]);
	v.push_back(tmp4[2]);
	try { ft::vector<int> tmp5(-1, -1); }
	catch (std::exception &e) { v.push_back(1); }
	t2 = timer();

	std::cout << "vector \x1B[33mconstructor\033[0m test \x1B[32mft\033[0m " << (t2 - t1) << std::endl;
	return v;
}

std::vector<TESTED_TYPE> vector_constructor_test_std() {
	time_t t1;
	time_t t2;
	std::vector<int> v;

	t1 = timer();
	std::vector<int> tmp(1000 * ratio, 4), tmp2(1000 * ratio, 5);
	std::vector<int> tmp0(tmp);
	tmp = tmp2;
	std::vector<int> tmp4(tmp.begin(), tmp.end());
	v.push_back(tmp4.size());
	v.push_back(tmp4.capacity());
	v.push_back(tmp[2]);
	v.push_back(tmp4[2]);
	try { std::vector<int> tmp5(-1, -1); }
	catch (std::exception &e) { v.push_back(1); }
	t2 = timer();

	std::cout << "vector \x1B[33mconstructor\033[0m test \x1B[34mstd\033[0m " << (t2 - t1) << std::endl;
	return v;
}

int		main(void) {
	{
		std::vector<int> std = vector_constructor_test_std();
		std::vector<int> ft = vector_constructor_test_ft();
		if (ft != std)
			std::cout << "\x1B[31mconstructor test failed\033[0m" << std::endl;
	}

	{
		std::vector<int> std = vector_assign_test_std();
		std::vector<int> ft = vector_assign_test_ft();
		if (ft != std)
			std::cout << "\x1B[31massign test failed\033[0m" << std::endl;
	}

	{
		std::vector<int> std = vector_erase_test_std();
		std::vector<int> ft = vector_erase_test_ft();
		if (ft != std)
			std::cout << "\x1B[31merase test failed\033[0m" << std::endl;
	}
}
