#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in("d2s1.txt");
    string line;
    vector<int> data;
    int horizontal = 0, depth = 0, aim = 0;
    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        size_t space = line.find_first_of(" ");
        string command = line.substr(0, space);
        int value = atoi(line.substr(space + 1).c_str());
        cout << command << " " << value << endl;
        if (command == "forward") {
            horizontal += value;
            depth += (aim * value);
        } else if (command == "down") {
            aim += value;
        } else if (command == "up") {
            aim -= value;
        }
    }

    cout << "depth " << depth << endl;
    cout << "horizontal " << horizontal << endl;
    cout << "combined " << depth * horizontal << endl;
    return 0;
}
