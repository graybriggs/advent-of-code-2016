#include <array>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace day12 {

class computer {
public:
	computer()
		: program_counter(0), registers({ 0 })
	{
	}

	computer(int r1, int r2, int r3, int r4)
    : program_counter(0)
	{
		registers[0] = r1;
		registers[1] = r2;
		registers[2] = r3;
		registers[3] = r4;
	}

	void run() {

		while (program_counter < program.size()) {
			decode_instruction(program[program_counter]);

		}
	}

	void dump_registers() const {
		for (auto reg : registers) {
			std::cout << reg << std::endl;
		}
	}

	void read_program(const std::string fname) {

		std::ifstream ifs(fname);
		std::string input;

		while (std::getline(ifs, input)) {
			program.push_back(input);
		}

	}

private:
	
	bool is_register(const char* str) {
		if (str[0] == 'a' || str[0] == 'b' || str[0] == 'c' || str[0] == 'd')
			return true;
		else
			return false;
	}

	void decode_instruction(const std::string next_ins) {

		char* tokens = std::strtok(const_cast<char*>(next_ins.c_str()), " ");

		if (std::strcmp(tokens, "cpy") == 0) {
			char* lhs = std::strtok(nullptr, " ");
			char* rhs = std::strtok(nullptr, " ");

			if (is_register(lhs)) {
				cpy_reg(to_dec(*lhs), to_dec(*rhs));
			}
			else {
				cpy(std::stoi(std::string(lhs)), to_dec(*rhs));
			}

		}
		else if (std::strcmp(tokens, "inc") == 0) {
			char* reg = std::strtok(nullptr, " ");
			inc(to_dec(*reg));
		}
		else if (std::strcmp(tokens, "dec") == 0) {
			char* reg = std::strtok(nullptr, " ");
			dec(to_dec(*reg));
		}
		else if (std::strcmp(tokens, "jnz") == 0) {
			char* lhs = std::strtok(nullptr, " ");
			char* rhs = std::strtok(nullptr, " ");

			if (is_register(lhs)) {
				jnz_reg(to_dec(*lhs), std::stoi(std::string(rhs)));
			}
			else {
				jnz(std::stoi(std::string(lhs)), std::stoi(std::string(rhs)));
			}
		}
	}

	int to_dec(const int reg) const {
		return reg - 'a';
	}

	void cpy(const int val, const int reg) {
		registers[reg] = val;
		program_counter++;
	}

	void cpy_reg(const int reg2, const int reg1) {
		registers[reg1] = registers[reg2];
		program_counter++;
	}

	void inc(const int reg_num) {
		registers[reg_num]++;
		program_counter++;
	}

	void dec(const int reg_num) {
		registers[reg_num]--;
		program_counter++;
	}

	void jnz(const int value, const int amount) {

		if (value == 0) {
			program_counter++;
			return;
		}
		else
			program_counter += amount;
	}

	void jnz_reg(const char reg_num, const int amount) {
		if (registers[reg_num] == 0) {
			program_counter++;
			return;
		}
		else
			program_counter += amount;
	}

private:

	std::vector<std::string> program;
	std::uint32_t program_counter;
	std::array<int, 4> registers;

};

}

int main() {

	using namespace day12;

	// takes a while

	// part 1
	/*
	computer comp;
	comp.read_program("day12-input.txt");
	comp.run();

	comp.dump_registers();
	*/

	// part 2

	computer comp(0,0,1,0);
	comp.read_program("day12-input.txt");
	comp.run();

	comp.dump_registers();

}
