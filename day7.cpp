#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace day7 {

std::vector<std::string> get_input(const std::string& fname) {

	std::vector<std::string> addresses;
	std::string input;

	std::ifstream ifs(fname);

	while (std::getline(ifs, input)) {
		addresses.push_back(input);
	}
	return addresses;
}

std::vector<std::string> get_hypernet_sequences(const std::string& input) {

	std::vector<std::string> hypernets;
	int start;

	for (int i = 0; i < input.length(); ++i) {

		if (input[i] == '[') {
			start = i;
		}
		if (input[i] == ']') {
			hypernets.push_back(input.substr(start + 1, i - start - 1));
		}

	}
	return hypernets;
}

std::vector<std::string> get_ip(const std::string& input) {

	std::vector<std::string> ips;

	int start = 0;
	int end = 0;

	std::string ip;
	bool read = true;

	for (int i = 0; i < input.length(); ++i) {

		if (input[i] == '[') {
			read = false;
			ips.push_back(ip);
			ip.clear();
		}
		else if (input[i] == ']') {
			read = true;
			++i;
		}

		if (read)
			ip += input[i];
	}
	ips.push_back(ip);

	return ips;
}

bool has_four_char_palindrome(const std::string& input) {

	if (input.length() < 4)
		return false;

	for (int i = 0; i < input.length() - 4; ++i) {

		if (input[i] == input[i + 3] && input[i + 1] == input[i + 2] && input[i] != input[i + 1])
			return true;

	}
	return false;
}

int calculate_tls_support(const std::vector<std::string>& input) {
	int counter = 0;
	bool valid;

	for (auto& ip : input) {

		valid = false;

		auto hypernets = get_hypernet_sequences(ip);
		auto ips = get_ip(ip);

		for (auto& hn : hypernets) {
			if (has_four_char_palindrome(hn)) {
				valid = false;
			}
		}

		if (!valid) {
			for (auto& i : ips) {
				if (has_four_char_palindrome(i))
					valid = true;
			}
		}

		if (valid) {
			++counter;
		}
	}
	return counter;
}

// Part 2 functions

struct three_sequence {
	three_sequence() {
		seq[0] = '-';
		seq[1] = '-';
		seq[2] = '-';
	}
	three_sequence(char a, char b, char c) {
		seq[0] = a;
		seq[1] = b;
		seq[2] = c;
	}

	char seq[3];

	bool is_inverse(const three_sequence& other) {
		if (seq[0] == other.seq[1] &&
			seq[2] == other.seq[1] &&
			seq[1] == other.seq[0] &&
			seq[1] == other.seq[2] &&
			seq[1] != other.seq[1])
			return true;
		else
			return false;
	}
};

three_sequence get_three_seq(const std::string& input, int index) {

	three_sequence ts;
	ts.seq[0] = input[index];
	ts.seq[1] = input[index + 1];
	ts.seq[2] = input[index + 2];

	return ts;
}

std::vector<three_sequence> has_three_seq(const std::string& input) {

	std::vector<three_sequence> seq_positions;

	if (input.length() < 3)
		return seq_positions;

	for (int index = 0; index < input.length() - 2; ++index) {
		if (input[index] == input[index + 2] && (input[index] != input[index + 1] && input[index + 2] != input[index + 1])) {
			seq_positions.push_back(get_three_seq(input, index));
		}
	}
	return seq_positions;
}

}

int main() {
	using namespace day7;

	auto input = get_input("day7-input.txt");

	//std::vector<std::string> input = { "aaa[bbbcb]xxxccab[axx]abababababab", "aba[bab]xyz", "xyx[xyx]xyx", "top[kek]eke", "zazbz[bzb]cdb" };


	int counter = calculate_tls_support(input);

	std::cout << counter << " IPs support TLS" << std::endl;

	counter = 0;

	for (auto& ip : input) {

		auto ipaddresses = get_ip(ip);
		auto hnsequences = get_hypernet_sequences(ip);

		std::vector<three_sequence> ip_seq;
		std::vector<three_sequence> hn_seq;

		for (auto ips : ipaddresses) {
			auto ipv = has_three_seq(ips);
			ip_seq.insert(std::begin(ip_seq), std::begin(ipv), std::end(ipv));
		}

		for (auto hn : hnsequences) {
			auto hnv = has_three_seq(hn);
			hn_seq.insert(std::begin(hn_seq), std::begin(hnv), std::end(hnv));
		}

		// herp derp
		auto hnts = std::begin(hn_seq);
		while (hnts != std::end(hn_seq)) {

			auto ipts = std::begin(ip_seq);
			while (ipts != std::end(ip_seq)) {

				if (hnts->is_inverse(*ipts)) {
					counter++;
					ipts = std::end(ip_seq);
					hnts = std::end(hn_seq);
				}
				else {
					ipts++;
				}
			}
			if (hnts != std::end(hn_seq)) // ended by inner loop
				hnts++;
		}
	}

	std::cout << counter << " IPs support SSL" << std::endl;

	char c;
	std::cin >> c;
}