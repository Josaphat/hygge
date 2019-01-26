#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

int show_image()
{
	std::cout << "Hello World\n";

	std::ifstream scene1;
	scene1.open("scene1.bmp", std::ios::binary | std::ios::ate);
	scene1.seekg(0, scene1.end);
	unsigned int length = scene1.tellg();
	scene1.seekg(0, scene1.beg);
	std::vector<char> buffer(length);
	scene1.read(buffer.data(), length);
	scene1.close();

	for (unsigned int i = 0; i < 54; i++) {
		std::cout << +(uint8_t)buffer.data()[i];
		std::cout << " ";
	}
	std::cout << "\n";
	std::cout << "\n";
	int row_padded = (128 * 3 + 3) & (~3);
	std::cout << "row padding = " << row_padded;
	std::cout << std::endl;

	for (unsigned int i = 54; i < buffer.size(); i+=3) {
		if ((i-54) % (128 * 3) == 0) {
			std::cout << "\n";
		}

		auto r = (uint8_t)buffer.data()[i+2];
		auto g = (uint8_t)buffer.data()[i+1];
		auto b = (uint8_t)buffer.data()[i+0];
		if (r == 0 && b == 0 && g == 0) {
			std::cout << " ";
		}
		else if (r == 255 && b == 255 && g == 255) {
			std::cout << "x";
		}
		else {
			std::cout << "^";
		}

	}

    return 0;
}
