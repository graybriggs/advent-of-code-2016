
#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace day8 {

std::vector<std::string> read_input(std::string fname) {

	std::vector<std::string> instructions;

	std::ifstream ifs(fname);
	std::string input;

	while (std::getline(ifs, input)) {
		instructions.push_back(input);
	}
	return instructions;
}

class Screen {
public:

	Screen() {
		std::fill(std::begin(screen), std::end(screen), '.');
	}

	void put_pixel(const int x, const int y) {
		screen[y * screen_w + x] = '#';
	}


	void parse_instruction(const std::string& ins) {

		if (ins.find("row") != std::string::npos) {
			int a, b;
			sscanf(ins.c_str(), "rotate row y=%d by %d", &a, &b);

			rotate_row(a, b);
		}
		else if (ins.find("column") != std::string::npos) {
			int a, b;
			sscanf(ins.c_str(), "rotate column x=%d by %d", &a, &b);
			
			rotate_column(a, b);
		}
		else if (ins.find("rect") != std::string::npos) {
			int x, y;
			sscanf(ins.c_str(), "rect %dx%d", &x, &y);
			
			create_rect(x, y);
		}
		else {
			return;
		}

	}

	void create_rect(int x, int y) {

		for (int i = 0; i < y; ++i) {
			for (int j = 0; j < x; ++j) {
				screen[i * screen_w + j] = '#';
			}
		}

	}

	void rotate_row(int row, int amount) {
		if (row > screen_h)
			return;

		std::array<int, screen_w> row_buffer;

		for (int i = 0; i < screen_w; ++i) {
			row_buffer[i] = screen[row * screen_w + i];
		}

		clear_row(row);

		for (int i = 0; i < screen_w; ++i) {
			if (i + amount < screen_w)
				screen[row * screen_w + i + amount] = row_buffer[i];
			else
				screen[row * screen_w + i + amount - screen_w] = row_buffer[i];
		}

	}

	void rotate_column(int col, int amount) {
		if (col > screen_w)
			return;

		std::array<int, screen_h> column_buffer;

		for (int i = 0; i < screen_h; ++i) {
			column_buffer[i] = screen[i * screen_w + col];
		}

		clear_column(col);

		for (int i = 0; i < screen_h; ++i) {

			if (i + amount < screen_h)
				screen[(i + amount) * screen_w + col] = column_buffer[i];
			else
				screen[(i + amount) * screen_w + col - (screen_w * screen_h)] = column_buffer[i];


		}

	}

	void print_screen() {

		for (int y = 0; y < screen_h; ++y) {
			for (int x = 0; x < screen_w; x++) {
				std::cout << (char)screen[y * screen_w + x];
			}
			std::cout << std::endl;
		}
	}

	int count_on_pixels() {
		int counter = 0;

		for (int i = 0; i < screen.size(); i++) {
			if (screen[i] == '#')
				++counter;
		}
		return counter;
	}

private:

	void clear_row(int row) {

		for (int i = 0; i < screen_w; ++i) {
			screen[row * screen_w + i] = '.';
		}
	}

	void clear_column(int col) {

		for (int i = 0; i < screen_h; i += screen_h) {
			screen[i * screen_h + col] = '.';
		}
	}


private:
	static const int screen_w = 50;
	static const int screen_h = 6;

	std::array<int, screen_w * screen_h> screen;

};
 
}

int main() {

	using namespace day8;

	auto instructions = read_input("day8-input.txt");

	Screen scr;

	for (auto& ins : instructions)
		scr.parse_instruction(ins);

	scr.print_screen();
	std::cout << scr.count_on_pixels() << " turned on";

}
