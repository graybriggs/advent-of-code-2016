#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


std::vector<std::string> get_signal(const std::string fname) {

	std::vector<std::string> signal;

	std::ifstream ifs(fname);
	std::string input;

	while (std::getline(ifs, input)) {
		signal.push_back(input);
	}

	return signal;

}

char most_frequent_char(const std::map<char, int> m) {

	int highest = m.begin()->second;
	char hc = m.begin()->first;

	for (auto it : m) {
		if (it.second > highest) {
			highest = it.second;
			hc = it.first;
		}
	}
	return hc;
}

char least_frequent_char(const std::map<char, int> m) {

	int lowest = m.begin()->second;
	char lc = m.begin()->first;

	for (auto it : m) {
		if (it.second < lowest) {
			lowest = it.second;
			lc = it.first;
		}
	}
	return lc;
}


int main() {

	auto signals = get_signal("day6-input.txt");

	std::map<char, int> occurrence;

	for (int column = 0; column < 8; column++) {
		for (auto& sig : signals) {
			auto it = occurrence.find(sig[column]);
			if (it != std::end(occurrence)) {
				int val = occurrence[sig[column]];
				occurrence[sig[column]] = ++val;
			}
			else {
				occurrence[sig[column]] = 1;
			}
		}

		//std::cout << most_frequent_char(occurrence);
		std::cout << least_frequent_char(occurrence);			
		occurrence.clear();
	}
	std::cout << std::endl;

	char c;
	std::cin >> c;

}

