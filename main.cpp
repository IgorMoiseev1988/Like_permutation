#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std::string_literals;

int askNumber() {
	int ret {0};
	do {
		std::cin >> ret;
		if (std::cin.fail()) {
			std::cout << "This is not a number! Try again: ";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
	} while (ret == 0);
	std::cin.ignore(32767, '\n');
	return ret;
}

template <typename T>
void T_swap(T& a, T&b) {
	T temp = a;
	a = b;
	b = temp;
}

int factorial(int N) {
	if (N == 1) return 1;
	if (N == 0) return 1;
	return factorial(N - 1) * N;
}

int sumNumber(int N) {
	if (N < 10) return N;
	return sumNumber(N / 10) + N % 10;
}

void binaryPrint(int N) {
	unsigned int n = static_cast<unsigned int>(N);
	if (n < 2) {
		std::cout << n;
	} else {
		binaryPrint(n / 2);
		std::cout << n % 2;
	}
}

//std::set<int>::iterator operator+(std::set<int>::iterator it, int a) {
//	while (a--) ++it;
//	return it;
//}

template<typename T>
std::ostream& operator<< (std::ostream& os, std::vector<T> v) {
	os << "["s;
	bool first {true};
	for (const auto& elem : v) {
		if (!first) os << " ";
		os << elem;
		first = false;
	}
	os << "]"s;
	return os;
}

template<typename OutputIt, typename ForwardIt>
bool next_value(OutputIt iterator, ForwardIt first, ForwardIt last) { 
	auto it = std::find(first, last, *iterator);
	if (it == last || it == std::prev(last)) {
		*iterator = *first;
		return true;
	}
	*iterator = *(++it);
	return false;
}

template<typename InputIt1, typename InputIt2>
bool end_permutation(InputIt1 first, InputIt1 last, InputIt2 control) {
	typedef typename std::iterator_traits<InputIt1>::value_type T;
	return std::all_of(first, last, [control](const T& t) { return t == *control; });
}

template <typename ForwardIt1, typename ForwardIt2>
bool non_sorted_includes(ForwardIt1 container_first, ForwardIt1 container_last, ForwardIt2 values_first, ForwardIt2 values_last) {
	for (; container_first != container_last; ++container_first) {
		if (std::find(values_first, values_last, *container_first) == values_last) return false;
	}
	return true;
}

template <typename T, typename U>
bool check_types(const T&, const U&) { return true; }

template <typename T>
bool check_types(const T&) { return false; }

template<typename OutputIt, typename ForwardIt>
bool next_limit_permutation(OutputIt container_first, OutputIt container_last, ForwardIt values_first, ForwardIt values_last) {
	typename std::iterator_traits<OutputIt>::difference_type container_size = std::distance(container_first, container_last);
	typename std::iterator_traits<ForwardIt>::difference_type values_size = std::distance(values_first, values_last);
	if (container_size < values_size || !(container_size * values_size)) return false;
  //тут бы проверить что оба контейнера укзаывают на данные одного типа
	//if (std::is_same_v<decltype(*container_first), decltype(*values_first)>) {
	//	std::cerr << "Containers must have same type\n";
	//	return false;
	//}
	if (!(non_sorted_includes(container_first, container_last, values_first, values_last))) {
		std::cerr << "First container must only contains values form second conteiner\n";
		return false;
	}
	if (end_permutation(container_first, container_last, std::prev(values_last))) return false;
	while ((container_size > 0) && (next_value(container_first + --container_size, values_first, values_last)));
	return container_size >= 0;
}

int main() {
	std::set<int> values {1, 0};
	std::vector<int> arr {1,0,1,1};
	int count {0};
	do {
		std::cout << ++count << ": "s << arr << "\n"s;
	} while (next_limit_permutation(arr.begin(), arr.end(), values.begin(), values.end()));

	return 0;
}
