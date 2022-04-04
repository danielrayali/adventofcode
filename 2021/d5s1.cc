#include <iostream>
#include <fstream>
#include "util.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input("d5s1.txt");
    while (getline(input, line)) {
        size_t pos_x = line.find_first_of(",");
        int x = atoi(line.substr(0, pos_x).c_str());
        int pos_y = line.find_first_of(" -> ", pos_x);
        int y = atoi(line.substr(pos_x + 1, pos_y - (pos_x + 1)).c_str());
        cout << "First: " << x << " " << y << endl;

        pos_x = line.find_first_of(",", pos_y + 4);
        x = atoi(line.substr(pos_y + 4, pos_x - (pos_y + 4)).c_str());
        y = atoi(line.substr(pos_x + 1).c_str());
        cout << "Second: " << x << " " << y << endl;
    }
    return 0;
}
