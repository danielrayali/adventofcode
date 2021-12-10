#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in("d1s1.txt");
    string line;
    vector<int> data;
    while (getline(in, line)) {
        data.push_back(atoi(line.c_str()));
    }

    int prev = numeric_limits<int>::max();
    int increases = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data.at(i) > prev) {
            increases++;
        }
        prev = data.at(i);
    }

    cout << "Number of increases: " << increases << endl;
    return 0;
}
