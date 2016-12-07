

#include <iostream>
#include <string>
#include <vector>
#include <fstream>



std::vector<std::string> getCodes(std::string fname) {

	std::vector<std::string> codes;
	
	std::ifstream ifs(fname);
	std::string line;

	while (std::getline(ifs, line)) {
		codes.push_back(line);
	}
	return codes;
}


int main() {

	std::vector<std::string > codes = getCodes("day2-input.txt");

	
	// Part 1
	std::cout << "Part 1\n";

	int x = 0;
	int y = 0;

	for (auto& code : codes) {
		for (int i = 0; i < code.length(); i++) {
			
			switch (code[i]) {
			case 'U':
				if (y < 1)
					y++;
				break;
			case 'D':
				if (y > -1)
					y--;
				break;
			case 'L':
				if (x > -1)
					x--;
				break;
			case 'R':
				if (x < 1)
					x++;
				break;
			}
		}
		std::cout << x << ", " << y << std::endl;
	}

	// Part 2
	std::cout << "Part 2\n";

	int grid[5][5] = {
		{0,0,1,0,0},
		{0,2,3,4,0},
		{5,6,7,8,9},
		{0,-1,-2,-3,0},
		{0,0,-4,0,0}
	};
	x = 0;
	y = 2;


	for (auto& code : codes) {
		for (int i = 0; i < code.length(); i++) {

			switch (code[i]) {
			case 'U':
				if (y > 0 && grid[y - 1][x] != 0)
					y--;
				break;
			case 'D':
				if (y < 4 && grid[y + 1][x] != 0)
					y++;
				break;
			case 'L':
				if (x > 0 && grid[y][x - 1] != 0)
					x--;
				break;
			case 'R':
				if (x < 4 && grid[y][x + 1] != 0)
					x++;
				break;
			}
		}
		std::cout << x << ", " << y << std::endl;
	}

	char c;
	std::cin >> c;
}



