#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

enum class Direction{ North, East, South, West };

struct Instruction {
	char dir;
	int dist;
};

std::string& strip_whitespace(std::string& s) {

	s.erase(std::remove_if(std::begin(s), std::end(s), [](char c) {
		return std::isspace(c);
	}));

	return s;
}


void read_coordinates(std::vector<Instruction>& instructions, const std::string& fn) {
	
	std::ifstream ifs(fn);
	std::string value;

	while (!ifs.eof()) {
		std::getline(ifs, value, ',');
		value = strip_whitespace(value);
		
		Instruction ins;
		ins.dir = value.at(0);
		ins.dist = std::stoi(value.substr(1));
		instructions.push_back(ins);
	}
}



struct Position {

	Position() :
		posx(0), posy(0), dir(Direction::North)
	{
	}

	void process_instructions(std::vector<Instruction>& instructions) {

		for (auto& ins : instructions) {
			update_position(ins);
		}
	}

	void update_position(const Instruction& ins) {
		
		if (ins.dir == 'R') {
			if (dir == Direction::North)
				dir = Direction::East;
			else if (dir == Direction::East)
				dir = Direction::South;
			else if (dir == Direction::South)
				dir = Direction::West;
			else if (dir == Direction::West)
				dir = Direction::North;
		}
		else if (ins.dir == 'L') {
			if (dir == Direction::North)
				dir = Direction::West;
			else if (dir == Direction::West)
				dir = Direction::South;
			else if (dir == Direction::South)
				dir = Direction::East;
			else if (dir == Direction::East)
				dir = Direction::North;
		}

		if (dir == Direction::North)
			posy += ins.dist;
		else if (dir == Direction::South)
			posy -= ins.dist;
		else if (dir == Direction::East)
			posx += ins.dist;
		else if (dir == Direction::West)
			posx -= ins.dist;
	}

	int distance() {
		return std::abs(posx) + std::abs(posy);
	}

	int posx, posy;
	Direction dir;
};

/*

int main() {

	std::vector<Instruction> instructions;

	read_coordinates(instructions, "day1-input.txt");

	Position p;
	p.process_instructions(instructions);
	std::cout << p.distance() << std::endl;

	char c;
	std::cin >> c;
}

*/