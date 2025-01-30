
/*
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <string>

void print_c(const std::vector < std::string > & x) {
	for (std::string element : x) {

		std::cout << element << " ";
	}
	std::cout << '\n';
}

int main()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::vector<std::string> v{ "apple","cake","egg","juice"};
	std::vector < std::string > original_v;
	
	std::copy(v.begin(), v.end(), std::back_inserter(original_v));
	print_c(original_v);
	
print_c(v);

std::swap(v[0], v.back());
std::shuffle(v.begin(), v.end() - 1, g);
print_c(v);



}
*/