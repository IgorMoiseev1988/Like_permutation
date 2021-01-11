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
  return (os);
}

template<typename OutputIt, typename ForwardIt>
bool next_value(OutputIt iterator, ForwardIt first, ForwardIt last) { 
  auto it = std::find(first, last, *iterator);
  if (it == last || it == std::prev(last)) {
     *iterator = *first;
     return (true);
  }
  *iterator = *(std::next(it));
  return (false);
}

template<typename OutputIt, typename ForwardIt>
bool prev_value(OutputIt iterator, ForwardIt first, ForwardIt last) {
  auto it = std::find(first, last, *iterator);
  if (it == first) {
    *iterator = *(std::prev(last));
    return (true);
  }
  *iterator = *(std::prev(it));
  return (false);
}

template<typename InputIt1, typename InputIt2>
bool end_permutation(InputIt1 first, InputIt1 last, InputIt2 control) {
  typedef typename std::iterator_traits<InputIt1>::value_type T;
  return (std::all_of(first, last, [control](const T& t) { return (t == *control); }));
}

template<typename InputIt1, typename InputIt2>
bool start_permutation(InputIt1 first, InputIt1 last, InputIt2 control) {
  typedef typename std::iterator_traits<InputIt1>::value_type T;
  return (std::all_of(first, last, [control](const T& t) { return (t == *control); }));
}

template <typename ForwardIt1, typename ForwardIt2>
bool non_sorted_includes(ForwardIt1 container_first, ForwardIt1 container_last, ForwardIt2 values_first, ForwardIt2 values_last) {
  for (; container_first != container_last; ++container_first) {
    if (std::find(values_first, values_last, *container_first) == values_last) return (false);
  }
  return (true);
}

template <typename T>
bool is_difference_types(const T&, const T&) { return (false); }

template <typename T, typename U>
bool is_difference_types(const T&, const U&) { return (true); }

template<typename InputIt1, typename InputIt2>
bool is_valid_containers(InputIt1 container_first, InputIt1 container_last, InputIt2 values_first, InputIt2 values_last) {
  typename std::iterator_traits<InputIt1>::difference_type container_size = std::distance(container_first, container_last);
  typename std::iterator_traits<InputIt2>::difference_type values_size = std::distance(values_first, values_last);
  if (container_size == 0 || values_size == 0) return false;
  if (is_difference_types(container_first, values_first)) {
    std::cerr << "Containers must have same types\n"s;
    return (false);
  }
  if (!(non_sorted_includes(container_first, container_last, values_first, values_last))) {
    std::cerr << "First container must only contains values from second container\n"s;
    return (false);
  }
  return (true);
}

template<typename OutputIt, typename ForwardIt>
bool next_limit_permutation(OutputIt container_first, OutputIt container_last, ForwardIt values_first, ForwardIt values_last) {
typename std::iterator_traits<OutputIt>::difference_type container_size = std::distance(container_first, container_last);
  if (!is_valid_containers(container_first, container_last, values_first, values_last)) return false;
  if (end_permutation(container_first, container_last, std::prev(values_last))) return false;
  while ((container_size > 0) && (next_value(container_first + --container_size, values_first, values_last)));
  return container_size >= 0;
}

template<typename OutputIt, typename ForwardIt>
bool prev_limit_permutation(OutputIt container_first, OutputIt container_last, ForwardIt values_first, ForwardIt values_last) {
  typename std::iterator_traits<OutputIt>::difference_type container_size = std::distance(container_first, container_last);
  if (!is_valid_containers(container_first, container_last, values_first, values_last)) return false;
  if (start_permutation(container_first, container_last, values_first)) return false;
  while ((container_size > 0) && (prev_value(container_first + --container_size, values_first, values_last)));
  return container_size >= 0;
}

//for example
int main() {
std::vector<int> values {1, 3, 5};
std::vector<int> arr {1, 3};
int count {0};
  do {
    std::cout << ++count << ": "s << arr << "\n"s;
  } while (next_limit_permutation(arr.begin(), arr.end(), values.begin(), values.end()));
  do {
    std::cout << ++count << ": "s << arr << "\n";
  } while (prev_limit_permutation(arr.begin(), arr.end(), values.begin(), values.end()));
  return 0;
}
