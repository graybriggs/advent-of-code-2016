#include <algorithm>
#include <iostream>
#include <vector>


void invert(std::vector<int>& data) {

	for (std::size_t i = 0; i < data.size(); ++i) {
		if (data[i] == 1)
			data[i] = 0;
		else
			data[i] = 1;
	}

}


std::vector<int> dragon_curve(std::vector<int>& data, const int disk_size) {

	std::vector<int> resulting_data(data);

	while (resulting_data.size() < disk_size) {

		std::vector<int> copy(resulting_data);
		std::reverse(std::begin(copy), std::end(copy));
		invert(copy);

		resulting_data.push_back(0);

		for (auto &c : copy) {
			resulting_data.push_back(c);
		}
	}

	resulting_data.erase(std::begin(resulting_data) + disk_size, std::end(resulting_data));

	return resulting_data;

}
std::vector<int> checksum(std::vector<int>& data) {

	std::vector<int> cksum;
	
	while (data.size() % 2 == 0) {
		cksum.clear();

		for (std::size_t i = 0; i < data.size(); i += 2) {
			if (data[i] == data[i + 1])
				cksum.push_back(1);
			else
				cksum.push_back(0);
		}
		
		data.clear();
		for (auto& cs : cksum) {
			data.push_back(cs);
		}
	}
	std::cout << "\n";
	return cksum;
}



int main() {

	constexpr int pt_1_disk_size = 272;
	constexpr int pt_2_disk_size = 35651584;

	std::vector<int> data = { 0,1,1,1,0,1,1,0,1,0,1,0,0,1,0,0,0 };

	std::vector<int> resulting_data = dragon_curve(data, pt_2_disk_size);
		
	std::cout << "\n\n";
	
	std::vector<int> cksum = checksum(resulting_data);

	std::cout << "Checksum: " << std::endl;
	for (auto& cs : cksum)
		std::cout << cs;

}