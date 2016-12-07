#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Triangle {
	int edge[3];
};

std::vector<Triangle> split(std::string fname) {

	std::vector<Triangle> triangles;
	std::string input;
	std::fstream ifs(fname);

	int first, second, third;

	while (std::getline(ifs, input)) {
		Triangle t;
		std::sscanf(input.c_str(), "%d %d %d", &t.edge[0], &t.edge[1], &t.edge[2]);
		triangles.push_back(t);
	}

	return triangles;
}



int main() {

	std::vector<Triangle> triangles = split("day3-input.txt");

	int possible = 0;

	for (auto& tri : triangles) {

		if ((tri.edge[0] + tri.edge[1] > tri.edge[2]) &&
			(tri.edge[0] + tri.edge[2] > tri.edge[1]) &&
			(tri.edge[1] + tri.edge[2] > tri.edge[0])) {
			possible++;
		}
	}

	std::cout << possible << " possible" << std::endl;

	std::cout << "Part 2" << std::endl;

	// file size is divisible by 3 so we are safe.
	possible = 0;

	for (int column = 0; column < 3; column++) {
		for (int i = 0; i < triangles.size(); i += 3) {

			if ((triangles[i    ].edge[column] + triangles[i + 1].edge[column] > triangles[i + 2].edge[column]) &&
				(triangles[i    ].edge[column] + triangles[i + 2].edge[column] > triangles[i + 1].edge[column]) &&
				(triangles[i + 1].edge[column] + triangles[i + 2].edge[column] > triangles[i    ].edge[column])) {
					possible++;
				}
		}
	}

	std::cout << possible << " possible" << std::endl;

	char c;
	std::cin >> c;
}

