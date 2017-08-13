#include <iostream>
#include "hash_table.h"
#include <time.h>
#include <vector>
int main () 
{
	srand(time(NULL));
	hash_table<int> h(100);
	std::vector<int> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(rand() % 10000 + 1);
		h.insert(v.back(), i);
	}

	for (int i = 0; i < 100; i++) {
		std::cout << h[v[i]] << std::endl;
	}

	std::cout << "Size: " << h.size() << std::endl;

	for (int i = 0; i < 100; i++) {
		std::cout << h.remove(v[i]) << std::endl;
	}

	std::cout << "Size: " << h.size() << std::endl;
}