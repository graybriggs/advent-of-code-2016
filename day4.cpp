
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

const int checksum_length = 5;

std::vector<std::string> get_input(const std::string& fname) {

	std::vector<std::string> roomData;

	std::ifstream ifs(fname);
	std::string input;

	while (std::getline(ifs, input)) {
		roomData.push_back(input);
	}
	return roomData;
}

std::string extract_checksum(const std::string& code) {

	return code.substr(code.find('[') + 1, checksum_length);

}

std::string extract_code(const std::string& code)  {

	return code.substr(0, code.find('[') - 3);

}

std::string extract_sectorid(const std::string& code) {

	int pos = 0;
	for (; pos < code.length(); ++pos) {
		if (isdigit(code[pos])) {
			break;
		}
	}
	return code.substr(pos, 3);
}

std::vector<char> find_highest_char(std::map<char, int> m) {

	std::vector<char> highest_chars;
	
	for (int i = 0; i < 5; i++) {

		int highest = std::begin(m)->second;
		char highest_key = std::begin(m)->first;

		for (auto& a : m) {
			if (a.second > highest) {
				highest = a.second;
				highest_key = a.first;
			}
		}
		highest_chars.push_back(highest_key);
		m.erase(highest_key);
	}
	return highest_chars;
}

bool is_match(const std::vector<char>& highest_chars, const std::string& checksum) {

	for (int i = 0; i < highest_chars.size(); ++i) {
		if (highest_chars[i] != checksum[i])
			return false;
	}
	return true;
}

unsigned char rotate_char(const unsigned char c, const int amount) {

	unsigned char rotated_char = c + amount;

	if (rotated_char > 'z') {
		int diff = rotated_char - 122;

		diff %= 26;

		rotated_char = 'a' + diff - 1; 
	}
	return rotated_char;
}

std::string decrypt_room_name(const std::string& name, const int sector_id) {

	std::string decrypted_name;

	for (int i = 0; i < name.length(); ++i) {
		if (name[i] == '-')
			decrypted_name += " ";
		else
			decrypted_name += rotate_char(name[i], (sector_id % 26));
	}
	return decrypted_name;
}

int main() {

	std::vector<std::string> data = get_input("day4-input.txt");

	std::map<char, int> occurrence;
	int sector_id_sum = 0;

	for (auto& d : data) {

		auto code = extract_code(d);
		auto checksum = extract_checksum(d);
		auto sid = extract_sectorid(d);

		for (int i = 0; i < code.length(); ++i) {
			if (code[i] != '-') {
				auto it = occurrence.find(code[i]);
				if (it != std::end(occurrence)) {
					int counter = occurrence[code[i]];
					occurrence[code[i]] = ++counter;
				}
				else {
					occurrence[code[i]] = 1;
				}
			}

		}
		auto& v = find_highest_char(occurrence);
		occurrence.clear();

		if (is_match(v, checksum)) {
			sector_id_sum += std::stoi(sid);
		}
	}
	std::cout << sector_id_sum << std::endl;

	std::cout << "Part 2" << std::endl;

	for (auto& d : data) {
		auto code = extract_code(d);
		auto sid = extract_sectorid(d);	
		auto decrypted_name = decrypt_room_name(code, std::stoi(sid));

		if (decrypted_name.find("north") != std::string::npos) {
			std::cout << decrypted_name << std::endl;
			std::cout << sid << std::endl;
			break;
		}		
	}
	
}