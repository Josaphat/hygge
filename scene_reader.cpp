#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>


int main(int argc, char* argv[])
{
	//std::cout << "Hello World\n";

	std::ifstream scene1;
	scene1.open("scene1.bmp", std::ios::binary | std::ios::ate);
	scene1.seekg(0, scene1.end);
	unsigned int length = scene1.tellg();
	scene1.seekg(0, scene1.beg);
	std::vector<char> buffer(length);
	scene1.read(buffer.data(), length);
	scene1.close();


	std::ofstream out_scene1;
	out_scene1.open("scene1.txt");
	//for (unsigned int i = 0; i < 54; i++) {
	//	std::cout << +(uint8_t)buffer.data()[i];
	//	std::cout << " ";
	//}
	//std::cout << "\n";
	//std::cout << "\n";
	//int row_padded = (128 * 3 + 3) & (~3);
	//std::cout << "row padding = " << row_padded;
	//std::cout << std::endl;

	unsigned int offset = 54;
	for (unsigned int row = 0; row < 72; row++) {
		for (unsigned int col = 0; col < 128*3; col += 3) {

			if (col == 0 && row!=0) {
				std::cout << "\n";
				out_scene1 << "\n";
			}

			auto r = (uint8_t)buffer.data()[offset + ((71 - row) * (128 * 3)) + (col) + 2];
			auto g = (uint8_t)buffer.data()[offset + ((71 - row) * (128 * 3)) + (col) + 1];
			auto b = (uint8_t)buffer.data()[offset + ((71 - row) * (128 * 3)) + (col) + 0];
			if (r == 0 && b == 0 && g == 0) {
				std::cout << "X";
				out_scene1 << "X";
			}
			else if (r == 255 && b == 255 && g == 255) {
				std::cout << ".";
				out_scene1 << ".";
			}
			else if (r == 32 && b == 64 && g == 192) {
				std::cout << "G";
				out_scene1 << "G";
			}
			else if (r == 224 && b == 64 && g == 32) {
				std::cout << "R";
				out_scene1 << "R";
			}
			else {
				std::cout << "val: " << +r << " " << +b << " " << +g;
				std::cout << "?";
				out_scene1 << "?";
			}
		}
	}
	out_scene1.close();

    return 0;
}
